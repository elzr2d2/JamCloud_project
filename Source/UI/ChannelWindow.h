#pragma once

#include "JuceHeader.h"
#include "ChannelComponent.h"
#include "AudioThumbnailComponent.h"
#include "Audio/AudioEngine.h"

class ChannelWindow : public Component, public Timer
{
public:
	ChannelWindow(AudioEngine& inEngine);

	void timerCallback() override;

private:
    void addNewTrackComponent(AudioTrack& audioTrack);
    void clearChannels();
    void rebuildTrackList();

	AudioEngine& engine;
	std::vector<std::unique_ptr<ChannelComponent>> channels;
    int channelY = 0;

};