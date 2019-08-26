#pragma once

#include "JuceHeader.h"
#include "Audio/AudioEngine.h"
#include "TreeComponent.h"
#include "UiHelper.h"
class ChannelComponent : public TreeComponent,
                         public Button::Listener,
                         public Slider::Listener
                         
                         
{
public:

    ChannelComponent(AudioEngine& inEngine, AudioTrack& inTrack);
	~ChannelComponent();
    void paint(Graphics& g) override;
    void resized() override;
    void buttonClicked(Button* buttonThatWasClicked) override;
    void sliderValueChanged(Slider* sliderThatWasMoved) override;
    bool isSelected() { return selected; };

	void update() override;

private:
  
    void clickSelectButton() const;
    void clickAddFileButton();
    void valueTreeChanged() override {};
	
	Colour getArmedTrackColor() const;

    std::unique_ptr<TextButton>  selectButton;
    std::unique_ptr<TextEditor>  nameText;
    std::unique_ptr<Slider>		 volumeSlider, panSlider;
    std::unique_ptr<ImageButton> muteButton, soloButton, addFileButton, selectInputButton;
	std::unique_ptr<Label>		 volLabel, panLabel;
	

    AudioEngine& engine;
    AudioTrack& track;

    bool selected = false;

};