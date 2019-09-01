#include "ToolbarComponent.h"

ToolbarComponent::ToolbarComponent(AudioEngine& inEngine) :
        engine(inEngine)
{
    startTimerHz(30);

    Colour darkGreyJam = Colour(0xff2c302f);
    Colour orangeJam = Colour(0xffc39400);

    /* Play Button */
    playButton.reset(new ImageButton("playButton"));
    addAndMakeVisible(playButton.get());
    playButton->setButtonText(TRANS("new button"));
    playButton->addListener(this);
    playButton->setImages(false, true, true,
                          ImageCache::getFromMemory(BinaryData::_028play_png, BinaryData::_028play_pngSize), 1.0f,
                          darkGreyJam,
                          Image(), 0.965f, Colours::orange,
                          Image(), 1.0f, darkGreyJam);
    playButton->setBounds(211, 24, 16, 16);

    /* Stop Button */
    stopButton.reset(new ImageButton("stopButton"));
    addAndMakeVisible(stopButton.get());
    stopButton->setButtonText(TRANS("new button"));
    stopButton->addListener(this);
    stopButton->setImages(false, true, true,
                          ImageCache::getFromMemory(BinaryData::_013stop_png, BinaryData::_013stop_pngSize), 1.0f,
                          darkGreyJam,
                          Image(), 1.0f, Colours::orange,
                          Image(), 1.0f, darkGreyJam);
    stopButton->setBounds(243, 24, 16, 16);

    /* Record Button */
    recordButton.reset(new ImageButton("recordButton"));
    addAndMakeVisible(recordButton.get());
    recordButton->setButtonText(TRANS("new button"));
    recordButton->addListener(this);
    recordButton->setImages(false, true, true,
                            ImageCache::getFromMemory(BinaryData::_023record_png, BinaryData::_023record_pngSize), 1.0f,
                            darkGreyJam,
                            Image(), 1.0f, Colours::darkred,
                            Image(), 1.0f, darkGreyJam);
    recordButton->setBounds(275, 24, 16, 16);


    /* Loop Button */
    loopButton.reset(new ImageButton("loopButton"));
    addAndMakeVisible(loopButton.get());
    loopButton->setButtonText(String());
    loopButton->addListener(this);
    loopButton->setImages(false, true, true,
                          ImageCache::getFromMemory(BinaryData::_081loop_png, BinaryData::_081loop_pngSize), 1.0f,
                          darkGreyJam,
                          Image(), 1.0f, Colours::orange,
                          Image(), 1.0f, darkGreyJam);

    loopButton->setBounds(305, 18, 20, 27);

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
    timeText->setText(TRANS("time"));
    timeText->setJustification(Justification::centredLeft);
    timeText->setColour(TextEditor::ColourIds::textColourId, orangeJam);
    timeText->setColour(TextEditor::ColourIds::outlineColourId, Colours::transparentWhite);
    timeText->setFont(Font("Bahnschrift", 20.00f, Font::plain).withTypefaceStyle("Regular"));
    timeText->setBounds(12, 16, 80, 30);


    /* Bpm Text Editor */
    bpmText.reset(new TextEditor("bpmText"));
    addAndMakeVisible(bpmText.get());
    bpmText->setMultiLine(false);
    bpmText->setReturnKeyStartsNewLine(false);
    bpmText->setReadOnly(false);
    bpmText->setScrollbarsShown(false);
    bpmText->setCaretVisible(false);
    bpmText->setPopupMenuEnabled(true);
    bpmText->setColour(TextEditor::backgroundColourId, Colour(0x00000000));
    bpmText->setColour(TextEditor::ColourIds::outlineColourId, Colours::transparentWhite);
    bpmText->setColour(TextEditor::ColourIds::textColourId, orangeJam);
    bpmText->setFont(Font("Bahnschrift", 20.00f, Font::plain).withTypefaceStyle("Regular"));
    bpmText->setText(TRANS("120"));
    bpmText->setBounds(116, 16, 40, 30);

    /* Metronome Button */
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
    metronomeButton->setBounds(352, 20, 20, 20);

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
    playButton = nullptr;
}


