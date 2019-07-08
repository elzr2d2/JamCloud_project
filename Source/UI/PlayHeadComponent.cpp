#include "PlayHeadComponent.h"

PlayHeadComponent::PlayHeadComponent(AudioEngine & inEngine):engine(inEngine)
  {
	startTimerHz(30);
  }

void PlayHeadComponent::paint(Graphics & g)
{
	auto yPosition = 200;
	g.setColour(Colours::orange);
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
	//double t = editViewState.xToTime(e.x, getWidth());
	//edit.getTransport().setCurrentPosition(t);
	

	lastMousePosition = e.position;
	if (lastMousePosition.getX() > 0)
	{
		xPosition = lastMousePosition.getX();
	}
	timerCallback();
	
}

void PlayHeadComponent::mouseDown(const MouseEvent &e)
{
	DBG("mouseDown");
	engine.getTransport().setUserDragging(true);
	mouseDrag(e);
	
}

void PlayHeadComponent::mouseUp(const MouseEvent &)
{
	engine.getTransport().setUserDragging(false);
	
	
}

int PlayHeadComponent::timeToX(double time, int width) const
{
	/*
	 return roundToInt (((time - viewX1) * width) / (viewX2 - viewX1));
	*/
	return 0;
}

double PlayHeadComponent::xToTime(int x, int width) const
{
	/*
	CachedValue<double> viewX1, viewX2, viewY;
	ValueTree state;
	
	viewX1.referTo(state, IDs::viewX1, um, 0);
	viewX2.referTo(state, IDs::viewX2, um, 60);
	*/
	// return (double (x) / width) * (viewX2 - viewX1) + viewX1;
	return (double(x) / width);
	//return 0.0;
}

void PlayHeadComponent::timerCallback()
{
	/*
	    if (firstTimer)
    {
        // On Linux, don't set the mouse cursor until after the Component has appeared
        firstTimer = false;
        setMouseCursor (MouseCursor::LeftRightResizeCursor);
    }
	
    int newX = timeToX (engine.getTransport().getCurrentPosition(), getWidth());
    if (newX != xPosition)
    {
        repaint (jmin (newX, xPosition) - 1, 0, jmax (newX, xPosition) - jmin (newX, xPosition) + 3, getHeight());
        xPosition = newX;
    }
	*/
	if (engine.isPlaying())
	{
		xPosition += 2;
		repaint();
	}
	else
	{
		repaint();
	}


}
