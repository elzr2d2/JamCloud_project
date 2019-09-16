#pragma once

#include "JuceHeader.h"
#include "Audio/AudioEngine.h"
#include "UI/Toolbar/ToolbarComponent.h"
#include "UI/Menu/MenuComponent.h"
#include "UI/Grid/GridComponent.h"
#include "UI/Dialogs/LoadingDialog.h"
#include "UI/Helpers/UiHelper.h"

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
	//LoadingDialog loadingDialog{};

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UIEngine)
};
