#pragma once

#include "JuceHeader.h"
#include "Audio/AudioEngine.h"

namespace HelpersIDs
{
#define DECLARE_ID(name)  const juce::Identifier name (#name);
	DECLARE_ID(EDITVIEWSTATE)
	DECLARE_ID(viewX1)
	DECLARE_ID(viewX2)
	DECLARE_ID(viewY)
#undef DECLARE_ID
}
namespace te = tracktion_engine;

class PlayHeadComponent : public Component , private Timer
{
public:
	PlayHeadComponent(AudioEngine& inEngine);

	void paint(Graphics& g) override;
	bool hitTest(int x, int y) override;
	void mouseDrag(const MouseEvent&) override;
	void mouseDown(const MouseEvent&) override;
	void mouseUp(const MouseEvent&) override;

	int timeToX(double time, int width) const
	{
		return roundToInt(((time - viewX1) * width) / (viewX2 - viewX1));
	}

	double xToTime(int x, int width) const
	{
		return (double(x) / width) * (viewX2 - viewX1) + viewX1;
	}

private:
	void timerCallback() override;

	AudioEngine& engine;

	int xPosition = 200;
	bool firstTimer = true;

	/* new Varebles */
	CachedValue<double> viewX1, viewX2, viewY;
	ValueTree state;
};