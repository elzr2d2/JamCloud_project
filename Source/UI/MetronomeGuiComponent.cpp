/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MetronomeGuiComponent.h"

//==============================================================================
MetronomeGuiComponent::MetronomeGuiComponent()
{
   
    // Some platforms require permissions to open input channels so request that here
    if (RuntimePermissions::isRequired (RuntimePermissions::recordAudio)
        && ! RuntimePermissions::isGranted (RuntimePermissions::recordAudio))
    {
        RuntimePermissions::request (RuntimePermissions::recordAudio,
                                     [&] (bool granted) { if (granted)  setAudioChannels (2, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (0, 0);
    }
}

MetronomeGuiComponent::~MetronomeGuiComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}


bool MetronomeGuiComponent::getStatePlay()
{
	metronome.setBpm(bpm);
	return statePlay;
}

void MetronomeGuiComponent::setStatePlay(bool statePlay)
{
	this->statePlay = statePlay;
}

void MetronomeGuiComponent::setBpm(double bpm)
{
	this->bpm = bpm;
}

double MetronomeGuiComponent::getBpm()
{
	return bpm;
}



//==============================================================================
void MetronomeGuiComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    metronome.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MetronomeGuiComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    bufferToFill.clearActiveBufferRegion();
    
    if (statePlay)
    {
		
        metronome.getNextAudioBlock (bufferToFill);
    }
	else
	{
		metronome.reset();
	}
}

void MetronomeGuiComponent::releaseResources()
{
    
}



