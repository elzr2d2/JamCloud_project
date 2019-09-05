#pragma once

#include "JuceHeader.h"
#include "Audio/MetronomeComponent.h"
#include "TreeComponent.h"
#include "Audio/AudioEngine.h"

class MetronomeGuiComponent : public AudioAppComponent,
								public Button::Listener,
								public Timer
				
{
public:
	MetronomeGuiComponent(AudioEngine &inEngine);
    ~MetronomeGuiComponent();

    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;


	void paint(Graphics& g) override;
	void resized() override;

	void buttonClicked(Button* buttonThatWasClicked) override;

	void timerCallback() override;
	
	void play();
	void stop();

	enum class PlayState
	{
		Playing,
		Stopped
	};

private:

	std::unique_ptr<ImageButton> metronomeButton;
	PlayState playState{ PlayState::Stopped };
	MetronomeComponent metronome;
	AudioEngine &engine;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MetronomeGuiComponent)
};
