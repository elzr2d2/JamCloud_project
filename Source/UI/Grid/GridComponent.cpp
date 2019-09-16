
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
	//odrder numberrs
	double channelsWindowWidth = 200;
	double channelsWindowHeight = UiHelper::getChannelHeight()*UiHelper::numChannels();
	double offset = 10;
	double timeline = 20;
	double viewportHeight = channelsWindowHeight + timeline + offset;
	double gridWidth = UiHelper::getGridWidth();
	channelWindow.setBounds(0,0, channelsWindowWidth, channelsWindowHeight);
	viewport.setBounds(200,0,proportionOfWidth(0.8f), viewportHeight);
	thumbnailsWindow.setBounds(0, 0, gridWidth, channelsWindowHeight + timeline);
}


