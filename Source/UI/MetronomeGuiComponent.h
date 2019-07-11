/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "Audio/MetronomeComponent.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MetronomeGuiComponent : public AudioAppComponent
{
public:
    //==============================================================================
	MetronomeGuiComponent();
    ~MetronomeGuiComponent();

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;


  
	bool getStatePlay();
	void setStatePlay(bool statePlay);

	

private:
	
	bool statePlay = false;

	MetronomeComponent metronome;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MetronomeGuiComponent)
};
