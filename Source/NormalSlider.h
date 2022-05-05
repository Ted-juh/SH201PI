/*
  ==============================================================================
    Slider.h Created: 5 Mar 2022 11:23:15am Author:  Tedjuh
  ==============================================================================
*/

#pragma once

#include <juceHeader.h>
#include "CustomColours.h"
#include "NormalSliderLF.h"

class NormalSlider : public juce::Slider
{
public:
    NormalSlider()
    {
        setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
        setLookAndFeel(&normalSliderLF);
        setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
        setRotaryParameters(juce::MathConstants<float>::pi * 1.2f, juce::MathConstants<float>::pi * 2.8f, true);
        setRange(0, 127, 1);
        setDoubleClickReturnValue(true, 0);        
}

    ~NormalSlider()
    {
        setLookAndFeel(nullptr);
    }

    void paint(juce::Graphics& g)
    {
        juce::Slider::paint(g);
        if (isEntered) {}
    }

    void mouseEnter(const juce::MouseEvent& event)
    {
        isEntered = true;
    }

    void mouseMove(const juce::MouseEvent& event)
    {    
    }

    void mouseDown(const juce::MouseEvent& event)
    {
        if (rDown = true)
        {
            juce::Slider::mouseDown(event);
        }
    }
    void mouseDrag(const juce::MouseEvent& event)
    {
        // Get start and end angles of the slider in floats.
        float start = getRotaryParameters().startAngleRadians;
        float end = getRotaryParameters().endAngleRadians;

        juce::Slider::mouseDrag(event);
    }
        
    void mouseExit(const juce::MouseEvent& event)
    {
        isEntered = false;
    }

    bool rDown{ false };
    bool isEntered{ false };
    bool mPos{ false };

private:

    NormalSliderLF normalSliderLF;
    int pixelsForFullDragExtent = 50;
    int previousX[1] = {};
    int previousY[1] = {};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NormalSlider)
};

