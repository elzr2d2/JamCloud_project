#pragma once

#include "JuceHeader.h"
#include "Audio/AudioEngine.h"
#include "UI/helpers/UiHelper.h"

namespace te = tracktion_engine;

class PlayHeadComponent : public Component,
						  public Timer
{
public:
	PlayHeadComponent(AudioEngine& inEngine);
	~PlayHeadComponent();

	void timerCallback() override;
	void paint(Graphics& g) override;
	void mouseDrag(const MouseEvent&) override;
	void mouseDown(const MouseEvent&) override;
	void mouseUp(const MouseEvent&) override;

private:
	
	double xPos = 0;
	AudioEngine& engine;
	

};