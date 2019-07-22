
#include "GridComponent.h"

GridComponent::GridComponent (AudioEngine& inEngine) : 
	engine(inEngine),
	channelWindow(inEngine),
	thumbnailsWindow(inEngine)
{

	addAndMakeVisible(channelWindow);
	addAndMakeVisible(viewport);
	viewport.setViewedComponent(&thumbnailsWindow, false);
	viewport.setScrollBarThickness(10);
	
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
	channelWindow.setBounds(0,0,200,360);
	viewport.setBounds(200,0,proportionOfWidth(1.0f), 400);
	thumbnailsWindow.setBounds(0, 0, 60000, 400);

}

