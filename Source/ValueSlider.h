/*  ==============================================================================
    ValueSlider.h Created: 3 Apr 2022 11:59:17pm Author:  Tedjuh
  ==============================================================================
*/

#pragma once

#include<JuceHeader.h>
#include"NormalSlider.h"
#include"ValueBox.h"
#include"CustomColours.h"


class ValueSlider : public juce::Component,
                    public juce::Slider::Listener
{
public:

    ValueSlider(const juce::String& slidName)   :   sliderName(slidName)
    {
        //  This is the round slider
        addAndMakeVisible(vSlider);

        //  This is the minimum value slider
        addAndMakeVisible(minValBox);
        minValBox.setRange(0, 122, 1);
        minValBox.setValue(0);
        minValBox.addListener(this);

        // This is the maximum value slider
        addAndMakeVisible(maxValBox);
        maxValBox.setRange(5, 127, 1);
        maxValBox.setValue(127);
        maxValBox.addListener(this);
    }
    
    ~ValueSlider() {}

    void resized()
    { 
        vSlider.setBounds(0, 0, getWidth(), getWidth());
       minValBox.setBounds(getWidth() * 0.0625, getWidth() * 0.7875, getWidth() * 0.375, getWidth() * 0.2125);
       maxValBox.setBounds(getWidth() * 0.5625, getWidth() * 0.7875, getWidth() * 0.375, getWidth() * 0.2125);
     }

    void paintOverChildren(juce::Graphics& g)
    {
        // need to use paintOverChildren because the parentComponent is the one on the bottom.. 
        // every childcomponent gets added on top. So to display text from the parent on top.. use paintoverchildren.

        juce::Font normFont("CobaltItalien", 10.0f, juce::Font::plain);

        g.setColour(CustomColours::white);
        g.setFont(normFont);
        g.setFont(12.0f);
        g.drawText(sliderName, 0, getHeight() / 2.7f, getWidth(), getHeight() / 6.0f, juce::Justification::centred, false);
     }

    void sliderValueChanged(juce::Slider* slider) override
    {
        double minVal       = minValBox.getValue();
        double maxVal       = maxValBox.getValue();

        float start = juce::MathConstants<float>::pi * 1.2f;
        float end = juce::MathConstants<float>::pi * 2.8f;

        float diff = (end - start) / 127;

        float newStart = start + (diff * minValBox.getValue());
        float newEnd =  start + (diff * maxValBox.getValue());

        // set start Angle by dragging the minimum valuebox
        if (slider == &minValBox)
        {
            

            vSlider.setRotaryParameters(newStart, newEnd, true);
            vSlider.setRange(minValBox.getValue(), maxValBox.getValue(), true);
            repaint();
        }

        // set end Angle by dragging the maximum valuebox
        if (slider == &maxValBox)
        {
            vSlider.setRotaryParameters(newStart, newEnd, true);
            vSlider.setRange(minValBox.getValue(), maxValBox.getValue(), true);
            repaint();
        }
    }
            
private:

    const juce::String    sliderName;
    NormalSlider    vSlider;
    ValueBox        minValBox;
    ValueBox        maxValBox;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ValueSlider)
};