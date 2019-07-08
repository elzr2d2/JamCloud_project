#pragma once

#include "JuceHeader.h"
#include "Audio/AudioEngine.h"

class PlayHeadComponent : public Component , private Timer
{
public:
	PlayHeadComponent(AudioEngine& inEngine);
	void paint(Graphics& g) override;
	bool hitTest(int x, int y) override;
	void mouseDrag(const MouseEvent&) override;
	void mouseDown(const MouseEvent&) override;
	void mouseUp(const MouseEvent&) override;
	int timeToX(double time, int width) const;
	double xToTime(int x, int width) const;
private:
	AudioEngine& engine;

	void timerCallback() override;
	int xPosition = 0;
	bool firstTimer = true;
	Point<float> lastMousePosition;
};