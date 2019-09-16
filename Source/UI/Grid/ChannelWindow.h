#pragma once

#include "JuceHeader.h"
#include "Audio/AudioEngine.h"
#include "UI/Helpers/TreeComponent.h"
#include "ChannelComponent.h"

class ChannelWindow : public TreeComponent
{
public:
	ChannelWindow(AudioEngine& inEngine);
	~ChannelWindow();

	void update() override;

private:
    void addNewTrackComponent(AudioTrack& audioTrack);
    void clearChannels();
    void rebuildTrackList();

	AudioEngine& engine;
	std::vector<std::unique_ptr<ChannelComponent>> channels;
    int channelY = 0;
};