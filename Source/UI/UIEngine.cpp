#include "UIEngine.h"

constexpr int toolBarHeight = 130;
constexpr int menuHeight = 40;
constexpr int yOfGrid = 100;
constexpr int xOfGrid = 200;

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
	auto width = proportionOfWidth(1.0f);
	menu.setBounds(0, 0, getWidth(), menuHeight);
    toolbar.setBounds(0, menuHeight, getWidth(), toolBarHeight);
	grid.setBounds(getLocalBounds().withTrimmedTop(toolBarHeight + menuHeight));
	
}

