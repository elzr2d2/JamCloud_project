#pragma once

#include "JuceHeader.h"
#include "ChannelComponent.h"
#include "AudioThumbnailComponent.h"
#include "Audio/AudioEngine.h"
#include "TreeComponent.h"

class AudioTrackThumbnail : public TreeComponent					 
{
public:
	AudioTrackThumbnail(AudioTrack& inTrack);
	~AudioTrackThumbnail();
	void update() override;
	void paint(Graphics& g) override;
	void resized() override;

private:
	void rebuildClips();
	std::vector<std::unique_ptr<AudioThumbnailComponent>> audioThumbnailComponents;
	AudioTrack& track;
	
};