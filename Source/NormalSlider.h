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

        //auto radius = 40.0f;

        if (isEntered)                          // if mouse enters the component..
        {
            /*
            if (mPos)                           // if mouse is on left or right side of the component
            {
                juce::Path lArc;
                lArc.addCentredArc(NormalSlider::getWidth() / 2.0f, (NormalSlider::getHeight() / 2) - (NormalSlider::getHeight() / 10), radius - 20.0f, radius - 20.0f, 0, 3.92699099f, 5.4977875975f, true);
                g.setColour(CustomColours::fRed);
                g.strokePath(lArc, juce::PathStrokeType(2, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
                repaint();
            }
            else
            {
                juce::Path lArc;
                lArc.addCentredArc(NormalSlider::getWidth() / 2.0f, (NormalSlider::getHeight() / 2) - (NormalSlider::getHeight() / 10), radius - 19.0f, radius - 19.0f, 0.0f, 7.0685838525f, 8.63938046f, true);
                g.setColour(CustomColours::fRed);
                g.strokePath(lArc, juce::PathStrokeType(2, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
                repaint();
            }
            */
        }
    }

    void mouseEnter(const juce::MouseEvent& event)
    {
        isEntered = true;
    }
    void mouseMove(const juce::MouseEvent& event)
    {
        int x = event.x;
        x < (getWidth() / 2) ? mPos = true : mPos = false;
    }
    void mouseDown(const juce::MouseEvent& event)
    {
        //event.mods.isMiddleButtonDown() && rDown == true ? rDown = true : juce::Slider::mouseDown(event);

        if (event.mods.isMiddleButtonDown() && rDown == true)
        {
            juce::Slider::mouseDown(event);
        }
        else if (rDown = true)
        {
            juce::Slider::mouseDown(event);
        }
    }
    void mouseDrag(const juce::MouseEvent& event)
    {
        // Let mouse Disapear when adjusting the values.
        event.source.enableUnboundedMouseMovement(true, false);

        // Get start and end angles of the slider in floats.
        float start = getRotaryParameters().startAngleRadians;
        float end = getRotaryParameters().endAngleRadians;

        // get the actual mouse position
        int x = event.position.x;
        int y = event.position.y;

        // get the old mouse position
        int dx = previousX[0] - x;
        int dy = previousY[0] - y;

        // set a base value for mousediff to calculate the distance travelled
        double mouseDiff = 0;

        // Function to let the mouse adjust values. Left/ down = minus  Right/ Up is plus.

        dx < 0 ? mouseDiff = mouseDiff + 1 : mouseDiff = mouseDiff - 1;
        dy < 0 ? mouseDiff = mouseDiff - 1 : mouseDiff = mouseDiff + 1;

        // mouseDiff is used to calculate the right amount of drag for start and end value (Same "feel" as the actual value of the slider)
        float mouseDiffInFloats = mouseDiff * (1.0 / pixelsForFullDragExtent);

        // math for start and end point of the slider, limited
        float newStart = start + mouseDiffInFloats;
        newStart = juce::jlimit((juce::MathConstants<float>::pi * 1.2f), (end - 0.05f), newStart);

        float newEnd = end + mouseDiffInFloats;
        newEnd = juce::jlimit(start + 0.05f, juce::MathConstants<float>::pi * 2.8f, newEnd);

        // New code to calculate the new start/ end value to set in in a new range.

        double minVal = getMinimum();
        double maxVal = getMaximum();

        double newMinVal = round(minVal + (mouseDiff * 0.51));
        newMinVal = juce::jlimit((double)0, (double)127, newMinVal);
        //juce::NormalisableRange<double> snapToLegalValue(double newMinVal);

        double newMaxVal = round(maxVal + mouseDiff * 0.51);
        newMaxVal = juce::jlimit((double)0, (double)127, newMaxVal);

        // set the parameters and see the magic happen
        if (event.mods.isMiddleButtonDown())                                 // if right mouse button is down    [1]
        {
            if (mPos)                                                       // if mouse is on left side of the component. [1a]
            {
                setRotaryParameters(newStart, end, true);
                setRange(newMinVal, maxVal, 1);
                setValue((newMinVal + maxVal) / 2);
            }
            else                                                            // if mouse is on right side of the component. [1b]
            {
                setRotaryParameters(start, newEnd, true);
                setRange(minVal, newMaxVal, 1);
                setValue((newMinVal + maxVal) / 2);
            }
        }
        else                                                               // let blocked mouseEvent of left mouse button go through [2]
        {
            juce::Slider::mouseDrag(event);
        }

        // set the the actual mouseposition to compare them again when the mouse is moved.
        previousX[0] = x;
        previousY[0] = y;
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

