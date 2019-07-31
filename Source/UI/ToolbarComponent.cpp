#include "ToolbarComponent.h"

ToolbarComponent::ToolbarComponent(AudioEngine& inEngine) :
        playButton(inEngine),
        engine(inEngine)
{
	startTimerHz(30);
	/* Record Button */
    recordButton.reset(new ImageButton("recordButton"));
    addAndMakeVisible(recordButton.get());
    recordButton->setButtonText(TRANS("new button"));
    recordButton->addListener(this);
    recordButton->setImages(false, true, true,
                            ImageCache::getFromMemory(BinaryData::_023record_png, BinaryData::_023record_pngSize), 1.0f,
							Colours::whitesmoke,
							Image(), 1.0f, Colours::darkred,
							Image(), 1.0f, Colours::whitesmoke);
    recordButton->setBounds(384, 39, 16, 19);

	/* Stop Button */
    stopButton.reset(new ImageButton("stopButton"));
    addAndMakeVisible(stopButton.get());
    stopButton->setButtonText(TRANS("new button"));
    stopButton->addListener(this);
	stopButton->setImages(false, true, true,
		ImageCache::getFromMemory(BinaryData::_013stop_png, BinaryData::_013stop_pngSize), 1.0f,
		Colours::whitesmoke,
		Image(), 1.0f, Colours::orange,
		Image(), 1.0f, Colours::darkorange);
    stopButton->setBounds(352, 40, 16, 16);

	/* Play Button */
    addAndMakeVisible(playButton);
    playButton.setBounds(320, 40, 16, 16);

	/* Loop Button */
    loopButton.reset(new ImageButton("loopButton"));
    addAndMakeVisible(loopButton.get());
    loopButton->setButtonText(String());
    loopButton->addListener(this);
    loopButton->setImages(false, true, true,
                          ImageCache::getFromMemory(BinaryData::_081loop_png, BinaryData::_081loop_pngSize), 1.0f,
						Colours::whitesmoke,
						Image(), 1.0f, Colours::orange,
						Image(), 1.0f, Colours::whitesmoke);

    loopButton->setBounds(414, 35, 20, 27);

	/* Time Text Editor */
    timeText.reset(new TextEditor("timeText"));
    addAndMakeVisible(timeText.get());
    timeText->setMultiLine(false);
    timeText->setReturnKeyStartsNewLine(false);
    timeText->setReadOnly(true);
    timeText->setScrollbarsShown(true);
    timeText->setCaretVisible(true);
    timeText->setPopupMenuEnabled(true);
    timeText->setColour(TextEditor::backgroundColourId, Colour(0x00000000));
    timeText->setColour(TextEditor::highlightColourId, Colour(0xb21a574e));
    timeText->setText(TRANS("00 : 00 : 00"));
	timeText->setColour(TextEditor::ColourIds::outlineColourId, Colours::transparentWhite);
    timeText->setBounds(64, 38, 80, 18);

	/* Bpm Text Editor */
    bpmText.reset(new TextEditor("bpmText"));
    addAndMakeVisible(bpmText.get());
    bpmText->setMultiLine(false);
    bpmText->setReturnKeyStartsNewLine(false);
    bpmText->setReadOnly(false);
    bpmText->setScrollbarsShown(true);
    bpmText->setCaretVisible(false);
    bpmText->setPopupMenuEnabled(true);
    bpmText->setColour(TextEditor::backgroundColourId, Colour(0x00000000));
    bpmText->setText(TRANS("120"));
	bpmText->setColour(TextEditor::ColourIds::outlineColourId, Colours::transparentWhite);
    bpmText->setBounds(64, 58, 80, 16);

	/* Metronome Button */
    metronomeButton.reset(new ImageButton("metronomeButton"));
    addAndMakeVisible(metronomeButton.get());
	metronomeButton->setButtonText(TRANS("new button"));
	metronomeButton->addListener(this);
	metronomeButton->setImages(false, true, true,
                                ImageCache::getFromMemory(BinaryData::_010triangle_png,
                                                          BinaryData::_010triangle_pngSize), 1.0f, 
											   Colours::whitesmoke,
                                Image(), 1.0f, Colours::orange,
                                Image(), 1.0f, Colours::whitesmoke);
	metronomeButton->setBounds(456, 35, 25, 23);

    setSize(1000, 500);
}

ToolbarComponent::~ToolbarComponent()
{
    recordButton = nullptr;
    stopButton = nullptr;
    loopButton = nullptr;
    timeText = nullptr;
    bpmText = nullptr;
    metronomeButton = nullptr;
}


