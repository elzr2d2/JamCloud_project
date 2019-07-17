#include "AudioTrackThumbnail.h"

AudioTrackThumbnail::AudioTrackThumbnail( AudioTrack& inTrack):
	track(inTrack)
  {
	startTimerHz(60);

	track.state.addListener(this);
  }

AudioTrackThumbnail::~AudioTrackThumbnail()
{
	track.state.removeListener(this);
}



void AudioTrackThumbnail::update()
{
	rebuildClips();
}

void AudioTrackThumbnail::paint(Graphics & g)
{

}

void AudioTrackThumbnail::resized()
{
	auto bounds = getLocalBounds();

	for (auto& thumbnail : audioThumbnailComponents)
	{
		auto position = thumbnail->getClip().getPosition();

		auto start = position.getStart() / 10 * (double)getWidth();
		auto length = position.getLength() / 10 * (double)getWidth();
		thumbnail->setBounds( start, 0, int(length), 70);

	}
}

void AudioTrackThumbnail::rebuildClips()
{
	audioThumbnailComponents.clear();
	for (auto* clip : track.getClips())
	{
		audioThumbnailComponents.emplace_back();

		auto& newThumbnail = audioThumbnailComponents.back();
		newThumbnail.reset(new AudioThumbnailComponent(*clip));
		addAndMakeVisible(*newThumbnail);
	}

	resized();
}
