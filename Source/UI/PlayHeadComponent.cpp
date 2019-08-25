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
	Colour orangeJam = Colour(0xffc39400);
	g.setColour(orangeJam);
	g.fillRect(0, yPosition, 2, 70*5+20);
}



void PlayHeadComponent::mouseDrag(const MouseEvent &e)
{

}

void PlayHeadComponent::mouseDown(const MouseEvent &e)
{

}

void PlayHeadComponent::mouseUp(const MouseEvent &e)
{
	
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
