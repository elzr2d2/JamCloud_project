#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "Audio/AudioEngine.h"

class NewProjectDialog : public Component, public Button::Listener
{
public:
	NewProjectDialog(AudioEngine& inEngine);
	~NewProjectDialog();

	void paint(Graphics& g) override;
	void resized() override;
	void buttonClicked(Button* buttonThatWasClicked) override;

private:

	std::unique_ptr<Label> bpmLabel;
	std::unique_ptr<TextEditor> bpmEditor;
	std::unique_ptr<Label> nameLabel;
	std::unique_ptr<TextEditor> nameEditor;
	std::unique_ptr<TextButton> sumbitButton;
	std::unique_ptr<Label> descLabel;
	std::unique_ptr<TextEditor> descEditor;
	AudioEngine& engine;
};

