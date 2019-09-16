#include "AudioThumbnailComponent.h"

constexpr int deleteClip = 1;
constexpr int leftTrim = 2;
constexpr int rightTrim = 3;

AudioThumbnailComponent::AudioThumbnailComponent(tracktion_engine::Clip& inClip) :
        thumbnailCache(5), thumbnail(512, formatManager, thumbnailCache),
        clip(inClip)
{
    formatManager.registerBasicFormats();
    thumbnail.addChangeListener(this);
    initSource();
	clip.state.addListener(this);
}

AudioThumbnailComponent::~AudioThumbnailComponent()
{
    thumbnail.removeChangeListener(this);
	clip.state.removeListener(this);
}

void AudioThumbnailComponent::paint(Graphics& g)
{
	auto clipLength = clip.getPosition().getLength();
	auto thumbnailWidth = UiHelper::timeToX(clipLength);
	thumbnailBounds.setSize(thumbnailWidth, UiHelper::getChannelHeight());

	if (!selected)
	{
		g.setColour(Colours::transparentWhite);
		g.fillRect(thumbnailBounds);
	}
	else
	{
		thumbnailBounds.~Rectangle();
	}
    

    if (thumbnail.getNumChannels() == 0)
        paintIfNoFileLoaded(g, thumbnailBounds);
    else
        paintIfFileLoaded(g, thumbnailBounds);
	
	if (selected)
	{
		g.setColour(Colours::lightgoldenrodyellow);
		g.drawRect(thumbnailBounds, 1);
	}
	else
	{
		g.setColour(Colours::transparentWhite);
		g.fillRect(thumbnailBounds);
	}
}



void AudioThumbnailComponent::changeListenerCallback(ChangeBroadcaster* source)
{
    if (source == &thumbnail)
        thumbnailChanged();
}

void AudioThumbnailComponent::thumbnailChanged()
{
    repaint();
}

void AudioThumbnailComponent::paintIfNoFileLoaded(Graphics& g, const Rectangle<int>& thumbnailBounds)
{
    g.fillAll(Colours::red);
    g.drawFittedText("File Error", thumbnailBounds, Justification::centred, 1);
}

void AudioThumbnailComponent::paintIfFileLoaded(Graphics& g, const Rectangle<int>& thumbnailBounds)
{

	g.setColour(Colours::transparentBlack);
	g.fillRect(thumbnailBounds);
	g.setColour(Colours::darkorange);

	
	auto clipLen = clip.getPosition().getLength();

	thumbnail.drawChannels(g, thumbnailBounds, 0.0, clipLen, 1.0f);	
}

void AudioThumbnailComponent::mouseDown(const MouseEvent& e/*event*/)
{


	if (e.mods.isLeftButtonDown())
	{
		selected = !selected;
		mouseDownWithinTarget = e.getEventRelativeTo(this).getMouseDownPosition();

	}
	else if (e.mods.isRightButtonDown() && selected)
	{
		PopupMenu menu;
		menu.addItem(1, "Delete");
		menu.addItem(2, "Trim From Left");
		menu.addItem(3, "Trim From Right");

		auto result = menu.show();

		switch (result)
		{
		case deleteClip: clip.removeFromParentTrack();
			break;
		case leftTrim:	 trimClipFromLeft();
			break;
		case rightTrim:  trimClipFromRight();
			break;
		default:
			break;
		}
		
	}
}

void AudioThumbnailComponent::mouseDrag(const MouseEvent & e)
{
	/* moves the thumbnail ui */
	auto bounds = getBounds();
	bounds += e.getEventRelativeTo(this).getPosition() - mouseDownWithinTarget;
	bounds.setY(0);
	if (bounds.getX() <= 0)
		bounds.setX(0);
	setBounds(bounds);

	/* moves the thumbnail audio */
	auto x = getPosition().getX();
	double newPos = UiHelper::xToTime(x);

	auto clipLength = clip.getPosition().getLength();
	EditTimeRange timeRange(newPos, clipLength + newPos);
	ClipPosition clipPosition = { timeRange ,0 };
	clip.setPosition(clipPosition);
	
}

void AudioThumbnailComponent::mouseUp(const MouseEvent & e)
{
	repaint();
}

bool AudioThumbnailComponent::isPlayheadOnThumbnail()
{
	auto playheadPos = clip.edit.getTransport().getCurrentPosition();
	auto start = clip.getPosition().getStart();
	auto end = clip.getPosition().getEnd();

	return playheadPos < end && playheadPos > start;
}

void AudioThumbnailComponent::trimClipFromLeft()
{
	auto playheadPos = clip.edit.getTransport().getCurrentPosition();
	auto start = clip.getPosition().getStart();
	auto end = clip.getPosition().getEnd();

	if (playheadPos < end && playheadPos > start)
	{

		
	}
	else
	{
		AlertWindow::showMessageBox(AlertWindow::AlertIconType::NoIcon, "Trim not Succeed", "triming is possible only when the playhead is on the wav form");
	}
}

void AudioThumbnailComponent::trimClipFromRight()
{
	auto playheadPos = clip.edit.getTransport().getCurrentPosition();
	auto start = clip.getPosition().getStart();
	auto end = clip.getPosition().getEnd();

	if (isPlayheadOnThumbnail())
	{
		clip.setEnd(playheadPos, false);
		auto x = getPosition().getX();
		double newPos = UiHelper::xToTime(x);
		auto len = clip.getPosition().getLength();
		EditTimeRange timeRange(newPos, len + newPos);
		ClipPosition pos = { timeRange ,0 };
		clip.setPosition(pos);
		

		double y = getPosition().getY();
		x = getPosition().getX();
		setBounds(x, y, getWidth(), getHeight());
		repaint();
	}
	else
	{
		AlertWindow::showMessageBox(AlertWindow::AlertIconType::NoIcon, "Trim not Succeed", "triming is possible only when the playhead is on the wav form");
	}
}

void AudioThumbnailComponent::update()
{
	repaint();
}

void AudioThumbnailComponent::initSource()
{
    File file = clip.getCurrentSourceFile();
    thumbnail.setSource(new FileInputSource(file));
}

