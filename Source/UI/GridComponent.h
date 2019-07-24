#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Audio/AudioEngine.h"
#include "ChannelWindow.h"
#include "AudioThumbnailWindow.h"


class GridComponent  : public Component
					  
{
public:
  
    GridComponent (AudioEngine& inEngine);
    ~GridComponent();

    void paint (Graphics& g) override;
    void resized() override;

private:

	ChannelWindow channelWindow;
	AudioThumbnailWindow thumbnailsWindow;
	Viewport viewport;
	AudioEngine& engine;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GridComponent)
};
