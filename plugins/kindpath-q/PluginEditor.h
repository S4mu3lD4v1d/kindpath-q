#pragma once

#include "shared/JuceIncludes.h"
#include "PluginProcessor.h"
#include "ui/KindPathMainComponent.h"
#include "core/education/EducationCards.h"

class KindPathQAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    explicit KindPathQAudioProcessorEditor(KindPathQAudioProcessor&);
    ~KindPathQAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    void loadEducationDeck();

    KindPathQAudioProcessor& audioProcessor;
    kindpath::education::EducationDeck deck;
    kindpath::ui::KindPathMainComponent mainView;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(KindPathQAudioProcessorEditor)
};
