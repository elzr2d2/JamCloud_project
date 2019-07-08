#pragma once

#include "JuceHeader.h"
#include "Audio/AudioEngine.h"

class PlayButton: public Component, public Button::Listener
{
public:
    PlayButton(AudioEngine& inEngine);

    void resized() override;
    void paint(Graphics& g) override;
    void buttonClicked(Button* button) override;
private:
    AudioEngine& engine;

    ImageButton playButton;
    ImageButton pauseButton;
};