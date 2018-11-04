/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Cavern3AudioProcessor::Cavern3AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
                params(*this, nullptr)
#endif
{
    //NormalisableRange<float> dryWetRange (0.0f, 1.0f);
    //NormalisableRange<float> dampingRange (0.0f, 1.0f);
    //NormalisableRange<float> roomSizeRange (0.0f, 1.0f);
    
    params.createAndAddParameter("dryWet", "DryWet", String(), NormalisableRange<float> (0.0f, 1.0f), 0.5f, nullptr, nullptr);
    params.createAndAddParameter("damping", "Damping", String(), NormalisableRange<float> (0.0f, 1.0f), 0.1f, nullptr, nullptr);
    params.createAndAddParameter("roomSize", "RoomSize", String(), NormalisableRange<float> (0.0f, 1.0f), 0.4f, nullptr, nullptr);
    params.createAndAddParameter("roomWidth", "RoomWidth", String(), NormalisableRange<float> (0.0f, 1.0f), 0.4f, nullptr, nullptr);
    
    params.state = ValueTree(Identifier("ReverbState"));
}

Cavern3AudioProcessor::~Cavern3AudioProcessor()
{
}

//==============================================================================
const String Cavern3AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Cavern3AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Cavern3AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Cavern3AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Cavern3AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Cavern3AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Cavern3AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Cavern3AudioProcessor::setCurrentProgram (int index)
{
}

const String Cavern3AudioProcessor::getProgramName (int index)
{
    return {};
}

void Cavern3AudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void Cavern3AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    cavern.setSampleRate(sampleRate);
}

void Cavern3AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Cavern3AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void Cavern3AudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    //Get current values
    const float lastDryWet = *params.getRawParameterValue("dryWet");
    const float lastRoomSize = *params.getRawParameterValue("roomSize");
    const float lastDamping = *params.getRawParameterValue("damping");
    const float lastWidth = *params.getRawParameterValue("roomWidth");

    // This is here to avoid people getting screaming feedback
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    const auto numChannels = jmin(totalNumInputChannels, totalNumOutputChannels);
    
    //Update Parameters, Merge Dry/Wet Levels
    cavernParameters.dryLevel = 1 - lastDryWet;
    cavernParameters.wetLevel = lastDryWet;
    cavernParameters.roomSize = lastRoomSize;
    cavernParameters.damping = lastDamping;
    cavernParameters.width = lastWidth;
    
    //Set Parameters
    cavern.setParameters(cavernParameters);
    
    //Process Mono/Stereo
    if (numChannels == 1)
        cavern.processMono(buffer.getWritePointer(0), buffer.getNumSamples());
    else if (numChannels == 2)
        cavern.processStereo(buffer.getWritePointer(0), buffer.getWritePointer(1), buffer.getNumSamples());
    
    //cavern.reset();
        
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
}

//==============================================================================
bool Cavern3AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* Cavern3AudioProcessor::createEditor()
{
    return new Cavern3AudioProcessorEditor (*this, params);
}

//==============================================================================
void Cavern3AudioProcessor::getStateInformation (MemoryBlock& destData)
{
    ScopedPointer<XmlElement> xml(params.state.createXml());
    copyXmlToBinary(*xml, destData);
}

void Cavern3AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    ScopedPointer<XmlElement> savedParametersXml (getXmlFromBinary(data, sizeInBytes));
    if (savedParametersXml != nullptr)
    {
        if (savedParametersXml->hasTagName(params.state.getType()))
        {
            params.state = ValueTree::fromXml(*savedParametersXml);
        }
        
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Cavern3AudioProcessor();
}
