#include "MainComponent.h"

MainComponent::MainComponent(): ui(engine)
{
	addAndMakeVisible(ui);

    setSize (1000, 600);
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
	g.fillAll(Colour(0xff323e44));
}

void MainComponent::resized()
{
	 ui.setBounds(getLocalBounds());
}
