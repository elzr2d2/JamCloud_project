
#include "GridComponent.h"

GridComponent::GridComponent (AudioEngine& inEngine) : 
	engine(inEngine),
	channelWindow(inEngine),
	playhead(inEngine)
{
	addAndMakeVisible(playhead);
	addAndMakeVisible(channelWindow);

    setSize (600, 400);
}

GridComponent::~GridComponent()
{

}

void GridComponent::paint (Graphics& g)
{
	   g.fillAll (Colour(0xff25292b));
}

void GridComponent::resized()
{
	channelWindow.setBounds(getLocalBounds());
	playhead.setBounds(getLocalBounds().withTrimmedLeft(200));
	playhead.toFront(true);
}

