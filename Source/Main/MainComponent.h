#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "UI/UIEngine.h"
#include "Audio/AudioEngine.h"
#include "CommandManager.h"

struct JamCloud
{
    AudioEngine engine;
    UIEngine ui { engine };
};

class MainComponent : public Component, public CommandTarget
{
public:
    MainComponent();

    void paint(Graphics& g) override;
    void resized() override;

    void performCommand(Command* command) override;


private:
    void createJamCloud();

    std::unique_ptr<JamCloud> cloud;
};
