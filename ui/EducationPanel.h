#pragma once

#include "shared/JuceIncludes.h"
#include "../core/education/EducationCards.h"

namespace kindpath::ui
{
    class EducationPanel : public juce::Component
    {
    public:
        EducationPanel();

        void setDeck(kindpath::education::EducationDeck* deckToUse);

        void paint(juce::Graphics& g) override;
        void resized() override;

    private:
        void showNextCard();

        kindpath::education::EducationDeck* deck = nullptr;
        int cardIndex = 0;
        kindpath::education::EducationCard currentCard;
        bool showDetails = false;

        juce::TextButton revealButton { "Why it feels good" };
    };
}
