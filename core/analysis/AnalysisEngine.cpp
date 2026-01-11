#include "AnalysisEngine.h"
#include "../dsp/MonoUtils.h"

namespace kindpath::analysis
{
    AnalysisEngine::AnalysisEngine()
        : fft(fftOrder),
          window(fftSize, juce::dsp::WindowingFunction<float>::hann)
    {
    }

    void AnalysisEngine::prepare(double sampleRate, int blockSize, int numChannels)
    {
        currentSampleRate = sampleRate;
        expectedBlockSize = blockSize;
        expectedChannels = numChannels;
        reset();
    }

    void AnalysisEngine::reset()
    {
        fifo.fill(0.0f);
        fftData.fill(0.0f);
        fifoIndex = 0;
        nextFFTReady = false;
        lastSample = 0.0f;

        const juce::SpinLock::ScopedLockType lock(snapshotLock);
        latestSnapshot = {};
    }

    void AnalysisEngine::setMonoMonitoring(bool enabled)
    {
        monoMonitoring.store(enabled);
    }

    bool AnalysisEngine::getMonoMonitoring() const noexcept
    {
        return monoMonitoring.load();
    }

    void AnalysisEngine::processBlock(juce::AudioBuffer<float>& buffer)
    {
        const int numSamples = buffer.getNumSamples();
        const int numChannels = buffer.getNumChannels();

        if (monoMonitoring.load() && numChannels > 1)
            kindpath::dsp::collapseToMono(buffer);

        float rmsSum = 0.0f;
        float peak = 0.0f;
        float correlation = 0.0f;
        float transientCount = 0.0f;

        const auto* left = buffer.getReadPointer(0);
        const auto* right = (numChannels > 1) ? buffer.getReadPointer(1) : nullptr;

        float sumL2 = 0.0f;
        float sumR2 = 0.0f;
        float sumLR = 0.0f;

        for (int i = 0; i < numSamples; ++i)
        {
            const float sampleL = left[i];
            const float sampleR = (right != nullptr) ? right[i] : sampleL;

            const float monoSample = 0.5f * (sampleL + sampleR);
            rmsSum += monoSample * monoSample;
            peak = std::max(peak, std::abs(monoSample));

            const float delta = std::abs(monoSample - lastSample);
            if (delta > 0.02f)
                transientCount += 1.0f;
            lastSample = monoSample;

            sumL2 += sampleL * sampleL;
            sumR2 += sampleR * sampleR;
            sumLR += sampleL * sampleR;

            pushNextSample(monoSample);
        }

        if (numChannels > 1 && sumL2 > 0.0f && sumR2 > 0.0f)
            correlation = sumLR / std::sqrt(sumL2 * sumR2);
        else
            correlation = 1.0f;

        const float rms = std::sqrt(rmsSum / static_cast<float>(numSamples));
        const float rmsDb = juce::Decibels::gainToDecibels(rms, -100.0f);
        const float crestDb = (rms > 0.0f) ? juce::Decibels::gainToDecibels(peak / rms) : 0.0f;
        const float transientDensity = transientCount / static_cast<float>(numSamples);

        if (nextFFTReady)
            performFFT();

        const juce::SpinLock::ScopedLockType lock(snapshotLock);
        latestSnapshot.rmsDb = rmsDb;
        latestSnapshot.crestDb = crestDb;
        latestSnapshot.correlation = juce::jlimit(-1.0f, 1.0f, correlation);
        latestSnapshot.transientDensity = transientDensity;
        latestSnapshot.monoMonitoring = monoMonitoring.load();
        updateFeelTags(latestSnapshot);
    }

    AnalysisSnapshot AnalysisEngine::getSnapshot() const
    {
        const juce::SpinLock::ScopedLockType lock(snapshotLock);
        return latestSnapshot;
    }

    void AnalysisEngine::pushNextSample(float sample) noexcept
    {
        fifo[static_cast<size_t>(fifoIndex)] = sample;
        ++fifoIndex;

        if (fifoIndex == fftSize)
        {
            if (! nextFFTReady)
            {
                std::copy(fifo.begin(), fifo.end(), fftData.begin());
                nextFFTReady = true;
            }

            fifoIndex = 0;
        }
    }

    void AnalysisEngine::performFFT()
    {
        window.multiplyWithWindowingTable(fftData.data(), fftSize);
        fft.performFrequencyOnlyForwardTransform(fftData.data());

        std::array<float, kSpectrumBars> bars {};
        const int maxBin = fftSize / 2;

        for (int bar = 0; bar < kSpectrumBars; ++bar)
        {
            const float start = std::pow(static_cast<float>(maxBin), static_cast<float>(bar) / kSpectrumBars);
            const float end = std::pow(static_cast<float>(maxBin), static_cast<float>(bar + 1) / kSpectrumBars);
            const int startBin = juce::jlimit(1, maxBin - 1, static_cast<int>(start));
            const int endBin = juce::jlimit(1, maxBin, static_cast<int>(end));

            float peak = 0.0f;
            for (int i = startBin; i < endBin; ++i)
                peak = std::max(peak, fftData[static_cast<size_t>(i)]);

            const float db = juce::Decibels::gainToDecibels(peak, -100.0f);
            bars[static_cast<size_t>(bar)] = juce::jlimit(0.0f, 1.0f, (db + 100.0f) / 100.0f);
        }

        const juce::SpinLock::ScopedLockType lock(snapshotLock);
        latestSnapshot.spectrumBars = bars;
        nextFFTReady = false;
    }

    void AnalysisEngine::updateFeelTags(AnalysisSnapshot& snapshot) const
    {
        snapshot.feelTags.clear();

        float lowEnergy = 0.0f;
        float highEnergy = 0.0f;
        for (int i = 0; i < kSpectrumBars; ++i)
        {
            const float value = snapshot.spectrumBars[static_cast<size_t>(i)];
            if (i < kSpectrumBars / 3)
                lowEnergy += value;
            else if (i > (kSpectrumBars * 2) / 3)
                highEnergy += value;
        }

        if (highEnergy > lowEnergy * 1.2f)
            snapshot.feelTags.add("Bright");
        if (lowEnergy > highEnergy * 1.2f)
            snapshot.feelTags.add("Warm");
        if (snapshot.crestDb > 6.0f)
            snapshot.feelTags.add("Punchy");
        if (snapshot.transientDensity > 0.05f)
            snapshot.feelTags.add("Snappy");
        if (snapshot.correlation < 0.2f)
            snapshot.feelTags.add("Wide");
        if (snapshot.correlation > 0.8f)
            snapshot.feelTags.add("Focused");
        if (snapshot.feelTags.isEmpty())
            snapshot.feelTags.add("Balanced");
    }
}