void ToolbarComponent::paint(Graphics& g)
{
    Colour darkGreyJam = Colour(0xff2c302f);
    /* Background */
    g.fillAll(Colour(0xff2c2d35));

    /* Light Screen */
    {
        int x = 8, y = 8, width = 156, height = 44;
        Colour lightScreen = Colour(0x258A878B);
        g.setColour(lightScreen);
        g.fillRect(x, y, width, height);
    }
    /* Frame Buttons */
    {
        float x = 204, y = 16, width = 30.0f, height = 30.0f;
        Colour greyFrameButton = Colour(0xff848180);
        g.setColour(greyFrameButton);
        int numOfRectButtons = 4;

        for (int i = 0; i < numOfRectButtons; i++)
        {
            g.fillRoundedRectangle(x, y, width, height, 1.000f);
            x += 32;
        }
        x += 15;
        g.fillRoundedRectangle(x, y, width, height, 20.000f);
    }

    /* littleLine */
    {
        int x = 100, y = 16, width = 1, height = 28;
        Colour littleLineColor = Colour(0xffa7a7a7);
        g.setColour(littleLineColor);
        g.fillRect(x, y, width, height);
    }

    /* Toggle Color For Buttons */
    if (engine.isLooping())
    {
        loopButton->setImages(false, true, true,
                              ImageCache::getFromMemory(BinaryData::_081loop_png, BinaryData::_081loop_pngSize), 1.0f,
                              Colours::orange,
                              Image(), 1.0f, Colours::orange,
                              Image(), 1.0f, Colours::orange);
    }
    else
    {
        loopButton->setImages(false, true, true,
                              ImageCache::getFromMemory(BinaryData::_081loop_png, BinaryData::_081loop_pngSize), 1.0f,
                              darkGreyJam,
                              Image(), 1.0f, Colours::orange,
                              Image(), 1.0f, darkGreyJam);
    }

    if (engine.isRecording())
    {
        recordButton->setImages(false, true, true,
                                ImageCache::getFromMemory(BinaryData::_023record_png, BinaryData::_023record_pngSize),
                                1.0f,
                                Colours::red,
                                Image(), 1.0f, darkGreyJam,
                                Image(), 1.0f, Colours::red);
    }
    else
    {
        recordButton->setImages(false, true, true,
                                ImageCache::getFromMemory(BinaryData::_023record_png, BinaryData::_023record_pngSize),
                                1.0f,
                                darkGreyJam,
                                Image(), 1.0f, Colours::darkred,
                                Image(), 1.0f, darkGreyJam);
    }

    if (engine.isPlaying())
    {
        playButton->setImages(false, true, true,
                              ImageCache::getFromMemory(BinaryData::_031pause_png, BinaryData::_031pause_pngSize), 1.0f,
                              Colours::darkorange,
                              Image(), 0.965f, Colours::orange,
                              Image(), 1.0f, Colours::darkorange);
    }
    else
    {
        playButton->setImages(false, true, true,
                              ImageCache::getFromMemory(BinaryData::_028play_png, BinaryData::_028play_pngSize), 1.0f,
                              darkGreyJam,
                              Image(), 0.965f, Colours::orange,
                              Image(), 1.0f, darkGreyJam);
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
    }
    else if (buttonThatWasClicked == stopButton.get())
    {
        engine.pause();
        engine.stop();
    }
    else if (buttonThatWasClicked == loopButton.get())
    {
        engine.loop();
    }
    else if (buttonThatWasClicked == playButton.get())
    {
        if (!engine.isPlaying())
            engine.play();
        else
            engine.pause();
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
    repaint();
}

void ToolbarComponent::getCurrentTimeText()
{
    auto playheadPos = engine.getTransport().getCurrentPlayhead()->getPosition();
    auto totalTime = roundDoubleToInt(playheadPos);

    seconds = totalTime % 60;
    minutes = totalTime / 60;

    double milSec = playheadPos - totalTime;
    if (milSec < 0)
    {
        seconds = seconds - 1;
        milSec = (milSec * -1) + 0.50;
    }
    milSec *= 100;

    auto sec = std::to_string(seconds);
    auto min = std::to_string(minutes);
    auto ms = std::to_string(roundDoubleToInt(milSec));
    if (seconds < 10)
    {
        timeText->setText("0" + min + ":0" + sec + ":" + ms);
    }
    else
    {
        timeText->setText("0" + min + ":" + sec + ":" + ms);
    }
}

void ToolbarComponent::timerCallback()
{
    getCurrentTimeText();
    setBpm();
}

void ToolbarComponent::setBpm()
{
    engine.setBpm(bpmText->getText().getDoubleValue());
}


