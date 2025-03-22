/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TheMultiTaskerAudioProcessorEditor::TheMultiTaskerAudioProcessorEditor (TheMultiTaskerAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (800, 450);


    //plugin name label
    addAndMakeVisible(plugin_name);
    plugin_name.setText("The Multitasker", juce::dontSendNotification);
    plugin_name.setJustificationType(juce::Justification::centred);

//effects 

    addAndMakeVisible(lableToggleReverb);
    addAndMakeVisible(lableToggleDelay);
    addAndMakeVisible(lableToggleSaturation);
    lableToggleReverb.setText("Toggle reverb", juce::dontSendNotification);
    lableToggleDelay.setText("Toggle delay", juce::dontSendNotification);
    lableToggleSaturation.setText("Toggle saturation", juce::dontSendNotification);


    addAndMakeVisible(toggleReverb);
    addAndMakeVisible(toggleDelay);
    addAndMakeVisible(toggleSaturation);

    addAndMakeVisible(effect_group);
    addAndMakeVisible(sliderReverb);
    addAndMakeVisible(sliderDelay);
    addAndMakeVisible(sliderSaturation);

    addAndMakeVisible(labelReverb);
    addAndMakeVisible(labelDelay);
    addAndMakeVisible(labelSaturation);


    lableToggleDelay.attachToComponent(&toggleDelay, true);
    lableToggleReverb.attachToComponent(&toggleReverb, true);
    lableToggleSaturation.attachToComponent(&toggleSaturation, true);

    effect_group.setText("Effects");

    labelReverb.setText("Reverb", juce::dontSendNotification);
    labelDelay.setText("Delay", juce::dontSendNotification);
    labelSaturation.setText("Saturation", juce::dontSendNotification);

    createSlider(sliderReverb, juce::Slider::LinearHorizontal, 0.0, 100.0, 1.0);
    createSlider(sliderDelay, juce::Slider::LinearHorizontal, 0.0, 100.0, 1.0);
    createSlider(sliderSaturation, juce::Slider::LinearHorizontal, 0.0, 100.0, 1.0);

//gain  

    addAndMakeVisible(toggleGain);
    addAndMakeVisible(lableToggleGain);
    lableToggleGain.setText("Toggle gain", juce::dontSendNotification);

    lableToggleGain.attachToComponent(&toggleGain, true);

    addAndMakeVisible(gain_group);
    addAndMakeVisible(labelGain);
    addAndMakeVisible(sliderGain);
    gain_group.setText("Gain");
    createSlider(sliderGain, juce::Slider::LinearHorizontal, -24.0, 24.0, 1);
    labelGain.setText("Decibles", juce::dontSendNotification);

//filters
// 
// 
// 
// 
// 

// 
    addAndMakeVisible(lableToggleLP);
    addAndMakeVisible(lableToggleHP);
    addAndMakeVisible(toggleLP);
    addAndMakeVisible(toggleHP);

    lableToggleLP.setText("Toggle LP", juce::dontSendNotification);
    lableToggleHP.setText("Toggle HP", juce::dontSendNotification);

    lableToggleLP.attachToComponent(&toggleLP, true);
    lableToggleHP.attachToComponent(&toggleHP, true);

    addAndMakeVisible(lp_fq);
    lp_fq.setText("Frequency", juce::dontSendNotification);

    addAndMakeVisible(lp_res);
    lp_res.setText("Resonance", juce::dontSendNotification);


    addAndMakeVisible(hp_fq);
    hp_fq.setText("Frequency", juce::dontSendNotification);

    addAndMakeVisible(hp_res);
    hp_res.setText("Resonance", juce::dontSendNotification);



    addAndMakeVisible(filters_group);
    addAndMakeVisible(highpass_group);
    addAndMakeVisible(lowpass_group);
    
    filters_group.setText("Filters");
    highpass_group.setText("Highpass");
    lowpass_group.setText("Lowpass");
  

    //sliders
    slider1f_attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "LP", slider1f);
    addAndMakeVisible(slider1f);

    slider2fr_attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "LPr", slider2fr);
    addAndMakeVisible(slider2fr);
   


    slider3f_attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "HP", slider3f);
    addAndMakeVisible(slider3f);
    addAndMakeVisible(slider4fr);
  
    addAndMakeVisible(low_pass_label);

    low_pass_label.setText("Lowpass Filter", juce::dontSendNotification);


    createSlider(slider1f, juce::Slider::LinearHorizontal, 20.0, 20000.0, 1.0);
    slider1f.setSkewFactorFromMidPoint(1000.0);

   

    createSlider(slider2fr, juce::Slider::LinearHorizontal, 0.0, 100.0, 1);
    

    createSlider(slider3f, juce::Slider::LinearHorizontal, 20.0, 20000.0, 1);
    slider3f.setSkewFactorFromMidPoint(1000.0);

    createSlider(slider4fr, juce::Slider::LinearHorizontal, 0.0, 100.0, 1);




    

}

