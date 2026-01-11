#include "EducationCards.h"

namespace kindpath::education
{
    static EducationCard cardFromVar(const juce::var& value)
    {
        EducationCard card;
        if (! value.isObject())
            return card;

        auto* obj = value.getDynamicObject();
        card.title = obj->getProperty("title").toString();
        card.summary = obj->getProperty("summary").toString();
        card.details = obj->getProperty("details").toString();

        const auto linksVar = obj->getProperty("links");
        if (auto* linksArray = linksVar.getArray())
        {
            for (const auto& link : *linksArray)
                card.links.add(link.toString());
        }

        return card;
    }

    bool EducationDeck::loadFromJsonString(const juce::String& jsonString, juce::String& errorMessage)
    {
        juce::var parsed;
        auto result = juce::JSON::parse(jsonString, parsed);
        if (result.failed())
        {
            errorMessage = result.getErrorMessage();
            return false;
        }

        if (! parsed.isArray())
        {
            errorMessage = errorMessage.isEmpty() ? "Expected a JSON array of cards" : errorMessage;
            return false;
        }

        cards.clear();
        auto* array = parsed.getArray();
        for (const auto& entry : *array)
            cards.push_back(cardFromVar(entry));

        return ! cards.empty();
    }

    bool EducationDeck::loadFromFile(const juce::File& file, juce::String& errorMessage)
    {
        if (! file.existsAsFile())
        {
            errorMessage = "Cards file not found: " + file.getFullPathName();
            return false;
        }

        const auto jsonText = file.loadFileAsString();
        return loadFromJsonString(jsonText, errorMessage);
    }

    int EducationDeck::getNumCards() const noexcept
    {
        return static_cast<int>(cards.size());
    }

    EducationCard EducationDeck::getCard(int index) const
    {
        if (cards.empty())
            return {};

        const auto safeIndex = static_cast<size_t>(index % static_cast<int>(cards.size()));
        return cards[safeIndex];
    }
}
