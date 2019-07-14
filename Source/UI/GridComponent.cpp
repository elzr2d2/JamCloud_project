
#include "GridComponent.h"

GridComponent::GridComponent (AudioEngine& inEngine) : 
	engine(inEngine),
	channelWindow(inEngine),
	playhead(inEngine)
	
{

	addAndMakeVisible(viewport);

	viewport.setViewedComponent(&channelWindow, false);
	//viewport.setViewedComponent(&playhead, false);
	viewport.setScrollBarThickness(10);
	channelWindow.setVisible(true);

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
	playhead.setBounds(300, 0, 20000, 360);
	viewport.setBounds(0,0,proportionOfWidth(1.0f), 400);
}

