#pragma once

#include "shared/JuceIncludes.h"
#include "core/analysis/AnalysisEngine.h"

class KindPathQAudioProcessor : public juce::AudioProcessor
{
public:
    KindPathQAudioProcessor();
    ~KindPathQAudioProcessor() override;

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;

    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void changeProgramName(int index, const juce::String& newName) override;

    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    kindpath::analysis::AnalysisEngine& getAnalysisEngine() { return analysisEngine; }

private:
    kindpath::analysis::AnalysisEngine analysisEngine;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(KindPathQAudioProcessor)
};