TheMultiTaskerAudioProcessorEditor::~TheMultiTaskerAudioProcessorEditor()
{
}

//==============================================================================
void TheMultiTaskerAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.setColour (juce::Colours::white);
    g.setFont (juce::Font (40.0f));
    
    auto margin = getWidth() / 32;


    filters_group.setBounds(margin, margin, getWidth()*0.40, getWidth()* 0.5);

    slider1f.setBounds(margin+filters_group.getWidth()*0.11, margin+ filters_group.getWidth() * 0.12, filters_group.getWidth()*0.80, filters_group.getHeight()*0.15);
    lp_fq.setBounds(margin + filters_group.getWidth() * 0.11, margin + filters_group.getWidth() * 0.17, filters_group.getWidth() * 0.80, filters_group.getHeight() * 0.15);

    slider2fr.setBounds(margin+filters_group.getWidth()*0.11, margin+ filters_group.getWidth() * 0.32, filters_group.getWidth()*0.80, filters_group.getHeight()*0.15);
    lp_res.setBounds(margin + filters_group.getWidth() * 0.11, margin + filters_group.getWidth() * 0.37, filters_group.getWidth() * 0.80, filters_group.getHeight() * 0.15);

    slider3f.setBounds(margin+filters_group.getWidth()*0.11, margin+ filters_group.getWidth() * 0.65, filters_group.getWidth()*0.80, filters_group.getHeight()*0.15);
    hp_fq.setBounds(margin + filters_group.getWidth() * 0.11, margin + filters_group.getWidth() * 0.70, filters_group.getWidth() * 0.80, filters_group.getHeight() * 0.15);
    slider4fr.setBounds(margin+filters_group.getWidth()*0.11, margin+ filters_group.getWidth() * 0.85, filters_group.getWidth()*0.80, filters_group.getHeight()*0.15);
    hp_res.setBounds(margin + filters_group.getWidth() * 0.11, margin + filters_group.getWidth() * 0.90, filters_group.getWidth() * 0.80, filters_group.getHeight() * 0.15);

    lowpass_group.setBounds(slider1f.getX() - slider1f.getWidth() * 0.075, slider1f.getY() - slider1f.getWidth() * 0.05, filters_group.getWidth() - filters_group.getWidth() * 0.1, slider1f.getHeight()+slider2fr.getHeight() + filters_group.getHeight() * 0.1);
    highpass_group.setBounds(slider1f.getX() - slider1f.getWidth() * 0.075, slider1f.getY() + slider1f.getWidth() * 0.62, filters_group.getWidth() - filters_group.getWidth() * 0.1, slider1f.getHeight()+slider2fr.getHeight() + filters_group.getHeight() * 0.1);
    toggleLP.setBounds(slider1f.getX() + slider1f.getWidth() * 0.25, getHeight()*0.70, filters_group.getWidth() - filters_group.getWidth() * 0.1, slider1f.getHeight() + slider2fr.getHeight() + filters_group.getHeight() * 0.1);
    toggleHP.setBounds(slider1f.getX() + slider1f.getWidth() * 0.80, getHeight()*0.70, filters_group.getWidth() - filters_group.getWidth() * 0.1, slider1f.getHeight() + slider2fr.getHeight() + filters_group.getHeight() * 0.1);


    effect_group.setBounds(filters_group.getX() + filters_group.getWidth() + margin, margin, getWidth() * 0.50, getWidth() * 0.30);

    toggleReverb.setBounds(effect_group.getX() + effect_group.getWidth() * 0.25, effect_group.getY() +effect_group.getHeight()*0.7, effect_group.getWidth() * 0.20, effect_group.getHeight() * 0.15);
    toggleDelay.setBounds(effect_group.getX() + effect_group.getWidth() * 0.55, effect_group.getY() +effect_group.getHeight()*0.7, effect_group.getWidth() * 0.20, effect_group.getHeight() * 0.15);
    toggleSaturation.setBounds(effect_group.getX() + effect_group.getWidth() * 0.90, effect_group.getY() +effect_group.getHeight()*0.7, effect_group.getWidth() * 0.20, effect_group.getHeight() * 0.15);
    

    sliderReverb.setBounds(effect_group.getX() + effect_group.getWidth() * 0.05, effect_group.getY() + effect_group.getHeight() * 0.1, effect_group.getWidth() - effect_group.getWidth() * 0.1, effect_group.getHeight() * 0.1);
    labelReverb.setBounds(effect_group.getX() + effect_group.getWidth() * 0.05, effect_group.getY() + effect_group.getHeight() * 0.17, effect_group.getWidth() - effect_group.getWidth() * 0.1, effect_group.getHeight() * 0.1);

    sliderDelay.setBounds(effect_group.getX() + effect_group.getWidth() * 0.05, effect_group.getY() + effect_group.getHeight() * 0.3, effect_group.getWidth() - effect_group.getWidth() * 0.1, effect_group.getHeight() * 0.1);
    labelDelay.setBounds(effect_group.getX() + effect_group.getWidth() * 0.05, effect_group.getY() + effect_group.getHeight() * 0.36, effect_group.getWidth() - effect_group.getWidth() * 0.1, effect_group.getHeight() * 0.1);

    sliderSaturation.setBounds(effect_group.getX() + effect_group.getWidth() * 0.05, effect_group.getY() + effect_group.getHeight() * 0.50, effect_group.getWidth() - effect_group.getWidth() * 0.1, effect_group.getHeight() * 0.1);
    labelSaturation.setBounds(effect_group.getX() + effect_group.getWidth() * 0.05, effect_group.getY() + effect_group.getHeight() * 0.56, effect_group.getWidth() - effect_group.getWidth() * 0.1, effect_group.getHeight() * 0.1);

    gain_group.setBounds(filters_group.getX() + filters_group.getWidth() + margin, margin+effect_group.getHeight()+effect_group.getHeight()*0.1, getWidth() * 0.50, getWidth() * 0.15);
    toggleGain.setBounds(gain_group.getX() + gain_group.getWidth() * 0.55, gain_group.getY() + gain_group.getHeight() * 0.70, gain_group.getWidth() * 0.40, gain_group.getHeight() * 0.2);

    sliderGain.setBounds(gain_group.getX() + gain_group.getWidth() * 0.1, gain_group.getY() + gain_group.getHeight() * 0.3, gain_group.getWidth() * 0.85, gain_group.getHeight() * 0.2);
    labelGain.setBounds(gain_group.getX() + gain_group.getWidth() * 0.1, gain_group.getY() + gain_group.getHeight() * 0.50, gain_group.getWidth() * 0.85, gain_group.getHeight() * 0.2);


    plugin_name.setBounds(getWidth()*0.80, getHeight()*0.85, getWidth()*0.2, getHeight()*0.2);



}

void TheMultiTaskerAudioProcessorEditor::resized()
{
   
}

