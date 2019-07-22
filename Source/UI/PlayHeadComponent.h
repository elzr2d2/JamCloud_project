#pragma once

#include "JuceHeader.h"
#include "Audio/AudioEngine.h"
#include "UiHelper.h"

namespace te = tracktion_engine;

class PlayHeadComponent : public Component , private Timer
{
public:
	PlayHeadComponent(AudioEngine& inEngine);

	void paint(Graphics& g) override;
	void mouseDrag(const MouseEvent&) override;
	void mouseDown(const MouseEvent&) override;
	void mouseUp(const MouseEvent&) override;

private:
	void timerCallback() override;

	AudioEngine& engine;
	double xPos = 0;

};