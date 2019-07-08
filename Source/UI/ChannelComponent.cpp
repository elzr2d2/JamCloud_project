
#include "ChannelComponent.h"

const Colour notArmedColor = Colour(0xff1b605e);
const Colour notToggledColor = Colours::white;

ChannelComponent::ChannelComponent(AudioEngine& inEngine, AudioTrack& inTrack)
        : engine(inEngine),
          track(inTrack)
{
    shouldUpdate.reset(new std::atomic<bool>(false));
    startTimerHz(60);

    track.state.addListener(this);

	/* Select Button */
    selectButton.reset(new TextButton("selectButton"));
    addAndMakeVisible(selectButton.get());
    selectButton->setButtonText(String());
    selectButton->addListener(this);
    selectButton->setColour(TextButton::buttonColourId, Colour(0xff1b605e));
    selectButton->setBounds(8, 8, 20, 20);

	/* Text Editor */
    nameText.reset(new TextEditor("nameText"));
    addAndMakeVisible(nameText.get());
    nameText->setMultiLine(false);
    nameText->setReturnKeyStartsNewLine(false);
    nameText->setReadOnly(false);
    nameText->setScrollbarsShown(true);
    nameText->setCaretVisible(true);
    nameText->setPopupMenuEnabled(true);
    nameText->setText(String());
    nameText->setBounds(35, 10, 90, 18);
	nameText->setColour(TextEditor::ColourIds::outlineColourId, Colours::transparentWhite);

	/* Volume Slider */
    volumeSlider.reset(new Slider("volume slider"));
    addAndMakeVisible(volumeSlider.get());
    volumeSlider->setRange(-30, 6, 0);
    volumeSlider->setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    volumeSlider->setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    volumeSlider->setColour(Slider::thumbColourId, Colours::whitesmoke);
    volumeSlider->addListener(this);
    volumeSlider->setBounds(135, 10, 60, 20);

	/* Pan Slider */
	panSlider.reset(new Slider("pan slider"));
	addAndMakeVisible(panSlider.get());
	panSlider->setRange(-100, 100, 0);
	panSlider->setSliderStyle(Slider::SliderStyle::LinearHorizontal);
	panSlider->setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	panSlider->setColour(Slider::thumbColourId, Colours::whitesmoke);
	panSlider->addListener(this);
	panSlider->setBounds(135, 40, 60, 20);

	/* Mute Button */
    muteButton.reset(new ImageButton("muteBotton"));
    addAndMakeVisible(muteButton.get());
    muteButton->setButtonText(TRANS("Mute"));
    muteButton->addListener(this);
    muteButton->setImages(false, true, true,
                          ImageCache::getFromMemory(BinaryData::_033mute_png, BinaryData::_033mute_pngSize), 1.000f,
                          Colours::whitesmoke,
                          Image(), 1.000f, Colours::whitesmoke,
                          Image(), 1.000f, Colours::whitesmoke);
    muteButton->setBounds(10, 40, 15, 15);

	/* Solo Button */
    soloButton.reset(new ImageButton("soloButton"));
    addAndMakeVisible(soloButton.get());
    soloButton->setButtonText(TRANS("Solo"));
    soloButton->addListener(this);
    soloButton->setImages(false, true, true,
                          ImageCache::getFromMemory(BinaryData::_048headphones_png, BinaryData::_048headphones_pngSize),
                          1.000f, Colours::white,
                          Image(), 1.000f, Colours::whitesmoke,
                          Image(), 1.000f, Colours::whitesmoke);
    soloButton->setBounds(45, 40, 15, 15);

	/* Add File Button */
    addFileButton.reset(new ImageButton("addFileButton"));
    addAndMakeVisible(addFileButton.get());
    addFileButton->setButtonText(TRANS("Add File"));
    addFileButton->addListener(this);
    addFileButton->setImages(false,
                             true,
                             true,
                             ImageCache::getFromMemory(BinaryData::_074folder_png, BinaryData::_074folder_pngSize),
                             1.000f,
							Colours::whitesmoke,
                             Image(),
                             1.000f,
							Colours::whitesmoke,
                             Image(),
                             1.000f,
                             Colours::darkorange);
    addFileButton->setBounds(80, 40, 15, 15);

	/* Select Input Button */
	selectInputButton.reset(new ImageButton("selectInputButton"));
	addAndMakeVisible(selectInputButton.get());
	selectInputButton->setButtonText(TRANS("Select Input"));
	selectInputButton->addListener(this);
	selectInputButton->setImages(false,
		true,
		true,
		ImageCache::getFromMemory(BinaryData::_073jackconnector1_png, BinaryData::_073jackconnector1_pngSize),
		1.000f,
		Colours::whitesmoke,
		Image(),
		1.000f,
		Colours::whitesmoke,
		Image(),
		1.000f,
		Colours::darkorange);
	selectInputButton->setBounds(80+35, 40, 15, 15);

}

