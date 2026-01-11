#pragma once

#include "shared/JuceIncludes.h"

namespace kindpath::education
{
    struct EducationCard
    {
        juce::String title;
        juce::String summary;
        juce::String details;
        juce::StringArray links;
    };

    class EducationDeck
    {
    public:
        EducationDeck() = default;

        bool loadFromJsonString(const juce::String& jsonString, juce::String& errorMessage);
        bool loadFromFile(const juce::File& file, juce::String& errorMessage);

        int getNumCards() const noexcept;
        EducationCard getCard(int index) const;

    private:
        std::vector<EducationCard> cards;
    };
}
