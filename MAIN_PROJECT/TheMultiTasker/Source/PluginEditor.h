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

    juce::Slider slider1f, slider2fr, slider3f, slider4fr, sliderReverb, sliderDelay, sliderSaturation, sliderGain;

    juce::Label labelReverb;
    juce::Label labelDelay;
    juce::Label labelSaturation;

    juce::Label low_pass_label;

    juce::Label lp_fq;
    juce::Label lp_res;
    juce::Label hp_fq;
    juce::Label hp_res;

    juce::Label plugin_name;

    juce::GroupComponent filters_group;
    juce::GroupComponent effect_group;

    juce::GroupComponent lowpass_group;
    juce::GroupComponent highpass_group;

    juce::GroupComponent gain_group;
    juce::Label labelGain;

    juce::ToggleButton toggleLP;
    juce::ToggleButton toggleHP;

    juce::ToggleButton toggleReverb;
    juce::ToggleButton toggleDelay;
    juce::ToggleButton toggleSaturation;

    juce::ToggleButton toggleGain;

    juce::Label lableToggleGain;
    juce::Label lableToggleReverb;
    juce::Label lableToggleSaturation;
    juce::Label lableToggleDelay;
    juce::Label lableToggleLP;
    juce::Label lableToggleHP;

    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> slider1f_attachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> slider2fr_attachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> slider3f_attachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> slider4fr_attachment;


    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> toggleLP_attachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> toggleHP_attachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> toggleGain_attachment;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> toggleReverb_attachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> toggleDelay_attachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> toggleSaturation_attachment;



    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderGain_attachment;


    void createSlider(juce::Slider& slider_instance, juce::Slider::SliderStyle style_info, double min, double max, double basic) {

        slider_instance.setSliderStyle(style_info);
        slider_instance.setTextBoxStyle(juce::Slider::TextBoxRight, false, 80, 20);
        slider_instance.setRange(min, max, basic);

    }




    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TheMultiTaskerAudioProcessorEditor)

};
