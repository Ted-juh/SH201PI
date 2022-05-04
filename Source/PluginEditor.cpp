/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SH201PIAudioProcessorEditor::SH201PIAudioProcessorEditor (SH201PIAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    

    addAndMakeVisible(valueSlider);
    
    
    //detuneSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DETUNE", valueSlider);

    setSize(250, 250);
}

SH201PIAudioProcessorEditor::~SH201PIAudioProcessorEditor()
{
}

//==============================================================================
void SH201PIAudioProcessorEditor::paint (juce::Graphics& g)
{
    auto mainCompBounds = getLocalBounds();

    g.fillAll(CustomColours::backgr);

    // is the big rectangle around the knobs, see it as a group.    
    auto lf01SectSize = juce::Rectangle <float>(7, 7, 350, 270);
    g.setColour(juce::Colour(0xFF484e52));
    g.fillRect(7, 7, 250, 340);

}

void SH201PIAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    valueSlider.setBounds(10, 10, 100, 100);
}


