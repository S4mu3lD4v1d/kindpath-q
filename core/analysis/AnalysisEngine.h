#pragma once

#include "shared/JuceIncludes.h"

namespace kindpath::analysis
{
    constexpr int kSpectrumBars = 32;

    struct AnalysisSnapshot
    {
        std::array<float, kSpectrumBars> spectrumBars {};
        float rmsDb = -100.0f;
        float crestDb = 0.0f;
        float correlation = 0.0f;
        float transientDensity = 0.0f;
        bool monoMonitoring = false;
        juce::StringArray feelTags;
    };

    class AnalysisEngine
    {
    public:
        AnalysisEngine();

        void prepare(double sampleRate, int blockSize, int numChannels);
        void reset();

        void setMonoMonitoring(bool enabled);
        bool getMonoMonitoring() const noexcept;

        void processBlock(juce::AudioBuffer<float>& buffer);
        AnalysisSnapshot getSnapshot() const;

    private:
        void pushNextSample(float sample) noexcept;
        void performFFT();
        void updateFeelTags(AnalysisSnapshot& snapshot) const;

        static constexpr int fftOrder = 11;
        static constexpr int fftSize = 1 << fftOrder;

        juce::dsp::FFT fft;
        juce::dsp::WindowingFunction<float> window;

        std::array<float, fftSize> fifo {};
        std::array<float, fftSize * 2> fftData {};
        int fifoIndex = 0;
        bool nextFFTReady = false;

        double currentSampleRate = 44100.0;
        int expectedBlockSize = 512;
        int expectedChannels = 2;

        std::atomic<bool> monoMonitoring { false };

        mutable juce::SpinLock snapshotLock;
        AnalysisSnapshot latestSnapshot;

        float lastSample = 0.0f;
    };
}
