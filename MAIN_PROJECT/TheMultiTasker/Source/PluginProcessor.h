/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class TheMultiTaskerAudioProcessor  : public juce::AudioProcessor, juce::AudioProcessorValueTreeState::Listener
{
public:
    //==============================================================================
    TheMultiTaskerAudioProcessor();
    ~TheMultiTaskerAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    void update_filter();
    juce::AudioProcessorValueTreeState treeState;

  
private:

    double last_sample_rate=0;
    
    juce::dsp::ProcessorDuplicator < juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> LPfilter;
    juce::dsp::ProcessorDuplicator < juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> HPfilter;

    juce::Reverb ReverbEffect;

    float LPcutoff = 1000.0f;
    float LPresonance = 0.1f;
    float HPcutoff = 1000.0f;
    float HPresonance = 0.1f;

    bool toggleLP = true;
    bool toggleHP = true;
    bool toggleGain = true;
    
    bool toggleReverb = true;
    bool toggleDelay = true;
    bool toggleSaturation = true;

    float gain = 0.0f;


    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    void parameterChanged(const juce::String& parameterID, float newValue) override;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TheMultiTaskerAudioProcessor)
};
