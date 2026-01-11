#pragma once

#include "shared/JuceIncludes.h"

namespace kindpath::ui
{
    class TransportBar : public juce::Component
    {
    public:
        TransportBar();

        void setFileName(const juce::String& name);
        void setLoadEnabled(bool enabled);
        void setMonoEnabled(bool enabled);

        std::function<void()> onLoadFile;
        std::function<void(bool)> onMonoChanged;

        void paint(juce::Graphics& g) override;
        void resized() override;

    private:
        juce::TextButton loadButton { "Load Audio" };
        juce::Label fileLabel;
        juce::ToggleButton monoToggle { "MONO" };
    };
}