void ChannelComponent::paint(Graphics& g)
{
    g.fillAll(Colour(0xff25292b));

    {
        float x = 0.0f, y = 0.0f, width = 200.0f, height = 70.0f;
        Colour fillColour2 = Colour(0xff262626);

        g.setGradientFill(ColourGradient(Colours::black,
                                         176.0f - 0.0f + x,
                                         16.0f - 0.0f + y,
                                         fillColour2,
                                         104.0f - 0.0f + x,
                                         48.0f - 0.0f + y,
                                         false));

        g.fillRoundedRectangle(x, y, width, height, 10.000f);
    }

}

void ChannelComponent::resized()
{
    auto bounds = getLocalBounds();

	int startX = 204;

    for (auto& thumbnail: audioThumbnailComponents)
    {
		auto position = thumbnail->getClip().getPosition();

		auto start = position.getStart() / 10 * (double)getWidth();
		auto length = position.getLength() / 10 * (double)getWidth();
    	
        thumbnail->setBounds(startX + (int)start, 0, int(length), bounds.getHeight());
    }

	
}

void ChannelComponent::buttonClicked(Button* buttonThatWasClicked)
{
	if (buttonThatWasClicked == selectButton.get())
	{
		clickSelectButton();
	}
	else if (buttonThatWasClicked == muteButton.get())
	{
		engine.muteChannel(track);
		
		if (track.isMuted(true))
		{
			//change color if is  Muted
			muteButton->setImages(false, true, true,
				ImageCache::getFromMemory(BinaryData::_033mute_png, BinaryData::_033mute_pngSize), 1.000f,
				Colours::darkorange,
				Image(), 1.000f, Colours::darkorange,
				Image(), 1.000f, Colours::darkorange);
		}
		else
		{
			//change color if is Not Muted
			muteButton->setImages(false, true, true,
				ImageCache::getFromMemory(BinaryData::_033mute_png, BinaryData::_033mute_pngSize), 1.000f,
				Colours::whitesmoke,
				Image(), 1.000f, Colours::whitesmoke,
				Image(), 1.000f, Colours::whitesmoke);
		}
	
	}

	else if (buttonThatWasClicked == soloButton.get())
	{
		engine.soloChannel(track);

		if (track.isSolo(false))
		{
			//change color if is Not Solo
			soloButton->setImages(false, true, true,
				ImageCache::getFromMemory(BinaryData::_048headphones_png, BinaryData::_048headphones_pngSize), 1.000f,
				Colours::darkorange,
				Image(), 1.000f, Colours::darkorange,
				Image(), 1.000f, Colours::darkorange);
		}
		else
		{
			//change color if is  Solo
			soloButton->setImages(false, true, true,
				ImageCache::getFromMemory(BinaryData::_048headphones_png, BinaryData::_048headphones_pngSize),
				1.000f, Colours::white,
				Image(), 1.000f, Colours::whitesmoke,
				Image(), 1.000f, Colours::whitesmoke);
		}

	}

	else if (buttonThatWasClicked == addFileButton.get())
		clickAddFileButton();
	else if (buttonThatWasClicked == selectInputButton.get())
		engine.inputMonitoring(&track);

}

void ChannelComponent::clickAddFileButton()
{
    auto location = File::getSpecialLocation(File::userDesktopDirectory);

    FileChooser chooser("Choose a file", location, "*.wav", true, false);

    if (chooser.browseForFileToOpen())
    {
        auto file = chooser.getResult();

        engine.addNewClipFromFile(file, track);
		nameText.get()->setText(file.getFileName());
    }
	
}

void ChannelComponent::clickSelectButton() const
{
    bool shouldArm = !engine.isTrackArmed(track);

    engine.armTrack(track, shouldArm);

    selectButton->setToggleState(engine.isTrackArmed(track), dontSendNotification);
    selectButton->setColour(selectButton->buttonColourId, getArmedTrackColor());
}




Colour ChannelComponent::getArmedTrackColor() const
{
    auto color = notArmedColor;

    if (selectButton->getToggleState())
        color = Colours::orange;

    return color;
}



void ChannelComponent::sliderValueChanged(Slider* sliderThatWasMoved)
{
    if (sliderThatWasMoved == volumeSlider.get())
    {
        auto volume = (float) sliderThatWasMoved->getValue();
        engine.changeVolume(track, volume);
    }
	if (sliderThatWasMoved == panSlider.get())
	{
		auto pan = (float)sliderThatWasMoved->getValue();
		engine.changePan(track, pan);
	}
}

void ChannelComponent::timerCallback()
{
    if (shouldUpdate->load())
    {
        shouldUpdate->store(false);
        rebuildClips();
    }
}

void ChannelComponent::rebuildClips()
{
    audioThumbnailComponents.clear();

    for (auto* clip:track.getClips())
    {
        audioThumbnailComponents.emplace_back();

        auto& newThumbnail = audioThumbnailComponents.back();
		newThumbnail.reset(new AudioThumbnailComponent(*clip));
        addAndMakeVisible(*newThumbnail);
    }

    resized();
}


