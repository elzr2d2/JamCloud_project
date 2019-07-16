#pragma once

#include "JuceHeader.h"


class TreeComponent : public Component,
					  public Timer,
					  public ValueTreeAllEventListener
{
public:
	TreeComponent();
	void timerCallback() override;
	void valueTreeChildAdded(juce::ValueTree&, juce::ValueTree&) override { markForUpdate(); }
	void valueTreeChildRemoved(juce::ValueTree&, juce::ValueTree&, int) override { markForUpdate(); }
	void valueTreeChanged() override {};
	void markForUpdate() { shouldUpdate.store(true); }
protected:

	virtual void update();
private:
	std::atomic<bool>  shouldUpdate;
};