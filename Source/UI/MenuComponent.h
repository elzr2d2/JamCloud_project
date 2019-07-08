#pragma once

#include "JuceHeader.h"
#include "Audio/AudioEngine.h"

class MenuComponent  : public Component,
                       public Button::Listener
{
public:

    MenuComponent (AudioEngine& inEngine);
    ~MenuComponent();

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;

private:

    std::unique_ptr<TextButton> fileButton;
    std::unique_ptr<TextButton> cloudButton;
    std::unique_ptr<TextButton> settingsButton;
    std::unique_ptr<TextButton> userButton;
    std::unique_ptr<Label> logo;

	PopupMenu fileMenu, cloudMenu, settingsMenu , userMenu;
	AudioEngine &engine;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MenuComponent)
};
