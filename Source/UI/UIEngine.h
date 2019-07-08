#pragma once

#include "JuceHeader.h"
#include "Audio/AudioEngine.h"
#include "ToolbarComponent.h"
#include "MenuComponent.h"
#include "GridComponent.h"

class UIEngine : public Component
{
public:
	UIEngine(AudioEngine& inEngine);
	
	void resized() override;

private:
	ToolbarComponent toolbar;
	MenuComponent menu;
	GridComponent grid;
	AudioEngine& engine;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UIEngine)
};
