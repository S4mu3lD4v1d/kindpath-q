#pragma once

#include "shared/JuceIncludes.h"
#include "../core/analysis/AnalysisEngine.h"

namespace kindpath::ui
{
    class AnalysisPanel : public juce::Component
    {
    public:
        AnalysisPanel();

        void setSnapshot(const kindpath::analysis::AnalysisSnapshot& snapshot);

        void paint(juce::Graphics& g) override;
        void resized() override;

    private:
        kindpath::analysis::AnalysisSnapshot currentSnapshot;
    };
}
