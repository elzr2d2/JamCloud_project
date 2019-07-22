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
	
	g.setColour(Colours::purple);
	
	g.fillRect(0, yPosition, 2, 70*5);
}



void PlayHeadComponent::mouseDrag(const MouseEvent &e)
{
	xPos = e.x;
	timerCallback();
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
	if (engine.isPlaying() || engine.isRecording())
	{
		double pos = engine.getTransport().getCurrentPosition();
		double newPos = UiHelper::timeToX(pos);
		xPos = newPos;	
	}
	
	setBounds(xPos, 0, 3, 400);
		
}
