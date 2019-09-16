#pragma once

#include "JuceHeader.h"
#include "AudioThumbnailComponent.h"
#include "Audio/AudioEngine.h"
#include "UI/Helpers/TreeComponent.h"
#include "UI/Helpers/Colors.h"
#include "ChannelComponent.h"

class AudioTrackThumbnail : public TreeComponent					 
{
public:
	AudioTrackThumbnail(AudioTrack& inTrack);
	~AudioTrackThumbnail();

	void update() override;
	void paint(Graphics& g) override;
	void resized() override;
	void mouseDown(const MouseEvent&) override;

private:
	void rebuildClips();

	std::vector<std::unique_ptr<AudioThumbnailComponent>> audioThumbnailComponents;
	AudioTrack& track;
	
};