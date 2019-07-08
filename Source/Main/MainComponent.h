#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "UI/UIEngine.h"
#include "Audio/AudioEngine.h"

class MainComponent : public Component
{
public:
    MainComponent();

    void paint(Graphics& g) override;
    void resized() override;

private:

    UIEngine ui;
    AudioEngine engine;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
