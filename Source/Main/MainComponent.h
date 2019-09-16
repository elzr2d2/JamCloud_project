#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "UI/UiEngine/UIEngine.h"
#include "Audio/AudioEngine.h"
#include "CommandManager.h"

class MainComponent : public Component, public CommandTarget
{
public:
    MainComponent();
	~MainComponent();
    void paint(Graphics& g) override;
    void resized() override;

    void performCommand(Command* command) override;

    void loadFile();

private:
    void createJamCloud(ValueTree tree);

    std::unique_ptr<AudioEngine> engine;
    std::unique_ptr<UIEngine> ui;

};
