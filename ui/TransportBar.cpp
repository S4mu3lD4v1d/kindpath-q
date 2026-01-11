#include "TransportBar.h"

namespace kindpath::ui
{
    TransportBar::TransportBar()
    {
        addAndMakeVisible(loadButton);
        addAndMakeVisible(fileLabel);
        addAndMakeVisible(monoToggle);

        loadButton.onClick = [this]
        {
            if (onLoadFile)
                onLoadFile();
        };

        monoToggle.onClick = [this]
        {
            if (onMonoChanged)
                onMonoChanged(monoToggle.getToggleState());
        };

        fileLabel.setText("No file loaded", juce::dontSendNotification);
        fileLabel.setColour(juce::Label::textColourId, juce::Colours::silver);
        fileLabel.setJustificationType(juce::Justification::centredLeft);
    }

    void TransportBar::setFileName(const juce::String& name)
    {
        const auto labelText = name.isNotEmpty() ? name : "No file loaded";
        fileLabel.setText(labelText, juce::dontSendNotification);
    }

    void TransportBar::setLoadEnabled(bool enabled)
    {
        loadButton.setEnabled(enabled);
    }

    void TransportBar::setMonoEnabled(bool enabled)
    {
        monoToggle.setToggleState(enabled, juce::dontSendNotification);
    }

    void TransportBar::paint(juce::Graphics& g)
    {
        g.fillAll(juce::Colour(0xff15171b));
        g.setColour(juce::Colour(0xff2a2d34));
        g.drawRect(getLocalBounds(), 1);
    }

    void TransportBar::resized()
    {
        auto area = getLocalBounds().reduced(12, 8);
        auto rightArea = area.removeFromRight(120);

        monoToggle.setBounds(rightArea.removeFromRight(80));
        area.removeFromRight(12);
        loadButton.setBounds(area.removeFromLeft(120));
        area.removeFromLeft(12);
        fileLabel.setBounds(area);
    }
}
