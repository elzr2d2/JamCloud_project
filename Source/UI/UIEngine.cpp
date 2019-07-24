#include "UIEngine.h"

constexpr int toolBarHeight = 100;
constexpr int menuHeight = 40;
constexpr int yOfGrid = 100;
constexpr int xOfGrid = 200;
constexpr int gridHeight = 70*5+30;
constexpr int extra =200;

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
	grid.setBounds(0, menuHeight*2, getWidth(), gridHeight);
    toolbar.setBounds(0 + roundToInt(proportionOfWidth(1.0000f) * 0.0000f), proportionOfHeight(0.85f), getWidth(), toolBarHeight);

	
}

