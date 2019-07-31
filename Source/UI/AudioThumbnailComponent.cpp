

#include "AudioThumbnailComponent.h"
#include "UiHelper.h"

constexpr int deleteClip = 1;
constexpr int trimClip = 2;
constexpr int copyClip = 3;
AudioThumbnailComponent::AudioThumbnailComponent(tracktion_engine::Clip& inClip) :
        thumbnailCache(5), thumbnail(512, formatManager, thumbnailCache),
        clip(inClip)
{
    formatManager.registerBasicFormats();
    thumbnail.addChangeListener(this);
    initSource();
	
	
}

AudioThumbnailComponent::~AudioThumbnailComponent()
{
    thumbnail.removeChangeListener(this);
}

void AudioThumbnailComponent::paint(Graphics& g)
{
	Rectangle<int> thumbnailBounds(100, 70);
	auto w = UiHelper::timeToX(clip.getMaximumLength());
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

    thumbnail.drawChannels(g, thumbnailBounds, 0.0, thumbnail.getTotalLength(), 1.0f);
	
}

void AudioThumbnailComponent::mouseDown(const MouseEvent& e/*event*/)
{

	if (e.mods.isLeftButtonDown())
	{
		
		selected = !selected;
		dragger.startDraggingComponent(this, e);
		repaint();
	}
	else if (e.mods.isRightButtonDown() && selected)
	{
		PopupMenu menu;
		menu.addItem(1, "Delete");
		menu.addItem(2, "Trim");
		menu.addItem(3, "Copy");
	
		auto result = menu.show();

		switch (result)
		{
		case deleteClip: clip.removeFromParentTrack();
			break;
		case trimClip:
			break;
		case copyClip:
			break;
		default:
			break;
		}
	}


	
}

void AudioThumbnailComponent::mouseDrag(const MouseEvent & e)
{

	dragger.dragComponent(this, e, nullptr);
}

void AudioThumbnailComponent::mouseUp(const MouseEvent & e)
{
	//wants to take the x and change the time
	/*
	auto newPos = UiHelper::xToTime(e.x);
	EditTimeRange timeRange(newPos,  clip.getMaximumLength());
	ClipPosition pos = { timeRange ,0};
	clip.setPosition(pos);
	DBG("MOUSE UP HERE EEE EEE");
	*/
}

void AudioThumbnailComponent::initSource()
{
    File file = clip.getCurrentSourceFile();
    thumbnail.setSource(new FileInputSource(file));

}

