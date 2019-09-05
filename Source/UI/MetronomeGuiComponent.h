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


	//==============================================================================
	void paint(Graphics& g) override;
	void resized() override;

	void play();
	void stop();

	enum class PlayState
	{
		Playing,
		Stopped
	};

private:
	TextButton playButton{ "Play" };
	TextButton stopButton{ "Stop" };

	PlayState playState{ PlayState::Stopped };

	MetronomeComponent metronome;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MetronomeGuiComponent)
};
