#pragma once

#include "JuceHeader.h"
#include "Audio/AudioEngine.h"
#include "PlayButton.h"
#include "MetronomeGuiComponent.h"

class ToolbarComponent  : public Component,
                          public Button::Listener,
					      public Timer
{
public:

    ToolbarComponent (AudioEngine& inEngine);
    ~ToolbarComponent();

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;

	void getCurrentTimeText();
	void timerCallback() override;
private:

    std::unique_ptr<ImageButton> recordButton;
    std::unique_ptr<ImageButton> stopButton;
    std::unique_ptr<ImageButton> loopButton;
    std::unique_ptr<TextEditor> timeText;
    std::unique_ptr<TextEditor> bpmText;
    std::unique_ptr<ImageButton> metronomeButton;
	
	MetronomeGuiComponent metroGui;

	int minutes = 0;
	int seconds = 0;

    PlayButton playButton;

    AudioEngine& engine;
	

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ToolbarComponent)
};

