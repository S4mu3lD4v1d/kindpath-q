#include "WaveformView.h"

namespace kindpath::ui
{
    WaveformView::WaveformView(juce::AudioFormatManager& formatManager)
        : thumbnail(512, formatManager, thumbnailCache)
    {
    }

    void WaveformView::loadFile(const juce::File& file)
    {
        if (! file.existsAsFile())
        {
            statusText = "File not found";
            repaint();
            return;
        }

        thumbnail.setSource(new juce::FileInputSource(file));
        statusText = file.getFileName();
        repaint();
    }

    void WaveformView::clear()
    {
        thumbnail.clear();
        statusText = "Load audio to see the waveform";
        repaint();
    }

    void WaveformView::paint(juce::Graphics& g)
    {
        g.fillAll(juce::Colour(0xff0f1115));
        g.setColour(juce::Colour(0xff23262d));
        g.drawRect(getLocalBounds(), 1);

        if (thumbnail.getTotalLength() > 0.0)
        {
            g.setColour(juce::Colour(0xff7ed0ff));
            thumbnail.drawChannels(g, getLocalBounds().reduced(8), 0.0, thumbnail.getTotalLength(), 1.0f);
        }
        else
        {
            g.setColour(juce::Colours::grey);
            g.setFont(15.0f);
            g.drawFittedText(statusText, getLocalBounds().reduced(12), juce::Justification::centred, 2);
        }
    }

    void WaveformView::resized()
    {
    }
}
