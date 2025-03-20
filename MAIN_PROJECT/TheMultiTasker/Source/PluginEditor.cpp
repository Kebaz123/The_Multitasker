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


//filters
// 
// 
// 
// 
    addAndMakeVisible(filters_group);
    addAndMakeVisible(highpass_group);
    addAndMakeVisible(lowpass_group);
    
    filters_group.setText("Filters");
    highpass_group.setText("Highpass");
    lowpass_group.setText("Lowpass");
  

    //sliders
    
    addAndMakeVisible(slider1f);
    addAndMakeVisible(slider2fr);
    addAndMakeVisible(slider3f);
    addAndMakeVisible(slider4fr);
  
    addAndMakeVisible(low_pass_label);

    low_pass_label.setText("Lowpass Filter", juce::dontSendNotification);

    createSlider(slider1f, juce::Slider::LinearHorizontal, 20.0, 20000.0, 1.0);
    slider1f.setSkewFactorFromMidPoint(1000.0);

    createSlider(slider2fr, juce::Slider::LinearHorizontal, 0.0, 100.0, 0.0);
    

    createSlider(slider3f, juce::Slider::LinearHorizontal, 20.0, 20000.0, 1);
    slider3f.setSkewFactorFromMidPoint(1000.0);

    createSlider(slider4fr, juce::Slider::LinearHorizontal, 0.0, 100.0, 0.0);




    

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
    slider2fr.setBounds(margin+filters_group.getWidth()*0.11, margin+ filters_group.getWidth() * 0.36, filters_group.getWidth()*0.80, filters_group.getHeight()*0.15);

    slider3f.setBounds(margin+filters_group.getWidth()*0.11, margin+ filters_group.getWidth() * 0.65, filters_group.getWidth()*0.80, filters_group.getHeight()*0.15);
    slider4fr.setBounds(margin+filters_group.getWidth()*0.11, margin+ filters_group.getWidth() * 0.89, filters_group.getWidth()*0.80, filters_group.getHeight()*0.15);


    lowpass_group.setBounds(slider1f.getX() - slider1f.getWidth() * 0.075, slider1f.getY() - slider1f.getWidth() * 0.05, filters_group.getWidth() - filters_group.getWidth() * 0.1, slider1f.getHeight()+slider2fr.getHeight() + filters_group.getHeight() * 0.1);
    highpass_group.setBounds(slider1f.getX() - slider1f.getWidth() * 0.075, slider1f.getY() + slider1f.getWidth() * 0.65, filters_group.getWidth() - filters_group.getWidth() * 0.1, slider1f.getHeight()+slider2fr.getHeight() + filters_group.getHeight() * 0.1);


    plugin_name.setBounds(50, 375, 100, 20 );



}

void TheMultiTaskerAudioProcessorEditor::resized()
{
   
}

