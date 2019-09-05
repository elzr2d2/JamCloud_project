/*
  ==============================================================================

	This file was auto-generated!

  ==============================================================================
*/

#include "MetronomeGuiComponent.h"

//==============================================================================
MetronomeGuiComponent::MetronomeGuiComponent()
{
	playButton.setRadioGroupId(1);
	playButton.setToggleState(false, NotificationType::dontSendNotification);
	playButton.onClick = [this]() { play(); };
	addAndMakeVisible(playButton);

	stopButton.setRadioGroupId(1);
	playButton.setToggleState(true, NotificationType::dontSendNotification);
	stopButton.onClick = [this]() { stop(); };
	addAndMakeVisible(stopButton);

	setSize(200, 200);

	// Some platforms require permissions to open input channels so request that here
	if (RuntimePermissions::isRequired(RuntimePermissions::recordAudio)
		&& !RuntimePermissions::isGranted(RuntimePermissions::recordAudio))
	{
		RuntimePermissions::request(RuntimePermissions::recordAudio,
			[&](bool granted) { if (granted)  setAudioChannels(2, 2); });
	}
	else
	{
		// Specify the number of input and output channels that we want to open
		setAudioChannels(2, 2);
	}
}

MetronomeGuiComponent::~MetronomeGuiComponent()
{
	// This shuts down the audio device and clears the audio source.
	shutdownAudio();
}

void MetronomeGuiComponent::play()
{
	playState = PlayState::Playing;
}

void MetronomeGuiComponent::stop()
{
	playState = PlayState::Stopped;
	metronome.reset();
}

//==============================================================================
void MetronomeGuiComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
	metronome.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MetronomeGuiComponent::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill)
{
	bufferToFill.clearActiveBufferRegion();

	if (playState == PlayState::Playing)
	{
		metronome.getNextAudioBlock(bufferToFill);
	}
}

void MetronomeGuiComponent::releaseResources()
{
	// This will be called when the audio device stops, or when it is being
	// restarted due to a setting change.

	// For more details, see the help for AudioProcessor::releaseResources()
}

//==============================================================================
void MetronomeGuiComponent::paint(Graphics& g)
{
	// (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));

	// You can add your drawing code here!
}

void MetronomeGuiComponent::resized()
{
	Rectangle<int> bounds = getLocalBounds();

	FlexBox flexBox;
	flexBox.items.add(FlexItem(100, 100, playButton));
	flexBox.items.add(FlexItem(100, 100, stopButton));
	flexBox.performLayout(bounds);
}
