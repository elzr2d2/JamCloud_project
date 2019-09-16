#pragma once

#include "JuceHeader.h"
#include "Audio/AudioEngine.h"
#include "UI/Helpers/TreeComponent.h"
#include "UI/Helpers/UiHelper.h"
#include "MetronomeGuiComponent.h"

class ToolbarComponent : public TreeComponent,
                         public Button::Listener,
						 public Slider::Listener               
{
public:

    ToolbarComponent(AudioEngine& inEngine);
    ~ToolbarComponent();

    void paint(Graphics& g) override;
    void resized() override;
    void buttonClicked(Button* buttonThatWasClicked) override;

    void getCurrentTimeText();
  
	void update() override;
	void valueTreeChanged() override { markForUpdate(); };
	void sliderValueChanged(Slider* sliderThatWasMoved) override;

private:
	MetronomeGuiComponent metronomeButton;

    std::unique_ptr<ImageButton> recordButton;
    std::unique_ptr<ImageButton> stopButton;
    std::unique_ptr<ImageButton> loopButton;
    std::unique_ptr<ImageButton> playButton;


	std::unique_ptr<Slider> masterVolSlider;
	std::unique_ptr<Slider> bpmSlider;

	std::unique_ptr<TextEditor> timeText;
    int minutes = 0;
    int seconds = 0;

    AudioEngine& engine;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ToolbarComponent)
};

