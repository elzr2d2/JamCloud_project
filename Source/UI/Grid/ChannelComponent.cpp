#include "ChannelComponent.h"

ChannelComponent::ChannelComponent(AudioEngine& inEngine, AudioTrack& inTrack)
        : engine(inEngine),
          track(inTrack)
{
   
    startTimerHz(60);

    track.state.addListener(this);
	
	/* Track Name Label */
	trackText.reset(new Label("trackText",TRANS("")));
	addAndMakeVisible(trackText.get());
	trackText->setFont(Font("Bahnschrift", 15.00f, Font::plain).withTypefaceStyle("Regular").withExtraKerningFactor(-0.048f));
	trackText->setJustificationType(Justification::centredLeft);
	trackText->setEditable(false, true, false);
	trackText->setColour(Label::backgroundColourId, darkGreyJam);
	trackText->setColour(TextEditor::textColourId, Colours::whitesmoke);
	trackText->setColour(TextEditor::backgroundColourId, darkGreyJam);
	trackText->setColour(TextEditor::highlightColourId,blueSky);
	trackText->addListener(this);
	trackText->setText(track.getName(),NotificationType::dontSendNotification);
	trackText->setBounds(35, 8, 80, 20);

	/* Volume Slider */
    volumeSlider.reset(new Slider("volume slider"));
    addAndMakeVisible(volumeSlider.get());
    volumeSlider->setRange(-30, 6, 0);
    volumeSlider->setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    volumeSlider->setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    volumeSlider->setColour(Slider::thumbColourId, Colours::whitesmoke);
	volumeSlider->setColour(Slider::ColourIds::backgroundColourId, darkGreyJam);
	volumeSlider->setColour(Slider::ColourIds::trackColourId, orangeJam);
    volumeSlider->addListener(this);
    volumeSlider->setBounds(135, 10, 60, 20);

	/* Pan Slider */
	panSlider.reset(new Slider("pan slider"));
	addAndMakeVisible(panSlider.get());
	panSlider->setRange(-100, 100, 0);
	panSlider->setSliderStyle(Slider::SliderStyle::LinearHorizontal);
	panSlider->setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	panSlider->setColour(Slider::thumbColourId, Colours::whitesmoke);
	panSlider->setColour(Slider::ColourIds::backgroundColourId, darkGreyJam);
	panSlider->setColour(Slider::ColourIds::trackColourId, darkGreyJam);
	panSlider->addListener(this);
	panSlider->setBounds(135, 40, 60, 20);

	/* Select Button */
	selectButton.reset(new TextButton("selectButton"));
	addAndMakeVisible(selectButton.get());
	selectButton->setButtonText(String());
	selectButton->addListener(this);
	selectButton->setBounds(8, 8, 20, 20);

	/* Mute Button */
    muteButton.reset(new ImageButton("muteBotton"));
    addAndMakeVisible(muteButton.get());
    muteButton->setButtonText(TRANS("Mute"));
    muteButton->addListener(this);
    muteButton->setImages(false, true, true,
                          ImageCache::getFromMemory(BinaryData::_033mute_png, BinaryData::_033mute_pngSize), 1.000f,
                          Colours::whitesmoke,
                          Image(), 1.000f, Colours::lightgoldenrodyellow,
                          Image(), 1.000f, Colours::whitesmoke);
    muteButton->setBounds(10, 40, 15, 15);

	/* Solo Button */
    soloButton.reset(new ImageButton("soloButton"));
    addAndMakeVisible(soloButton.get());
    soloButton->setButtonText(TRANS("Solo"));
    soloButton->addListener(this);
    soloButton->setImages(false, true, true,
                          ImageCache::getFromMemory(BinaryData::_048headphones_png, BinaryData::_048headphones_pngSize),
                          1.000f, Colours::whitesmoke,
                          Image(), 1.000f, Colours::lightgoldenrodyellow,
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
							Colours::lightgoldenrodyellow,
                             Image(),
		                      1.000f,
							blueSky);
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
		Colours::lightgoldenrodyellow,
		Image(),
		1.000f,
		blueSky);
	selectInputButton->setBounds(80+35, 40, 15, 15);
}

