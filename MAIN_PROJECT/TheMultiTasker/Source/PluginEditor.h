/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class TheMultiTaskerAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    TheMultiTaskerAudioProcessorEditor (TheMultiTaskerAudioProcessor&);
    ~TheMultiTaskerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    TheMultiTaskerAudioProcessor& audioProcessor;


   
    //fr = filter resonance

    juce::Slider slider1f, slider2fr, slider3f, slider4fr, slider5f, slider6fr;

    juce::Label low_pass_label;

    juce::Label plugin_name;

    juce::GroupComponent filters_group;

    juce::GroupComponent lowpass_group;
    juce::GroupComponent highpass_group;


    void createSlider(juce::Slider& slider_instance, juce::Slider::SliderStyle style_info, double min, double max, double basic) {

        slider_instance.setSliderStyle(style_info);
        slider_instance.setTextBoxStyle(juce::Slider::TextBoxRight, false, 80, 20);
        slider_instance.setRange(min, max, basic);

    }




    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TheMultiTaskerAudioProcessorEditor)

};
