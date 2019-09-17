#pragma once

#include "JuceHeader.h"

/*

	For communicating with the Tracktion Engine's ValueTree (which holds the data of the project) we built the TreeComponent class.
	Every class or object which implements this class will have the ability to listen to the tree and change itself respectively.

*/

class TreeComponent : public Component,
					  public Timer,
					  public tracktion_engine::ValueTreeAllEventListener
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