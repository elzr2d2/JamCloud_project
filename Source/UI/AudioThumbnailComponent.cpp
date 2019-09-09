

#include "AudioThumbnailComponent.h"
#include "UiHelper.h"

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
	Rectangle<int> thumbnailBounds(100, 70);
	auto len = clip.getPosition().getLength();
	//auto w = UiHelper::timeToX(clip.getMaximumLength());
	auto w = UiHelper::timeToX(len);
	thumbnailBounds.setSize(w, 70);
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
		g.setColour(Colours::purple);
		g.drawRect(thumbnailBounds, 1);
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
    g.drawFittedText("", thumbnailBounds, Justification::centred, 1);
}

void AudioThumbnailComponent::paintIfFileLoaded(Graphics& g, const Rectangle<int>& thumbnailBounds)
{
	g.setColour(Colours::transparentBlack);
	g.fillRect(thumbnailBounds);
    g.setColour(Colours::darkorange);

	auto start= clip.getPosition().getStart();
	auto end = clip.getPosition().getEnd();
	auto clipLen = clip.getPosition().getLength();
    //thumbnail.drawChannels(g, thumbnailBounds, 0.0, clip.getMaximumLength(), 1.0f);
	//thumbnail.drawChannels(g, thumbnailBounds, start, end, 1.0f);
	DBG(clipLen);
	thumbnail.drawChannels(g, thumbnailBounds, 0.0, clipLen, 1.0f);
}

void AudioThumbnailComponent::mouseDown(const MouseEvent& e/*event*/)
{

	if (e.mods.isLeftButtonDown())
	{
		selected = !selected;
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
		case leftTrim: trimClipFromLeft();
			break;
		case rightTrim: trimClipFromRight();
			break;
		default:
			break;
		}
		repaint();
	}
}

void AudioThumbnailComponent::mouseDrag(const MouseEvent & e)
{

	double y = getPosition().getY();
	auto dis = e.getDistanceFromDragStartX();
	
	if (dis < 0)
	{
		xDrag = e.x;
		xDrag = +dis;
	}
	else
	{
		xDrag = dis;
	}

	if (xDrag >= 0)
	{	
		DBG(xDrag);
		setBounds(xDrag, y, getWidth(), getHeight());
		repaint();
	}
	else
	{
		setBounds(0, y, getWidth(), getHeight());
	}
}

void AudioThumbnailComponent::mouseUp(const MouseEvent & e)
{
	auto x = getPosition().getX();
	double newPos = UiHelper::xToTime(x);
	auto len = clip.getPosition().getLength();
	EditTimeRange timeRange(newPos, len + newPos);
	ClipPosition pos = { timeRange ,0};
	clip.setPosition(pos);
	repaint();
}

void AudioThumbnailComponent::trimClipFromLeft()
{
	/*===try members===*/
	auto playheadPos = clip.edit.getTransport().getCurrentPosition();
	//EditTimeRange etr{ playheadPos,pos };
	//auto end = clip.getPosition().getEnd();
	/*=================*/
	//clip.setStart(pos, true, false);
	//clip.setStart(playheadPos, false, false);
	
	
}

void AudioThumbnailComponent::trimClipFromRight()
{
	auto playheadPos = clip.edit.getTransport().getCurrentPosition();
	clip.setEnd(playheadPos, false);

	auto x = getPosition().getX();
	double newPos = UiHelper::xToTime(x);
	auto len = clip.getPosition().getLength();
	EditTimeRange timeRange(newPos, len + newPos);
	ClipPosition pos = { timeRange ,0 };
	clip.setPosition(pos);
	repaint();

	double y = getPosition().getY();
	 x = getPosition().getX();
	setBounds(x, y, getWidth(), getHeight());
	repaint();

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

