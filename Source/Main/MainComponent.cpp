#include "MainComponent.h"
#include "CommandManager.h"

MainComponent::MainComponent()
{
    getCommandManager().setTarget(this);

    createJamCloud(ValueTree());

    setSize(1000, 600);
}

//==============================================================================
void MainComponent::paint(Graphics& g)
{
    g.fillAll(Colour(0xff25292b));
}

void MainComponent::resized()
{
    if (ui != nullptr)
        ui->setBounds(getLocalBounds());
}

void MainComponent::createJamCloud(ValueTree tree)
{
    ui.reset();
    engine = std::make_unique<AudioEngine>(tree);
    ui = std::make_unique<UIEngine>(*engine);

    addAndMakeVisible(*ui);
    resized();
}

void MainComponent::performCommand(Command* command)
{
    if (auto newProject = dynamic_cast<Commands::NewProject*>(command))
        createJamCloud(ValueTree());

    else if (auto loadProject = dynamic_cast<Commands::LoadProject*>(command))
        loadFile();

}

void MainComponent::loadFile()
{
    auto location = File::getSpecialLocation(File::userDesktopDirectory);

    FileChooser chooser("Choose a file", location, "*.jam", true, false);

    if (chooser.browseForFileToOpen())
    {
        auto file = chooser.getResult();

        std::unique_ptr<XmlElement> xml;
        xml.reset(XmlDocument::parse(file));

        if (xml != nullptr)
        {
            auto tree = ValueTree::fromXml(*xml);

            if (tree.isValid())
                createJamCloud(tree);
        }

    }
}

