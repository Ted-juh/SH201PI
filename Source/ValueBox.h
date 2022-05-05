/*  ==============================================================================
    ValueBox.h Created: 3 Apr 2022 6:56:05pm Author:  Tedjuh
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class ValueBox : public juce::Slider, public juce::LookAndFeel_V4
{
public:
    ValueBox()
    {
        setSliderStyle(juce::Slider::LinearBarVertical);
        setTextBoxIsEditable(false);
        setVelocityBasedMode(true);
        setVelocityModeParameters(0.5, 1, 0.09, false);
        setWantsKeyboardFocus(true);
        setNumDecimalPlacesToDisplay(0);
    }

    ~ValueBox()
    {
        setLookAndFeel(nullptr);
    }

    void paint(juce::Graphics& g)
    {
        
        if (isEntered)
        {
            g.fillAll(juce::Colour(0x50FF0000));
            repaint();
        }
        else
        {
            g.fillAll(juce::Colour(0x20FFFFFF));
            repaint();
        }
    }

    void mouseEnter(const juce::MouseEvent& event)
    {
        isEntered = true;
    }

    void mouseDown(const juce::MouseEvent& event)
    {
        juce::Slider::mouseDown(event);
        setMouseCursor(juce::MouseCursor::NoCursor);
    }

    void mouseUp(const juce::MouseEvent& event)
    {
        juce::Slider::mouseUp(event);
        juce::Desktop::getInstance().getMainMouseSource().setScreenPosition(event.source.getLastMouseDownPosition());
        setMouseCursor(juce::MouseCursor::NormalCursor);
    }

    void mouseExit(const juce::MouseEvent& event)
    {
        isEntered = false;
    }

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

    bool isEntered = false;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ValueBox)
};