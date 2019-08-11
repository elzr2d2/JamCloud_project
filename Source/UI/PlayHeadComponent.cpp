#include "PlayHeadComponent.h"

PlayHeadComponent::PlayHeadComponent(AudioEngine & inEngine ):
	engine(inEngine)
  {
	startTimerHz(60);
	setSize(2, 70 * 5);
  }

void PlayHeadComponent::paint(Graphics & g)
{
	auto yPosition = 0;
	
	g.setColour(Colours::greenyellow);
	
	g.fillRect(0, yPosition, 2, 70*5+20);
}



void PlayHeadComponent::mouseDrag(const MouseEvent &e)
{

}

void PlayHeadComponent::mouseDown(const MouseEvent &e)
{
	//engine.getTransport().setUserDragging(true); 
	

}

void PlayHeadComponent::mouseUp(const MouseEvent &e)
{
	//engine.getTransport().setUserDragging(false);
}


void PlayHeadComponent::timerCallback()
{
	double pos = engine.getTransport().getCurrentPosition();
	double newPos = UiHelper::timeToX(pos);
	if (newPos != xPos)
	{
		xPos = newPos;
		setBounds(xPos, 0, 3, 400);
	}

}
