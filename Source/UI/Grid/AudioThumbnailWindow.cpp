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
	repaint();
	playhead.toFront(true);
}

void AudioThumbnailWindow::valueTreeChanged()
{
	auto bpmChanged = engine.isBpmChange;
	if (bpmChanged)
	{
		markForUpdate();
		engine.setBpmChange(false);
	}
}

void AudioThumbnailWindow::paint(Graphics& g)
{

	{
		float x = 0.0f, y = 0.0f, width = static_cast<float> (proportionOfWidth(1.0000f)), height = static_cast<float> (proportionOfHeight(1.0000f));

		Colour greyJam = Colour(0x5C666666);
		Colour blackJam = Colour(0x5c000000);
		double channelsHeight = channelHeight;
		
		/* Draw grey channels */
		for (int i = 0; i < numOfChannels; i++)
		{
			g.setColour(greyJam);
			g.fillRoundedRectangle(x, y, width, channelsHeight, 10.000f);
			channelsHeight += channelHeight;
	
		}
		/* Draw Timeline */
		
		y = channelHeight * numOfChannels *1.0;
		
		height = 20;
		g.setColour(blackJam);
		g.fillRoundedRectangle(x, y, width, height, 5.000f);

	}

	{
		int lineX = 0, lineY = 0, lineWidth = 1, lineHeight = proportionOfHeight(1.0000f);
		int barNumberY = 70 * 5, barNumberWidth = 30,barNumberHeight = 20;
		Colour mellowGrey = Colour(0xff787d79);
		auto beats = UiHelper::getNumOfBeats(engine.getTempoSetting().getBpm());
		int beatDistance = UiHelper::getBeatDistanceByBPM(engine.getTempoSetting().getBpm());

		
		for (int i = 0; i < beats; i++)
		{
			/* Draw the grid lines */
			if (i != 0) {
				g.setColour(mellowGrey);
				g.fillRect(lineX, lineY, lineWidth, lineHeight);
			}

			/* Write bar numbers */
			String bars = std::to_string(i+1);
			g.setColour(Colours::whitesmoke);
			g.setFont(Font("Bahnschrift", 13.10f, Font::plain).withTypefaceStyle("Regular"));
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
	addedTrackThumbnail->setBounds(0, channelY, getWidth(), channelHeight);
	channelY += channelHeight;
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
}
