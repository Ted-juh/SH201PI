/*  ==============================================================================
    CustomLookAndFeel.h Created: 5 Mar 2022 11:22:37am Author:  Tedjuh
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "CustomColours.h"

class NormalSliderLF : public juce::Component, public juce::LookAndFeel_V4
{
public:

    NormalSliderLF(){};
    ~NormalSliderLF() {};

    juce::Slider::SliderLayout getSliderLayout(juce::Slider & slider)
        {
            auto localBounds = slider.getLocalBounds();

            juce::Slider::SliderLayout layout;

            layout.textBoxBounds = localBounds.withY(-18);  //placement of label
            layout.sliderBounds = localBounds;

            return layout;
        };

    void drawRotarySlider(juce::Graphics & g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, juce::Slider & slider) override
        {
            auto bounds = juce::Rectangle <float>(x, y, width, height);
            auto buttonBounds = juce::Rectangle<float>(x + 2.0f, y, width - 2.0f, height - 2.0f);        // 5, 0, 60, 60, leaving space for the label at the bottom.
            auto buttonHeight = bounds.getHeight();
            auto buttonCentreX = bounds.getWidth() / 2;                                                     // should be 30 or 30 + 5 = 35
            auto buttonCentreY = (bounds.getHeight() / 2) - (buttonHeight / 10.0f);
            auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);      // 3,75 + (sliderPos * (8,4 - 3,75))    Takes start of angle and adds (sliderposition * 4,7) 

            //----------------------------------------------------------------------------------------------------------
            // Background arc = ok.

            auto arcDiam1 = buttonHeight * 0.75f;
            auto radius1 = arcDiam1 / 2;
            auto arcWidth = arcDiam1 / 15;

            //-----------------------------------------------------------------------------------------------------------------------
            //Background of ValueArc = ok.

            juce::Path backGroundArc;
            backGroundArc.addCentredArc(buttonCentreX, buttonCentreY, radius1, radius1, 0.0f, rotaryStartAngle, rotaryEndAngle, true);
            g.setColour(CustomColours::fRed);
            g.strokePath(backGroundArc, juce::PathStrokeType(arcWidth, juce::PathStrokeType::curved, juce::PathStrokeType::butt));

            //-----------------------------------------------------------------------------------------------------------------------
            //ValueArc = ok.

            juce::Path valueArc;
            valueArc.addCentredArc(buttonCentreX, buttonCentreY, radius1, radius1, 0.0f, rotaryStartAngle, toAngle, true);
            g.setColour(CustomColours::red);
            g.strokePath(valueArc, juce::PathStrokeType(arcWidth, juce::PathStrokeType::curved, juce::PathStrokeType::butt));

            //-----------------------------------------------------------------------------------------------------------------------
            // OuterCircle = ok

            // setup for the gradient:
            juce::Point<float> bottomLeft{ 40, 40 };
            juce::Point<float> topRight{ 60,20 };
            juce::ColourGradient sSilver(CustomColours::dSilver, bottomLeft, CustomColours::lSilver, topRight, false);

            auto arcDiam2 = buttonHeight * 0.63f;
            auto radius2 = arcDiam2 / 2;
            auto arcWidth2 = arcDiam2 / 7;

            juce::Path outerCirc;
            outerCirc.addCentredArc(buttonCentreX, buttonCentreY, radius2, radius2, 0.0f, 0, 2 * juce::MathConstants<float>::pi, true);
            g.setGradientFill(sSilver);
            g.strokePath(outerCirc, juce::PathStrokeType(arcWidth2, juce::PathStrokeType::curved, juce::PathStrokeType::butt));

            //--------------------------------------------------------------------------------------------------------
            // Drawing of InnerCircle

            juce::ColourGradient sRed(CustomColours::dRed, bottomLeft, CustomColours::lRed, topRight, false);

            auto arcDiam3 = buttonHeight * 0.55f;
            auto innerRingCircDistX = buttonCentreX - (arcDiam3 / 2);
            auto innerRingCircDistY = buttonCentreX - (arcDiam3 / 2) - (buttonHeight / 10);

            juce::Path innerCirc;
            innerCirc.addEllipse(innerRingCircDistX, innerRingCircDistY, arcDiam3, arcDiam3);
            g.setGradientFill(sRed);
            g.fillPath(juce::Path(innerCirc), juce::AffineTransform());

            //--------------------------------------------------------------------------------------------------------
            // Drawing of value pointer on Outer Circle (pointles, pun intended, but to give an extra sense of motion to the outer ring.

            juce::Path valPointer;
            valPointer.addEllipse(0, -radius1 * 0.86f, 3.0f, radius1 * 0.12f);
            g.setColour(CustomColours::red);
            g.fillPath(juce::Path(valPointer), juce::AffineTransform::rotation(toAngle).translated(buttonCentreX, buttonCentreY));

            // set name of the slider, takes name of component which is taken from the name that is given by doing "addAndMakeVisible" in the MainComponent.cpp.
            juce::Font normFont("CobaltItalien", 10.0f, juce::Font::plain);

            const juce::String slName = getName();
            
            g.setColour(CustomColours::white); 
            g.setFont(normFont);
            g.setFont(12.0f);
            g.drawText(slName, 0, buttonHeight / 2.7f, width, buttonHeight / 6.0f, juce::Justification::centred, false);
            //g.drawText(name, 0, buttonHeight / 2.7f, width, buttonHeight / 6.0f, juce::Justification::centred, false);

        }

    juce::Label* createSliderTextBox(juce::Slider & slider)
        {
            auto* l = new juce::Label();
            
            l->setJustificationType(juce::Justification::centred);
            l->setColour(juce::Label::textColourId, CustomColours::white);
            l->setColour(juce::Label::textWhenEditingColourId, slider.findColour(juce::Slider::textBoxTextColourId));
            l->setColour(juce::Label::outlineWhenEditingColourId, juce::Colours::black);
            l->setInterceptsMouseClicks(false, false);
             l->setFont(13.0f);
 
            return l;
        }
    
private:
    //ValueSlider valSlider;

    //JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NormalSliderLF)
};
