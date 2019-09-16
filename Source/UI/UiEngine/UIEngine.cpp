#include "UIEngine.h"

UIEngine::UIEngine(AudioEngine& inEngine) :
	engine(inEngine),
    toolbar(inEngine),
	menu(inEngine),
	grid(inEngine)
{
	addAndMakeVisible(menu);
	addAndMakeVisible(toolbar);
	addAndMakeVisible(grid);
}

void UIEngine::resized()
{
	menu.setBounds(0, 0, getWidth(), menuHeight);
	grid.setBounds(0,gridY, getWidth(), gridHeightUI);
    toolbar.setBounds(0, proportionOfHeight(0.91f), getWidth(), toolBarHeight);
	
}


