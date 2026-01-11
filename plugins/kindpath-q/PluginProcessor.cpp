#include "PluginProcessor.h"
#include "PluginEditor.h"

KindPathQAudioProcessor::KindPathQAudioProcessor()
    : AudioProcessor(BusesProperties().withInput("Input", juce::AudioChannelSet::stereo(), true)
                                       .withOutput("Output", juce::AudioChannelSet::stereo(), true))
{
}

KindPathQAudioProcessor::~KindPathQAudioProcessor() = default;

const juce::String KindPathQAudioProcessor::getName() const
{
    return "KindPath Q";
}

bool KindPathQAudioProcessor::acceptsMidi() const
{
    return false;
}

bool KindPathQAudioProcessor::producesMidi() const
{
    return false;
}

bool KindPathQAudioProcessor::isMidiEffect() const
{
    return false;
}

double KindPathQAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int KindPathQAudioProcessor::getNumPrograms()
{
    return 1;
}

int KindPathQAudioProcessor::getCurrentProgram()
{
    return 0;
}

void KindPathQAudioProcessor::setCurrentProgram(int)
{
}

const juce::String KindPathQAudioProcessor::getProgramName(int)
{
    return {};
}

void KindPathQAudioProcessor::changeProgramName(int, const juce::String&)
{
}

void KindPathQAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    analysisEngine.prepare(sampleRate, samplesPerBlock, getTotalNumInputChannels());
}

void KindPathQAudioProcessor::releaseResources()
{
}

bool KindPathQAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    const auto mainOut = layouts.getMainOutputChannelSet();
    if (mainOut != juce::AudioChannelSet::mono() && mainOut != juce::AudioChannelSet::stereo())
        return false;

    return layouts.getMainInputChannelSet() == mainOut;
}

void KindPathQAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;

    for (int ch = getTotalNumInputChannels(); ch < getTotalNumOutputChannels(); ++ch)
        buffer.clear(ch, 0, buffer.getNumSamples());

    analysisEngine.processBlock(buffer);
}

bool KindPathQAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* KindPathQAudioProcessor::createEditor()
{
    return new KindPathQAudioProcessorEditor(*this);
}

void KindPathQAudioProcessor::getStateInformation(juce::MemoryBlock&)
{
}

void KindPathQAudioProcessor::setStateInformation(const void*, int)
{
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new KindPathQAudioProcessor();
}
