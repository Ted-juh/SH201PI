/*  ==============================================================================
    This file contains the basic framework code for a JUCE plugin processor.
  ==============================================================================
*/
#include "PluginProcessor.h"
#include "PluginEditor.h"
//==============================================================================
SH201PIAudioProcessor::SH201PIAudioProcessor()

// this is an initialiser list, it initializes everything in the list (doh)
#ifndef JucePlugin_PreferredChannelConfigurations 
        : AudioProcessor(BusesProperties()

#if ! JucePlugin_IsMidiEffect

#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
    ), apvts(*this, nullptr, "Parameters", createParameters())
    // this points to the class I'm in right now. * is to de-reference.
    // createParameters() points to the parameterLayout (See the function parameterLayout)
#endif
{
}

SH201PIAudioProcessor::~SH201PIAudioProcessor()
{
}
//==============================================================================
const juce::String SH201PIAudioProcessor::getName() const
{
    return JucePlugin_Name;
}
bool SH201PIAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}
bool SH201PIAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}
bool SH201PIAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}
double SH201PIAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}
int SH201PIAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}
int SH201PIAudioProcessor::getCurrentProgram()
{
    return 0;
}
void SH201PIAudioProcessor::setCurrentProgram (int index)
{
}
const juce::String SH201PIAudioProcessor::getProgramName (int index)
{
    return {};
}
void SH201PIAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}
//==============================================================================
void SH201PIAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}
void SH201PIAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}
#ifndef JucePlugin_PreferredChannelConfigurations
bool SH201PIAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif
void SH201PIAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
}
//==============================================================================
bool SH201PIAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}
juce::AudioProcessorEditor* SH201PIAudioProcessor::createEditor()
{
    return new SH201PIAudioProcessorEditor (*this);
}
//==============================================================================
void SH201PIAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}
void SH201PIAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}
//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SH201PIAudioProcessor();
}

// this is the function for creating a return type for createParameters.
juce::AudioProcessorValueTreeState::ParameterLayout SH201PIAudioProcessor::createParameters()
{
    // this is a list (vector) of "ranged parameters" named params. SEE RANGEDPARAMETERS CLASS
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    // this puts an element at the end of the list (vector)
    // std::make_unique creates a block of memory to hold the parameters.
     params.push_back(std::make_unique < juce::AudioParameterFloat>("DETUNE", "Detune", 0.f, 127.f, 0.f));

    //return the list (vector)
    return{ params.begin(), params.end() };

}
