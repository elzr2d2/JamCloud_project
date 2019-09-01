#include "MainComponent.h"
#include "CommandManager.h"

MainComponent::MainComponent()
{
    getCommandManager().setTarget(this);

    createJamCloud();

    setSize(1000, 600);
}

//==============================================================================
void MainComponent::paint(Graphics& g)
{
    g.fillAll(Colour(0xff25292b));
}

void MainComponent::resized()
{
    if (cloud != nullptr)
        cloud->ui.setBounds(getLocalBounds());
}

void MainComponent::createJamCloud()
{
    cloud = std::make_unique<JamCloud>();
    addAndMakeVisible(cloud->ui);
    resized();
}

void MainComponent::performCommand(Command* command)
{
    if (auto newProject = dynamic_cast<Commands::NewProject*>(command))
        createJamCloud();
}

