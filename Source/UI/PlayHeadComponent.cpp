#include "PlayHeadComponent.h"

PlayHeadComponent::PlayHeadComponent(AudioEngine & inEngine ):
	engine(inEngine)
  {
	
	startTimerHz(30);
  }

void PlayHeadComponent::paint(Graphics & g)
{
	auto yPosition = 200;
	g.setColour(Colours::yellow);
	g.drawRect(xPosition, 0, 2, 70*5);

}

bool PlayHeadComponent::hitTest(int x, int y)
{
	if (std::abs(x - xPosition) <= 3)
		return true;
	return false;
}

void PlayHeadComponent::mouseDrag(const MouseEvent &e)
{
	
	double t = xToTime(e.x, getWidth());
	engine.getTransport().setCurrentPosition(t);
	timerCallback();
	
}

void PlayHeadComponent::mouseDown(const MouseEvent &e)
{
	engine.getTransport().setUserDragging(true);
}

void PlayHeadComponent::mouseUp(const MouseEvent &)
{
	engine.getTransport().setUserDragging(false);
}

void PlayHeadComponent::timerCallback()
{
	
	if (firstTimer)
	{
		// On Linux, don't set the mouse cursor until after the Component has appeared
		firstTimer = false;
		setMouseCursor(MouseCursor::LeftRightResizeCursor);
	}

	int newX = timeToX(engine.getTransport().getCurrentPosition(), getWidth());
	if (newX != xPosition)
	{
		repaint(jmin(newX, xPosition) - 1, 0, jmax(newX, xPosition) - jmin(newX, xPosition) + 3, getHeight());
		xPosition = newX;
	}
	

}
