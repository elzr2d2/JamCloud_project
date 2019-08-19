#include "NewProjectDialog.h"
#include <sstream>

NewProjectDialog::NewProjectDialog(AudioEngine& inEngine):
	engine(inEngine)
{
	bpmLabel.reset(new Label("bpmLabel",
		TRANS("BPM\n")));
	addAndMakeVisible(bpmLabel.get());
	bpmLabel->setFont(Font("Levenim MT", 18.00f, Font::plain).withTypefaceStyle("Regular").withExtraKerningFactor(-0.035f));
	bpmLabel->setJustificationType(Justification::centredLeft);
	bpmLabel->setEditable(false, false, false);
	bpmLabel->setColour(TextEditor::textColourId, Colours::black);
	bpmLabel->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

	bpmLabel->setBounds(72, 232, 48, 24);

	bpmEditor.reset(new TextEditor("bpmEditor"));
	addAndMakeVisible(bpmEditor.get());
	bpmEditor->setMultiLine(false);
	bpmEditor->setReturnKeyStartsNewLine(false);
	bpmEditor->setReadOnly(false);
	bpmEditor->setScrollbarsShown(true);
	bpmEditor->setCaretVisible(true);
	bpmEditor->setPopupMenuEnabled(true);
	bpmEditor->setColour(TextEditor::backgroundColourId, Colour(0x63000000));
	bpmEditor->setText(TRANS("120"));

	bpmEditor->setBounds(128, 232, 56, 24);

	nameLabel.reset(new Label("nameLabel",
		TRANS("Project Name")));
	addAndMakeVisible(nameLabel.get());
	nameLabel->setFont(Font("Levenim MT", 18.00f, Font::plain).withTypefaceStyle("Regular"));
	nameLabel->setJustificationType(Justification::centredLeft);
	nameLabel->setEditable(false, false, false);
	nameLabel->setColour(TextEditor::textColourId, Colours::black);
	nameLabel->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

	nameLabel->setBounds(16, 80, 104, 24);

	nameEditor.reset(new TextEditor("nameEditor"));
	addAndMakeVisible(nameEditor.get());
	nameEditor->setMultiLine(false);
	nameEditor->setReturnKeyStartsNewLine(false);
	nameEditor->setReadOnly(false);
	nameEditor->setScrollbarsShown(true);
	nameEditor->setCaretVisible(true);
	nameEditor->setPopupMenuEnabled(true);
	nameEditor->setColour(TextEditor::backgroundColourId, Colour(0x63000000));
	nameEditor->setText(TRANS("Project Name"));

	nameEditor->setBounds(128, 80, 168, 24);

	sumbitButton.reset(new TextButton("sumbitButton"));
	addAndMakeVisible(sumbitButton.get());
	sumbitButton->setButtonText(TRANS("LET\'S JAM !"));
	sumbitButton->addListener(this);
	sumbitButton->setColour(TextButton::buttonColourId, Colour(0xa3ffffff));
	sumbitButton->setColour(TextButton::textColourOffId, Colour(0xff159568));
	sumbitButton->setColour(TextButton::textColourOnId, Colour(0xff003e39));

	sumbitButton->setBounds(88, 312, 127, 48);

	descLabel.reset(new Label("descLabel",
		TRANS("Description")));
	addAndMakeVisible(descLabel.get());
	descLabel->setFont(Font("Levenim MT", 18.00f, Font::plain).withTypefaceStyle("Regular"));
	descLabel->setJustificationType(Justification::centredLeft);
	descLabel->setEditable(false, false, false);
	descLabel->setColour(TextEditor::textColourId, Colours::black);
	descLabel->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

	descLabel->setBounds(27, 112, 88, 24);

	descEditor.reset(new TextEditor("descEditor"));
	addAndMakeVisible(descEditor.get());
	descEditor->setMultiLine(true);
	descEditor->setReturnKeyStartsNewLine(true);
	descEditor->setReadOnly(false);
	descEditor->setScrollbarsShown(true);
	descEditor->setCaretVisible(true);
	descEditor->setPopupMenuEnabled(true);
	descEditor->setColour(TextEditor::backgroundColourId, Colour(0x63000000));
	descEditor->setColour(TextEditor::outlineColourId, Colour(0x00000000));
	descEditor->setText(TRANS("..."));

	descEditor->setBounds(128, 112, 168, 112);

	setSize(320, 400);
}


NewProjectDialog::~NewProjectDialog()
{

	bpmLabel = nullptr;
	bpmEditor = nullptr;
	nameLabel = nullptr;
	nameEditor = nullptr;
	sumbitButton = nullptr;
	descLabel = nullptr;
	descEditor = nullptr;

}

void NewProjectDialog::paint(Graphics & g)
{
	g.fillAll(Colour(0xff323e44));

	{
		int x = 0, y = 0, width = 320, height = 400;
		Colour fillColour1 = Colour(0xff150a0a), fillColour2 = Colour(0xff113028);

		g.setGradientFill(ColourGradient(fillColour1,
			136.0f - 0.0f + x,
			120.0f - 0.0f + y,
			fillColour2,
			304.0f - 0.0f + x,
			288.0f - 0.0f + y,
			false));
		g.fillRect(x, y, width, height);
	}

	{
		int x = 84, y = 20, width = 156, height = 30;
		String text(TRANS("CloudJam"));
		Colour fillColour = Colours::white;
		g.setColour(fillColour);
		g.setFont(Font("Levenim MT", 32.50f, Font::plain).withTypefaceStyle("Regular"));
		g.drawText(text, x, y, width, height,
			Justification::centred, true);
	}
}

void NewProjectDialog::resized()
{
}

void NewProjectDialog::buttonClicked(Button * buttonThatWasClicked)
{
	if (buttonThatWasClicked == sumbitButton.get())
	{
		//need to check if the bpm is number
		if (bpmEditor->isEmpty())
			bpmEditor->setText("120");
		if (nameEditor->isEmpty())
			nameEditor->setText("CloudJam Project");
		auto projectName = nameEditor->getText();
	
		double bpm = 0.0;

		std::stringstream stringToDouble;
	
		stringToDouble << bpmEditor->getText();
		stringToDouble >> bpm;

		engine.createNewProject(projectName, bpm);
		
	}
}
