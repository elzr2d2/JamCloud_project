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
		Colour fillColour2 = Colour(0x5C666666);
		int h = 70;
		for (int i = 0; i < 5; i++)
		{
			g.setColour(fillColour2);
			g.fillRoundedRectangle(x, y, width, h, 10.000f);
			h += 70;
		}
		
		g.setColour(fillColour);
		g.fillRoundedRectangle(x, 70*5, width, 20, 10.000f);
	}

	{
		int x = 0, y = 0, width = 1, height = proportionOfHeight(1.0000f);
		Colour fillColour = Colour(0xff787d79);
		g.setColour(fillColour);

		int numOfBars = 1;
		
		for (int i = 0; i < 600; i++)
		{
			if (x < 100)
			{
				String bars = std::to_string(numOfBars);
				g.setColour(Colours::white);
				g.drawText(bars, x, 70 * 5, 20, 18,
					Justification::centred, true);
				x += UiHelper::getBeatDistanceByBPM(120);
				numOfBars++;
			}
			g.setColour(fillColour);
			g.fillRect(x, y, width, height);

			g.setColour(Colours::white);
			String bars = std::to_string(numOfBars);
			g.drawText(bars, x, 70 * 5, 20, 18,
				Justification::centred, true);
			x += UiHelper::getBeatDistanceByBPM(120);
			numOfBars++;

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
