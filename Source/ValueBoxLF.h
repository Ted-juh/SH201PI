/*  ==============================================================================
    ValueBoxLF.h Created: 3 Apr 2022 6:56:29pm Author:  Tedjuh
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class ValueBoxLF : public juce::LookAndFeel_V4
{
public:
    ValueBoxLF() {};
    ~ValueBoxLF() {};

    void Paint(juce::Graphics& g) {}

    juce::Label* createSliderTextBox(juce::Slider& slider) override
    {
        auto* l = new juce::Label();
        l->setJustificationType(juce::Justification::centred);
        l->setColour(juce::Label::textColourId, slider.findColour(juce::Slider::textBoxTextColourId));
        l->setColour(juce::Label::textWhenEditingColourId, slider.findColour(juce::Slider::textBoxTextColourId));
        l->setColour(juce::Label::outlineWhenEditingColourId, slider.findColour(juce::Slider::textBoxOutlineColourId));
        l->setFont(14);

        return l;
    }

private:

};
