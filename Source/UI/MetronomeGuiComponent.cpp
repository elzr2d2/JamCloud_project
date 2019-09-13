
#include "MetronomeGuiComponent.h"

MetronomeGuiComponent::MetronomeGuiComponent(AudioEngine &inEngine):engine(inEngine)
{
	Colour darkGreyJam = Colour(0xff2c302f);
	Colour orangeJam = Colour(0xffc39400);
	Colour lightgrey = Colour(0x258A878B);

	startTimerHz(30);

	/* button */
	metronomeButton.reset(new ImageButton("metronomeButton"));
	addAndMakeVisible(metronomeButton.get());
	metronomeButton->setButtonText(TRANS("new button"));
	metronomeButton->addListener(this);
	metronomeButton->setImages(false, true, true,
		ImageCache::getFromMemory(BinaryData::_010triangle_png,
			BinaryData::_010triangle_pngSize), 1.0f,
		darkGreyJam,
		Image(), 1.0f, Colours::orange,
		Image(), 1.0f, darkGreyJam);
	metronomeButton->setBounds(0, 0, 20, 20);
	metronomeButton->setClickingTogglesState(true);
	metronomeButton->setToggleState(false, NotificationType::dontSendNotification);

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

void MetronomeGuiComponent::buttonClicked(Button * buttonThatWasClicked)
{
	if (buttonThatWasClicked == metronomeButton.get())
	{
		auto buttonPressed = metronomeButton->getToggleState();
		
	}
}

void MetronomeGuiComponent::timerCallback()
{
	metronome.setBpm(engine.getBpm());

	auto buttonPressed = metronomeButton->getToggleState();

	if (buttonPressed && engine.isPlaying())
		play();
	else
		stop();
}

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

void MetronomeGuiComponent::paint(Graphics& g)
{
	Colour darkGreyJam = Colour(0xff2c302f);
	Colour orangeJam = Colour(0xffc39400);
	Colour lightgrey = Colour(0x258A878B);
	
	g.fillAll(Colours::transparentWhite);

	if (metronomeButton->getToggleState())
	{
		metronomeButton->setImages(false, true, true,
			ImageCache::getFromMemory(BinaryData::_010triangle_png,
				BinaryData::_010triangle_pngSize), 1.0f,
			Colours::orange,
			Image(), 1.0f, Colours::orange,
			Image(), 1.0f, Colours::orange);
	}
	else
	{
		metronomeButton->setImages(false, true, true,
			ImageCache::getFromMemory(BinaryData::_010triangle_png,
				BinaryData::_010triangle_pngSize), 1.0f,
			darkGreyJam,
			Image(), 1.0f, Colours::orange,
			Image(), 1.0f, darkGreyJam);
	}


}

void MetronomeGuiComponent::resized()
{

}
