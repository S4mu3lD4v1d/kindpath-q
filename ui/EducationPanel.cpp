#include "EducationPanel.h"

namespace kindpath::ui
{
    EducationPanel::EducationPanel()
    {
        addAndMakeVisible(revealButton);
        revealButton.onClick = [this]
        {
            showNextCard();
            repaint();
        };
    }

    void EducationPanel::setDeck(kindpath::education::EducationDeck* deckToUse)
    {
        deck = deckToUse;
        cardIndex = 0;
        showDetails = false;
        if (deck != nullptr && deck->getNumCards() > 0)
            currentCard = deck->getCard(cardIndex);
        repaint();
    }

    void EducationPanel::showNextCard()
    {
        if (deck == nullptr || deck->getNumCards() == 0)
            return;

        cardIndex = (cardIndex + 1) % deck->getNumCards();
        currentCard = deck->getCard(cardIndex);
        showDetails = true;
    }

    void EducationPanel::paint(juce::Graphics& g)
    {
        g.fillAll(juce::Colour(0xff10141a));
        g.setColour(juce::Colour(0xff2f3440));
        g.drawRect(getLocalBounds(), 1);

        auto area = getLocalBounds().reduced(10);
        area.removeFromTop(32);

        g.setColour(juce::Colours::white);
        g.setFont(15.0f);
        g.drawText(currentCard.title.isNotEmpty() ? currentCard.title : "Did you know?", area.removeFromTop(20), juce::Justification::left, false);

        g.setColour(juce::Colours::silver);
        g.setFont(12.5f);
        g.drawFittedText(currentCard.summary.isNotEmpty() ? currentCard.summary : "Click the button to rotate a card.", area.removeFromTop(40), juce::Justification::left, 2);

        if (showDetails)
        {
            g.setColour(juce::Colour(0xffcbd5f5));
            g.drawFittedText(currentCard.details, area.removeFromTop(80), juce::Justification::left, 4);

            if (! currentCard.links.isEmpty())
            {
                area.removeFromTop(4);
                g.setColour(juce::Colour(0xff8aa4ff));
                g.drawText("Links: " + currentCard.links.joinIntoString(", "), area.removeFromTop(18), juce::Justification::left, false);
            }
        }
    }

    void EducationPanel::resized()
    {
        auto area = getLocalBounds().reduced(10);
        revealButton.setBounds(area.removeFromTop(26));
    }
}
