#pragma once

#include "JuceHeader.h"
#include "Audio/AudioEngine.h"
#include "AudioTrackThumbnail.h"

class AudioThumbnailWindow : public Component, public Timer
{
public:
	AudioThumbnailWindow(AudioEngine& inEngine);

	void timerCallback() override;
	void paint(Graphics& g) override;
private:

	void addNewAudioTrackThumbnail(AudioTrack& audioTrack);
	void clearAudioTrackThumbnails();
	void rebuildTrackThumbnailList();
	int channelY = 0;
	AudioEngine& engine;
	std::vector<std::unique_ptr<AudioTrackThumbnail>> trackThumbnails;

};
