#pragma once

#include "JuceHeader.h"
#include "Audio/AudioEngine.h"
#include "UI/Helpers/TreeComponent.h"
#include "UI/Helpers/UiHelper.h"
#include "UI/Helpers/Colors.h"

class ChannelComponent : public TreeComponent,
                         public Button::Listener,
                         public Slider::Listener,
						public Label::Listener		
{
public:
    ChannelComponent(AudioEngine& inEngine, AudioTrack& inTrack);
	~ChannelComponent();

    void paint(Graphics& g) override;
    void resized() override;

    void buttonClicked(Button* buttonThatWasClicked) override;
    void sliderValueChanged(Slider* sliderThatWasMoved) override;
	void labelTextChanged(Label* labelThatHasChanged) override;
    bool isSelected() { return selected; };

	void update() override;

private:
    void clickAddFileButton();

    std::unique_ptr<TextButton>  selectButton;
    std::unique_ptr<Slider>		 volumeSlider, panSlider;
    std::unique_ptr<ImageButton> muteButton, soloButton, addFileButton, selectInputButton;
	std::unique_ptr<Label>		 volLabel, panLabel;
	std::unique_ptr<Label>		 trackText;

    AudioEngine& engine;
    AudioTrack& track;
    bool selected = false;
};