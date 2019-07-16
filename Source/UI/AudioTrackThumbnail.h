#pragma once

#include "JuceHeader.h"
#include "ChannelComponent.h"
#include "AudioThumbnailComponent.h"
#include "Audio/AudioEngine.h"

class AudioTrackThumbnail : public Component, 
							 public Timer,
							 private te::ValueTreeAllEventListener
{
public:
	AudioTrackThumbnail(AudioEngine& inEngine, AudioTrack& inTrack);

	void timerCallback() override;
	void paint(Graphics& g) override;
	void resized() override;

private:
	void valueTreeChildAdded(juce::ValueTree&, juce::ValueTree&) override { engine.markForUpdate(); }
	void valueTreeChildRemoved(juce::ValueTree&, juce::ValueTree&, int) override { engine.markForUpdate(); }
	void valueTreeChanged() override {};
	void rebuildClips();

	std::vector<std::unique_ptr<AudioThumbnailComponent>> audioThumbnailComponents;
	AudioEngine& engine;
	AudioTrack& track;
};