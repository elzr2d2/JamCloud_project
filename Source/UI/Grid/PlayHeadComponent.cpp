#include "PlayHeadComponent.h"

PlayHeadComponent::PlayHeadComponent(AudioEngine & inEngine ):
	engine(inEngine)
  {
	startTimerHz(60);
	int playheadHeight = UiHelper::getPlayheadHeight();
	setSize(3, playheadHeight);
  }

PlayHeadComponent::~PlayHeadComponent()
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

void PlayHeadComponent::paint(Graphics & g)
{
	auto yPosition = 0;
	int Height = UiHelper::getPlayheadHeight();
	Colour orangeJam = Colour(0xffc39400);
	g.setColour(orangeJam);
	g.fillRect(0, yPosition, 3, Height);
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


