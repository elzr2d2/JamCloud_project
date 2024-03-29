#include "AudioTrackThumbnail.h"
#include "UI/Helpers/UiHelper.h"

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
		auto length = position.getLength();
		auto width = UiHelper::timeToX(length);
		auto start = position.getStart();
		auto stratPos = UiHelper::timeToX(start);

		thumbnail->setBounds(stratPos, 0, width, UiHelper::getChannelHeight());
	}
}

void AudioTrackThumbnail::mouseDown(const MouseEvent &e)
{
	auto newPlayheadPos = e.x;
	track.edit.getTransport().setCurrentPosition(UiHelper::xToTime(newPlayheadPos));

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
