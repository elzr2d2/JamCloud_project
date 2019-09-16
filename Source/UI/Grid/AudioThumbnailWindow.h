#pragma once

#include "JuceHeader.h"
#include "Audio/AudioEngine.h"
#include "AudioTrackThumbnail.h"
#include "UI/Helpers/TreeComponent.h"
#include "UI/Helpers/UiHelper.h"
#include "PlayHeadComponent.h"

class AudioThumbnailWindow : public TreeComponent
{
public:
	AudioThumbnailWindow(AudioEngine& inEngine);
	~AudioThumbnailWindow();

	void update() override;
	void valueTreeChanged() override;
	void paint(Graphics& g) override;

private:
	void addNewAudioTrackThumbnail(AudioTrack& audioTrack);
	void clearAudioTrackThumbnails();
	void rebuildTrackThumbnailList();
	void mouseDown(const MouseEvent&) override;

	int channelY = 0;
	AudioEngine& engine;
	std::vector<std::unique_ptr<AudioTrackThumbnail>> trackThumbnails;
	PlayHeadComponent playhead;
};
