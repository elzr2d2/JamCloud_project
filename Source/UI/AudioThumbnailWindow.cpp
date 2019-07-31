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
	repaint();

}


void AudioThumbnailWindow::paint(Graphics& g)
{

	{
		float x = 0.0f, y = 0.0f, width = static_cast<float> (proportionOfWidth(1.0000f)), height = static_cast<float> (proportionOfHeight(1.0000f));
		Colour fillColour = Colour(0x5c000000);
		Colour greyJam = Colour(0x5C666666);
		int h = 70;
		/* Draw grey channels */
		for (int i = 0; i < 5; i++)
		{
			g.setColour(greyJam);
			g.fillRoundedRectangle(x, y, width, h, 10.000f);
			h += 70;
		}
		/* Draw Frame */
		g.setColour(fillColour);
		g.fillRoundedRectangle(x, 70*5, width, 20, 10.000f);
	}

	{
		int lineX = 0, lineY = 0, lineWidth = 1, lineHeight = proportionOfHeight(1.0000f);
		int barNumberY = 70 * 5, barNumberWidth = 30,barNumberHeight = 20;
		Colour mellowGrey = Colour(0xff787d79);
		auto beats = UiHelper::getNumOfBeats(engine.getBpm());
		double beatDistance = UiHelper::getBeatDistanceByBPM(engine.getBpm());

		
		for (int i = 0; i < beats; i++)
		{
			/* Draw the grid lines */
			g.setColour(mellowGrey);
			g.fillRect(lineX,lineY, lineWidth, lineHeight);
			/* Write bar numbers */
			String bars = std::to_string(i+1);
			g.setColour(Colours::white);
			g.drawText(bars, lineX+1, barNumberY, barNumberWidth, barNumberHeight,
				Justification::left, true);
			lineX += beatDistance;
		}

	}
	
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

void AudioThumbnailWindow::mouseDown(const MouseEvent &e)
{
	auto newPlayheadPos = e.x;
	engine.getTransport().setCurrentPosition(UiHelper::xToTime(newPlayheadPos));
	UiHelper::xToTime(newPlayheadPos);
}
