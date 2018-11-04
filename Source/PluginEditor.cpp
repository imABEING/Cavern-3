/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Cavern3AudioProcessorEditor::Cavern3AudioProcessorEditor (Cavern3AudioProcessor& p, AudioProcessorValueTreeState &vts)
    : AudioProcessorEditor (&p), processor (p), valueStateTree (vts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
    addAndMakeVisible(dryWetSlider);
    dryWetSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    dryWetSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
    dryWetSlider.setRange(0, 1, 0.01);
    dryWetAttachment = new AudioProcessorValueTreeState::SliderAttachment(valueStateTree, "dryWet", dryWetSlider);
    
    addAndMakeVisible(dampingSlider);
    dampingSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    dampingSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
    dampingSlider.setRange(0, 1, 0.01);
    dampingAttachment = new AudioProcessorValueTreeState::SliderAttachment(valueStateTree, "damping", dampingSlider);
    
    addAndMakeVisible(roomSizeSlider);
    roomSizeSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    roomSizeSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
    roomSizeSlider.setRange(0, 1, 0.01);
    roomSizeAttachment = new AudioProcessorValueTreeState::SliderAttachment(valueStateTree, "roomSize", roomSizeSlider);
    
    addAndMakeVisible(roomWidthSlider);
    roomWidthSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    roomWidthSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
    roomWidthSlider.setRange(0, 1, 0.01);
    roomWidthAttachment = new AudioProcessorValueTreeState::SliderAttachment(valueStateTree, "roomWidth", roomWidthSlider);
}

Cavern3AudioProcessorEditor::~Cavern3AudioProcessorEditor()
{
}

//==============================================================================
void Cavern3AudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    g.fillAll(Colours::black);
    g.setColour (Colours::white);
    g.setFont (15.0f);
    //g.drawFittedText ("", getLocalBounds(), Justification::centred, 1);
}

void Cavern3AudioProcessorEditor::resized()
{
    const int sliderWidth = getWidth() / 4;
    const int sliderHeight = getHeight();
    
    dryWetSlider.setBounds(0, 0, sliderWidth, sliderHeight);
    roomSizeSlider.setBounds(sliderWidth, 0, sliderWidth, sliderHeight);
    dampingSlider.setBounds(sliderWidth * 2, 0, sliderWidth, sliderHeight);
    roomWidthSlider.setBounds(sliderWidth * 3, 0, sliderWidth, sliderHeight);
}
