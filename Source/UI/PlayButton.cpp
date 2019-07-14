#include "PlayButton.h"

PlayButton::PlayButton(AudioEngine& inEngine) : engine(inEngine)
{
    addChildComponent(playButton);
    addChildComponent(pauseButton);

    playButton.setButtonText("play");
    playButton.addListener(this);

    playButton.setImages(false, true, true,
                         ImageCache::getFromMemory(BinaryData::_028play_png, BinaryData::_028play_pngSize), 1.0f, Colours::whitesmoke,
                         Image(), 0.965f, Colours::orange,
                         Image(), 1.0f, Colours::whitesmoke);

    pauseButton.setButtonText("play");
    pauseButton.addListener(this);

    pauseButton.setImages(false, true, true,
                          ImageCache::getFromMemory(BinaryData::_031pause_png, BinaryData::_031pause_pngSize), 1.0f, Colours::darkorange,
                          Image(), 0.965f, Colours::orange,
                          Image(), 1.0f, Colours::darkorange);
}

void PlayButton::resized()
{
    playButton.setBounds(getLocalBounds());
    pauseButton.setBounds(getLocalBounds());
}

void PlayButton::buttonClicked(Button* button)
{
    if (button == &playButton)
        engine.play();
    else
        engine.pause();
}

void PlayButton::paint(Graphics& /*g*/)
{
    pauseButton.setVisible(engine.isPlaying());
    playButton.setVisible(!engine.isPlaying());
}
