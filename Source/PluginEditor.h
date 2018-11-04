/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "Images.h"

//==============================================================================
/**
*/
class Cavern3AudioProcessorEditor  : public AudioProcessorEditor
{
public:
    Cavern3AudioProcessorEditor (Cavern3AudioProcessor&, AudioProcessorValueTreeState&);
    ~Cavern3AudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    AudioProcessorValueTreeState& valueStateTree;
    
    Slider roomSizeSlider;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> roomSizeAttachment;
    
    Slider roomWidthSlider;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> roomWidthAttachment;
    
    Slider dampingSlider;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> dampingAttachment;
    
    Slider dryWetSlider;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> dryWetAttachment;
    
    Image background;
    Image logo;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Cavern3AudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Cavern3AudioProcessorEditor)
};
