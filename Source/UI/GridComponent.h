#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Audio/AudioEngine.h"
#include "PlayHeadComponent.h"
#include "ChannelWindow.h"

class GridComponent  : public Component
{
public:
  
    GridComponent (AudioEngine& inEngine);
    ~GridComponent();

    void paint (Graphics& g) override;
    void resized() override;

private:
	/*
	Viewport viewport;
	OR
	std::unique_ptr<Viewport> viewport;

	i dont know.......
	*/
	ChannelWindow channelWindow;
	PlayHeadComponent playhead;
	AudioEngine& engine;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GridComponent)
};
