#pragma once

#include "JuceHeader.h"
#include "TreeComponent.h"
#include "Audio/AudioEngine.h"
#include "AudioTrackThumbnail.h"
#include "PlayHeadComponent.h"

class AudioThumbnailWindow : public TreeComponent
{
public:
	AudioThumbnailWindow(AudioEngine& inEngine);
	~AudioThumbnailWindow();
	void update() override;
	void paint(Graphics& g) override;
private:
	void addNewAudioTrackThumbnail(AudioTrack& audioTrack);
	void clearAudioTrackThumbnails();
	void rebuildTrackThumbnailList();
	int channelY = 0;
	AudioEngine& engine;
	std::vector<std::unique_ptr<AudioTrackThumbnail>> trackThumbnails;

	PlayHeadComponent playhead;
};
