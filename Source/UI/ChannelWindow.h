#pragma once

#include "JuceHeader.h"
#include "Audio/AudioEngine.h"
#include "ChannelComponent.h"
#include "TreeComponent.h"

class ChannelWindow : public TreeComponent
					  
{
public:
	ChannelWindow(AudioEngine& inEngine);

	void update() override;

private:
    void addNewTrackComponent(AudioTrack& audioTrack);
    void clearChannels();
    void rebuildTrackList();

	AudioEngine& engine;
	std::vector<std::unique_ptr<ChannelComponent>> channels;
    int channelY = 0;
};