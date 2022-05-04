/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "ValueSlider.h"

//==============================================================================
/**
*/
class SH201PIAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SH201PIAudioProcessorEditor (SH201PIAudioProcessor&);
    ~SH201PIAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.

    ValueSlider         valueSlider{"Detune"};

    //std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> detuneSliderAttachment;

    // this isn't creating an audioProcessor, this is just pointing to the piece of memory that holds the audioProcessor
    SH201PIAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SH201PIAudioProcessorEditor)
};
