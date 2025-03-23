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
    treeState.addParameterListener("HP", this);
    treeState.addParameterListener("HPr", this);
    treeState.addParameterListener("LPr", this);
    treeState.addParameterListener("toggleLP", this);
    treeState.addParameterListener("toggleHP", this);
    treeState.addParameterListener("toggleGain", this);
    
    treeState.addParameterListener("toggleReverb", this);
    treeState.addParameterListener("toggleDelay", this);
    treeState.addParameterListener("toggleSaturation", this);

    treeState.addParameterListener("gain", this);
    treeState.addParameterListener("reverbRoomSize", this);

}

TheMultiTaskerAudioProcessor::~TheMultiTaskerAudioProcessor()
{
    treeState.removeParameterListener("LP", this);
    treeState.removeParameterListener("LPr", this);
    treeState.removeParameterListener("HP", this);
    treeState.removeParameterListener("HPr", this);
    treeState.removeParameterListener("toggleLP", this);
    treeState.removeParameterListener("toggleHP", this);
    treeState.removeParameterListener("gain", this);
    treeState.removeParameterListener("reverbRoomSize", this);
    treeState.removeParameterListener("toggleGain", this);

    treeState.removeParameterListener("toggleReverb", this);
    treeState.removeParameterListener("toggleDelay", this);
    treeState.removeParameterListener("toggleSaturation", this);

}   


juce::AudioProcessorValueTreeState::ParameterLayout TheMultiTaskerAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters;

    auto parameterLP = std::make_unique<juce::AudioParameterFloat>("LP", "LowPass", 20.0, 20000.0, 20000.0);
    auto parameterLPr = std::make_unique<juce::AudioParameterFloat>("LPr", "LowPassResonance", 0.1, 100.0, 0.1);
    auto parameterHP = std::make_unique<juce::AudioParameterFloat>("HP", "HighPass", 20.0, 20000.0, 20.0);
    auto parameterHPr = std::make_unique<juce::AudioParameterFloat>("HPr", "HighPassResonance", 0.1, 100.0, 0.1);

    auto parameterToggleLP = std::make_unique<juce::AudioParameterBool>("toggleLP", "toggleLowPass",  false);
    auto parameterToggleHP = std::make_unique<juce::AudioParameterBool>("toggleHP", "toggleHighPass", false);
    auto parameterToggleGain = std::make_unique<juce::AudioParameterBool>("toggleGain", "ToggleGain", false);

    auto parameterToggleReverb = std::make_unique<juce::AudioParameterBool>("toggleReverb", "ToggleReverb", false);
    auto parameterToggleDelay = std::make_unique<juce::AudioParameterBool>("toggleDelay", "ToggleDelay", false);
    auto parameterToggleSaturation = std::make_unique<juce::AudioParameterBool>("toggleSaturation", "ToggleSaturation", false);

    auto parameterGain = std::make_unique<juce::AudioParameterFloat>("gain", "Gain", -24, 24, 0.0);
    auto parameterReverbRoomSize = std::make_unique<juce::AudioParameterFloat>("reverbRoomSize", "ReverbRoomSize", 0.0, 1, 0.0);

    parameters.push_back(std::move(parameterLP));
    parameters.push_back(std::move(parameterLPr));
    parameters.push_back(std::move(parameterHP));
    parameters.push_back(std::move(parameterHPr));
    parameters.push_back(std::move(parameterToggleLP));
    parameters.push_back(std::move(parameterToggleHP));
    parameters.push_back(std::move(parameterGain));
    parameters.push_back(std::move(parameterReverbRoomSize));
    parameters.push_back(std::move(parameterToggleGain));

    parameters.push_back(std::move(parameterToggleReverb));
    parameters.push_back(std::move(parameterToggleDelay));
    parameters.push_back(std::move(parameterToggleSaturation));


    return { parameters.begin(), parameters.end() };


}
void TheMultiTaskerAudioProcessor::parameterChanged(const juce::String& parameterID, float newValue) {

    if (parameterID == "LP")
    {
      //  LPcutoff = newValue;


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

    juce::dsp::Reverb::Parameters params;
  

    params.roomSize = reverbRoomSize;
    params.damping = 0.5f;
    params.wetLevel = 0.4f;
    params.dryLevel = 0.8f;
    params.width = 1.0f;
    params.freezeMode = 0.0f;
    params.width = 0.0f;
    ReverbEffect.setParameters(params);

    last_sample_rate = sampleRate;

    juce::dsp::ProcessSpec info;
    info.sampleRate = sampleRate;
    info.maximumBlockSize = samplesPerBlock;
    info.numChannels = getTotalNumOutputChannels();
    LPfilter.prepare(info);
    HPfilter.prepare(info);


  //  ReverbEffect.prepare({ sampleRate, (juce::uint32)samplesPerBlock, 2 });


    LPfilter.reset();
    HPfilter.reset();
    ReverbEffect.reset();
   
    
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

    LPcutoff = *treeState.getRawParameterValue("LP");
    LPresonance = *treeState.getRawParameterValue("LPr");
    HPresonance = *treeState.getRawParameterValue("HPr");
    HPcutoff = *treeState.getRawParameterValue("HP");

    toggleLP = *treeState.getRawParameterValue("toggleLP");
    toggleHP = *treeState.getRawParameterValue("toggleHP");
    toggleGain = *treeState.getRawParameterValue("toggleGain");

    toggleReverb = *treeState.getRawParameterValue("toggleReverb");
    toggleDelay= *treeState.getRawParameterValue("toggleDelay");
    toggleSaturation = *treeState.getRawParameterValue("toggleSaturation");

    if (toggleLP) {
        *LPfilter.state = *juce::dsp::IIR::Coefficients<float>::makeLowPass(last_sample_rate, LPcutoff, LPresonance);
    }
    else {
        *LPfilter.state = *juce::dsp::IIR::Coefficients<float>::makeLowPass(last_sample_rate, 20000.0, 0.1);
    }
    if (toggleHP) {
        *HPfilter.state = *juce::dsp::IIR::Coefficients<float>::makeHighPass(last_sample_rate, HPcutoff, HPresonance);
    }
    else {
        *HPfilter.state = *juce::dsp::IIR::Coefficients<float>::makeHighPass(last_sample_rate, 20.0, 0.1);

    }
}

void TheMultiTaskerAudioProcessor::update_effect() {

    reverbRoomSize = *treeState.getRawParameterValue("reverbRoomSize");

    juce::dsp::Reverb::Parameters params;
    params.roomSize = reverbRoomSize;
    params.damping = 0.5f;
    params.wetLevel = 0.4f;
    params.dryLevel = 0.8f;
    params.width = 1.0f;
    params.freezeMode = 0.0f;
    params.width = 0.0f;
    ReverbEffect.setParameters(params);




}

void TheMultiTaskerAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    float convertedGain = juce::Decibels::decibelsToGain(static_cast<float>(*treeState.getRawParameterValue("gain")));

    

    juce::dsp::AudioBlock<float> block(buffer);
    update_filter();
   
    
    LPfilter.process(juce::dsp::ProcessContextReplacing<float>(block));
    HPfilter.process(juce::dsp::ProcessContextReplacing<float>(block));

    update_effect();
    if(toggleReverb) ReverbEffect.processStereo(block.getChannelPointer(0), block.getChannelPointer(1), buffer.getNumSamples());



    if (toggleGain) {
        for (int channel = 0; channel < totalNumInputChannels; ++channel)
        {
            auto* blockData = block.getChannelPointer(channel);

            for (int sample = 0; sample < block.getNumSamples(); ++sample) {
                blockData[sample] *= convertedGain;
            }


        }
    }
    

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

    juce::MemoryOutputStream save_stream(destData, false);
    treeState.state.writeToStream(save_stream);

}

void TheMultiTaskerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.


    auto tree = juce::ValueTree::readFromData(data, size_t(sizeInBytes));
    if (tree.isValid()) {

        treeState.state = tree;
        LPcutoff = static_cast<float>(*treeState.getRawParameterValue("LP"));
        LPresonance = static_cast<float>(*treeState.getRawParameterValue("LPr"));
        HPresonance = static_cast<float>(*treeState.getRawParameterValue("LPr"));
        HPcutoff = static_cast<float>(*treeState.getRawParameterValue("HP"));
        gain = static_cast<float>(*treeState.getRawParameterValue("gain"));
        reverbRoomSize = static_cast<float>(*treeState.getRawParameterValue("reverbRoomSize"));


        toggleLP=static_cast<bool>(*treeState.getRawParameterValue("toggleLP"));
        toggleHP=static_cast<bool>(*treeState.getRawParameterValue("toggleHP"));
        toggleGain =static_cast<bool>(*treeState.getRawParameterValue("toggleGain"));


        toggleReverb = static_cast<bool>(*treeState.getRawParameterValue("toggleReverb"));
        toggleDelay = static_cast<bool>(*treeState.getRawParameterValue("toggleDelay"));
        toggleSaturation = static_cast<bool>(*treeState.getRawParameterValue("toggleSaturation"));


    }

}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TheMultiTaskerAudioProcessor();
}
