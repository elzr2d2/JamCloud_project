
#include "GridComponent.h"

GridComponent::GridComponent (AudioEngine& inEngine) : 
	engine(inEngine),
	channelWindow(inEngine),
	playhead(inEngine)
	
{

	addAndMakeVisible(viewport);
	viewport.setViewedComponent(&playhead,false);
	viewport.setViewedComponent(&channelWindow, false);
	viewport.setScrollBarThickness(10);
	playhead.setVisible(true);
	playhead.toFront(true);

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

	channelWindow.setBounds(0,0,20000,360);
	//channelWindow.setBounds(getLocalBounds());
	playhead.setBounds(getLocalBounds().withTrimmedLeft(200));
	playhead.toFront(true);
	viewport.setBounds(0,0,proportionOfWidth(1.0f), 400);
}

