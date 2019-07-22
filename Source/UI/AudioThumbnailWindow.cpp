#include "AudioThumbnailWindow.h"

AudioThumbnailWindow::AudioThumbnailWindow(AudioEngine & inEngine):
	engine(inEngine),
	playhead(inEngine)
{
	startTimerHz(60);
	engine.getEdit()->state.addListener(this);
	addAndMakeVisible(playhead);

}

AudioThumbnailWindow::~AudioThumbnailWindow()
{
	engine.getEdit()->state.removeListener(this);
}

void AudioThumbnailWindow::update()
{
	rebuildTrackThumbnailList();
	playhead.toFront(false);

}


void AudioThumbnailWindow::paint(Graphics& g)
{
	//g.fillAll(Colours::darkgrey);
	
}


void AudioThumbnailWindow::addNewAudioTrackThumbnail(AudioTrack & audioTrack)
{
	trackThumbnails.emplace_back();

	auto& addedTrackThumbnail = trackThumbnails.back();

	addedTrackThumbnail.reset(new AudioTrackThumbnail(audioTrack));

	addAndMakeVisible(*addedTrackThumbnail);

	addedTrackThumbnail->setBounds(0, channelY, getWidth(), 70);
	channelY += 70;
}

void AudioThumbnailWindow::clearAudioTrackThumbnails()
{
	trackThumbnails.clear();
	channelY = 0;
}

void AudioThumbnailWindow::rebuildTrackThumbnailList()
{
	clearAudioTrackThumbnails();
	for (auto * track : engine.getTrackList())
	{
		auto audioTrack = dynamic_cast<AudioTrack*> (track);

		if (audioTrack != nullptr)
			addNewAudioTrackThumbnail(*audioTrack);
	}
	
}
