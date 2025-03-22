/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TheMultiTaskerAudioProcessor::TheMultiTaskerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif

    ), LPfilter(juce::dsp::IIR::Coefficients<float>::makeLowPass(44100, 20000.0, 0.1f)), treeState(*this, nullptr, "slider_values", createParameterLayout())
#endif
{
    treeState.addParameterListener("LP", this);

}

TheMultiTaskerAudioProcessor::~TheMultiTaskerAudioProcessor()
{
    treeState.removeParameterListener("LP", this);
}


juce::AudioProcessorValueTreeState::ParameterLayout TheMultiTaskerAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters;

    auto parameterLP = std::make_unique<juce::AudioParameterFloat>("LP", "LowPass", 20.0, 20000.0, 1000.0);

    parameters.push_back(std::move(parameterLP));

    return { parameters.begin(), parameters.end() };


}

void TheMultiTaskerAudioProcessor::parameterChanged(const juce::String& parameterID, float new_parameter_value) {

    if (parameterID == "LowPass") {
        LPcutoffFREQ = new_parameter_value;
    }

}


//==============================================================================
const juce::String TheMultiTaskerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TheMultiTaskerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TheMultiTaskerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool TheMultiTaskerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double TheMultiTaskerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TheMultiTaskerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TheMultiTaskerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TheMultiTaskerAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String TheMultiTaskerAudioProcessor::getProgramName (int index)
{
    return {};
}

void TheMultiTaskerAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}


//==============================================================================
void TheMultiTaskerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    last_sample_rate = sampleRate;

    juce::dsp::ProcessSpec info;
    info.sampleRate = sampleRate;
    info.maximumBlockSize = samplesPerBlock;
    info.numChannels = getTotalNumOutputChannels();
    LPfilter.prepare(info);

    LPfilter.reset();
   
    
}

void TheMultiTaskerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TheMultiTaskerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void TheMultiTaskerAudioProcessor::update_filter() {

    float LPcutoff = *treeState.getRawParameterValue("LP");

    *LPfilter.state = *juce::dsp::IIR::Coefficients<float>::makeLowPass(last_sample_rate, LPcutoff, 0.1f);
}

void TheMultiTaskerAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    juce::dsp::AudioBlock<float> block(buffer);
    update_filter();
    
    LPfilter.process(juce::dsp::ProcessContextReplacing<float>(block));



    

}


//==============================================================================
bool TheMultiTaskerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* TheMultiTaskerAudioProcessor::createEditor()
{
    return new TheMultiTaskerAudioProcessorEditor (*this);
}

//==============================================================================
void TheMultiTaskerAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.

    

}

void TheMultiTaskerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TheMultiTaskerAudioProcessor();
}
