#pragma once

#include "JuceHeader.h"
#include "Audio/AudioEngine.h"
#include "MetronomeGuiComponent.h"
#include "TreeComponent.h"
#include "UiHelper.h"
#include "MetronomeGuiComponent.h"

class ToolbarComponent : public TreeComponent,
                         public Button::Listener,
						public ComboBox::Listener,
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
    void setBpm();

	void comboBoxChanged(ComboBox* comboBoxThatHasChanged) override;
	void sliderValueChanged(Slider* sliderThatWasMoved) override;

private:

    std::unique_ptr<ImageButton> recordButton;
    std::unique_ptr<ImageButton> stopButton;
    std::unique_ptr<ImageButton> loopButton;
    std::unique_ptr<ImageButton> metronomeButton;
    std::unique_ptr<ImageButton> playButton;
    std::unique_ptr<TextEditor> timeText;
    std::unique_ptr<TextEditor> bpmText;
    MetronomeGuiComponent metroGui;
	std::unique_ptr<Slider> masterVolSlider;
	std::unique_ptr<ComboBox> zoomComboBox;
    int minutes = 0;
    int seconds = 0;
	MetronomeGuiComponent mgc;
    AudioEngine& engine;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ToolbarComponent)
};