void ToolbarComponent::paint(Graphics& g)
{


    g.fillAll(Colour(0xff25292b));

    {
        int x = 0, y = 0, width = proportionOfWidth(1.0f), height = 100;
        Colour fillColour = Colour(0xff162f30);
        g.setColour(fillColour);
        g.fillRect(x, y, width, height);
    }

    {
        float x = 6.0f, y = 6.0f, width = 180.0f, height = 90.0f;
        Colour fillColour1 = Colour(0xff1d1d1d), fillColour2 = Colour(0xff292a2a);
        g.setGradientFill(ColourGradient(Colours::black,
                                         104.0f - 12.0f + x,
                                         24.0f - 12.0f + y,
                                         fillColour2,
                                         static_cast<float> (-8) - 12.0f + x,
                                         112.0f - 12.0f + y,
                                         false));
        g.fillRoundedRectangle(x, y, width, height, 10.0f);
    }


    {
        int x = 20, y = 20, width = 156, height = 18;
        String text(TRANS("Project Name"));
        Colour fillColour = Colours::white;
        g.setColour(fillColour);
        g.setFont(Font("levenim MT", 20.0f, Font::plain).withTypefaceStyle("Bold"));
        g.drawText(text, x, y, width, height,
                   Justification::bottomLeft, true);
    }

    {
        int x = 20, y = 40, width = 50, height = 18;
        String text(TRANS("Time : "));
        Colour fillColour = Colours::white;
        g.setColour(fillColour);
        g.setFont(Font("levenim MT", 20.0f, Font::plain).withTypefaceStyle("Bold"));
        g.drawText(text, x, y, width, height,
                   Justification::bottomLeft, true);
    }

    {
        int x = 20, y = 60, width = 50, height = 18;
        String text(TRANS("BPM : "));
        Colour fillColour = Colours::white;
        g.setColour(fillColour);
        g.setFont(Font("levenim MT", 20.0f, Font::plain).withTypefaceStyle("Bold"));
        g.drawText(text, x, y, width, height,
                   Justification::bottomLeft, true);
    }

    {
        float x = 310.0f, y = 30.0f, width = 137.0f, height = 36.0f;
        Colour fillColour = Colour(0xf2275353);
        Colour strokeColour = Colour(0xff202e2e);

        g.setColour(fillColour);
        g.fillRoundedRectangle(x, y, width, height, 10.0f);
        g.setColour(strokeColour);
        g.drawRoundedRectangle(x, y, width, height, 10.0f, 1.0f);
    }

}

void ToolbarComponent::resized()
{
	
}

void ToolbarComponent::buttonClicked(Button* buttonThatWasClicked)
{
	if (buttonThatWasClicked == recordButton.get())
	{
		engine.recording();
		if (engine.isRecording())
		{
			recordButton->setImages(false, true, true,
				ImageCache::getFromMemory(BinaryData::_023record_png, BinaryData::_023record_pngSize), 1.0f,
				Colours::red,
				Image(), 1.0f, Colours::lightgrey,
				Image(), 1.0f, Colours::red);
		}
		else 
		{
			recordButton->setImages(false, true, true,
				ImageCache::getFromMemory(BinaryData::_023record_png, BinaryData::_023record_pngSize), 1.0f,
				Colours::whitesmoke,
				Image(), 1.0f, Colours::darkred,
				Image(), 1.0f, Colours::whitesmoke);
		}

	}

	else if (buttonThatWasClicked == stopButton.get())
	{
		engine.pause();
		engine.stop();
	}
	else if (buttonThatWasClicked == loopButton.get())
	{

		
	}
	else if (buttonThatWasClicked == metronomeButton.get())
	{
		setBpm();

		if (!metroGui.getStatePlay())
		{
			metroGui.setStatePlay(true);
		}
		else
		{
			metroGui.setStatePlay(false);
		}


		
	}

}

void ToolbarComponent::getCurrentTimeText()
{
	auto playheadPos = engine.getTransport().getCurrentPlayhead()->getPosition();
	auto totalTime = roundDoubleToInt(playheadPos);

	seconds = totalTime % 60;
	minutes = totalTime / 60;

	auto  sec = std::to_string(seconds);
	auto  min = std::to_string(minutes);
	
	if (seconds < 10)
	{
		timeText->setText("0" + min + ":0" + sec);
	}
	else
	{
		timeText->setText("0" + min + ":" + sec);
	}



}

void ToolbarComponent::timerCallback()
{
	getCurrentTimeText();
	setBpm();
}

void ToolbarComponent::setBpm()
{
	//metroGui.setBpm(bpmText->getText().getDoubleValue());
	engine.setBpm(bpmText->getText().getDoubleValue());
}


