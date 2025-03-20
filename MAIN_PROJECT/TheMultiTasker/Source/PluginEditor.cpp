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

    addAndMakeVisible(plugin_name);
    plugin_name.setText("The Multitasker", juce::dontSendNotification);
    plugin_name.setJustificationType(juce::Justification::centred);


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
    
}

void TheMultiTaskerAudioProcessorEditor::resized()
{
   
}
