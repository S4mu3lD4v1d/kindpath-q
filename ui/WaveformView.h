#pragma once

#include "shared/JuceIncludes.h"

namespace kindpath::ui
{
    class WaveformView : public juce::Component
    {
    public:
        explicit WaveformView(juce::AudioFormatManager& formatManager);

        void loadFile(const juce::File& file);
        void clear();

        void paint(juce::Graphics& g) override;
        void resized() override;

    private:
        juce::AudioThumbnailCache thumbnailCache { 8 };
        juce::AudioThumbnail thumbnail;
        juce::String statusText = "Load audio to see the waveform";
    };
}
