#pragma once

#include "shared/JuceIncludes.h"

namespace kindpath::dsp
{
    template <typename FloatType>
    inline void collapseToMono(juce::AudioBuffer<FloatType>& buffer)
    {
        const int numChannels = buffer.getNumChannels();
        if (numChannels < 2)
            return;

        const int numSamples = buffer.getNumSamples();
        auto* left = buffer.getWritePointer(0);
        auto* right = buffer.getWritePointer(1);

        for (int i = 0; i < numSamples; ++i)
        {
            const FloatType mono = static_cast<FloatType>(0.5) * (left[i] + right[i]);
            left[i] = mono;
            right[i] = mono;
        }

        for (int ch = 2; ch < numChannels; ++ch)
            buffer.clear(ch, 0, numSamples);
    }
}