ChannelComponent::~ChannelComponent()
{
	track.state.removeListener(this);
}

void ChannelComponent::paint(Graphics& g)
{

    g.fillAll(Colour(0xff25292b));

	/* Background */
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
	/* Vol Label */
	{
		int x = 145, y = 1, width = 40, height = 20;
		String text(TRANS("VOL"));
		g.setColour(Colours::whitesmoke);
		g.setFont(Font("Bahnschrift", 10.00f, Font::plain).withTypefaceStyle("Regular"));
		g.drawText(text, x, y, width, height,
			Justification::centred, true);
	}
	/* PAN Label */
	{
		int x = 145, y = 30, width = 40, height = 20;
		String text(TRANS("PAN"));
		g.setColour(Colours::whitesmoke);
		g.setFont(Font("Bahnschrift", 10.00f, Font::plain).withTypefaceStyle("Regular"));
		g.drawText(text, x, y, width, height,
			Justification::centred, true);
	}

	/* Mute Button */
	if (track.isMuted(true))
	{
		//change color if is  Muted
		muteButton->setImages(false, true, true,
			ImageCache::getFromMemory(BinaryData::_033mute_png, BinaryData::_033mute_pngSize), 1.000f,
			blueSky,
			Image(), 1.000f, blueSky,
			Image(), 1.000f, blueSky);
	}
	else
	{
		//change color if is Not Muted
		muteButton->setImages(false, true, true,
			ImageCache::getFromMemory(BinaryData::_033mute_png, BinaryData::_033mute_pngSize), 1.000f,
			Colours::whitesmoke,
			Image(), 1.000f, Colours::lightgoldenrodyellow,
			Image(), 1.000f, Colours::whitesmoke);
	}

	/* Solo Button */
	if (track.isSolo(false))
	{
		//change color if is Not Solo
		soloButton->setImages(false, true, true,
			ImageCache::getFromMemory(BinaryData::_048headphones_png, BinaryData::_048headphones_pngSize), 1.000f,
			blueSky,
			Image(), 1.000f, blueSky,
			Image(), 1.000f, blueSky);
	}
	else
	{
		//change color if is  Solo
		soloButton->setImages(false, true, true,
			ImageCache::getFromMemory(BinaryData::_048headphones_png, BinaryData::_048headphones_pngSize),
			1.000f, Colours::whitesmoke,
			Image(), 1.000f, Colours::lightgoldenrodyellow,
			Image(), 1.000f, Colours::whitesmoke);
	}

	/* Select Button */
	if (engine.isTrackArmed(track))
	{
		selectButton->setColour(TextButton::ColourIds::buttonColourId, orangeJam);

	}
	else
	{
		selectButton->setColour(TextButton::ColourIds::buttonColourId, darkGreyJam);
	}
}

void ChannelComponent::resized()
{
    auto bounds = getLocalBounds();
	
}

void ChannelComponent::buttonClicked(Button* buttonThatWasClicked)
{
	if (buttonThatWasClicked == selectButton.get())
	{
		engine.toggleArm(track);
	}
	else if (buttonThatWasClicked == muteButton.get())
	{
		engine.muteChannel(track);
	}
	else if (buttonThatWasClicked == soloButton.get())
	{
		engine.soloChannel(track);
	}
	else if (buttonThatWasClicked == addFileButton.get())
	{
		clickAddFileButton();
	}
	else if (buttonThatWasClicked == selectInputButton.get())
	{
		engine.inputMonitoring(&track);
	}
	repaint();
}

void ChannelComponent::clickAddFileButton()
{
    auto location = File::getSpecialLocation(File::userDesktopDirectory);
    FileChooser chooser("Choose a file", location, "*.wav", true, false);

    if (chooser.browseForFileToOpen())
    {
        auto file = chooser.getResult();
        engine.addNewClipFromFile(file, track);
		
    }
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

void ChannelComponent::labelTextChanged(Label * labelThatHasChanged)
{
	if (labelThatHasChanged == trackText.get())
	{
		track.setName(trackText->getText());
	}
}

void ChannelComponent::update()
{
	
}





