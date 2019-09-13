#include "MenuComponent.h"
#include "Main/CommandManager.h"

constexpr int newFile = 1;
constexpr int saveAsFile = 2;
constexpr int loadFile = 3;
constexpr int exportAsWavFile = 4;
constexpr int saveFile= 5;
constexpr int audioSettings = 7;



MenuComponent::MenuComponent (AudioEngine& inEngine):
	engine(inEngine),
	newProjectDialog(inEngine)
{
	Colour darkGreyJam = Colour(0xff2c302f);
	Colour orangeJam = Colour(0xffc39400);
	/* File Button */
    fileButton.reset (new TextButton ("fileButton"));
    addAndMakeVisible (fileButton.get());
    fileButton->setButtonText (TRANS("File"));
    fileButton->addListener (this);
	fileButton->setColour(TextButton::ColourIds::buttonColourId, darkGreyJam);
    fileButton->setBounds (8, 8, 65, 24);

	/* Cloud Button */
    cloudButton.reset (new TextButton ("cloudButton"));
    addAndMakeVisible (cloudButton.get());
    cloudButton->setButtonText (TRANS("Cloud"));
    cloudButton->addListener (this);
	cloudButton->setColour(TextButton::ColourIds::buttonColourId, darkGreyJam);
    cloudButton->setBounds (80, 8, 65, 24);

	/* Settings Button */
    settingsButton.reset (new TextButton ("settingsButton"));
    addAndMakeVisible (settingsButton.get());
    settingsButton->setButtonText (TRANS("Settings"));
    settingsButton->addListener (this);
	settingsButton->setColour(TextButton::ColourIds::buttonColourId, darkGreyJam);
    settingsButton->setBounds (152, 8, 65, 24);

	/* LOGO */
    logo.reset (new Label ("logo",
                           TRANS("JamCloud")));
    addAndMakeVisible (logo.get());
    logo->setFont (Font ("Levenim MT", 26.40f, Font::plain).withTypefaceStyle ("Regular").withExtraKerningFactor (-0.030f));
    logo->setJustificationType (Justification::centredLeft);
    logo->setEditable (false, false, false);
    logo->setColour (TextEditor::textColourId, Colours::orange);
    logo->setColour (TextEditor::backgroundColourId, Colours::white);

	/* File Menu */
	fileMenu.addSectionHeader("Project");
	fileMenu.addItem(newFile, "New Project");
	fileMenu.addItem(loadFile, "Load Project");
	fileMenu.addSectionHeader("Files");
	fileMenu.addItem(saveFile, "save");
	fileMenu.addItem(saveAsFile, "Save As..");
	fileMenu.addItem(exportAsWavFile, "Export As WAV");
	
	/* Settings Menu*/
	settingsMenu.addItem(audioSettings, "Audio Settings");
	
    setSize (600, 40);
}

MenuComponent::~MenuComponent()
{
    fileButton = nullptr;
    cloudButton = nullptr;
    settingsButton = nullptr;
    logo = nullptr;
}


void MenuComponent::paint (Graphics& g)
{
    g.fillAll (Colour (0xff323e44));

    {
        int x = 0, y = 0, width = proportionOfWidth (1.0000f), height = 40;
        Colour fillColour = Colour (0xff25292b);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
    }

}

void MenuComponent::resized()
{
    logo->setBounds (568, 6, roundToInt (65 * 1.6615f), 32);
}

void MenuComponent::buttonClicked (Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == fileButton.get())
    {
		auto result = fileMenu.show();

		switch (result)
		{
		case newFile:			invokeCommand(new Commands::NewProject());
			break;
		case loadFile:			invokeCommand(new Commands::LoadProject());
			break;
		case saveAsFile:		engine.saveAsFile();
			break;
		case exportAsWavFile:	engine.exportFile();
			break;
		case saveFile:			engine.saveFile();
			break;
		default:
			break;
		}
    }
    else if (buttonThatWasClicked == cloudButton.get())
    {		
	/*<<<<<<< HEAD
			=======
		URL url("C:\\CODE\\JamCloud\\JamCloud_Firesharp\\JamCloud_Firesharp\\bin\\Debug\\JamCloud_Firesharp.exe");
		url.launchInDefaultBrowser();
		
	>>>>>>> 94bb6dab4f1cd123fcb301de587e9386a3d35793*/	
    }
    else if (buttonThatWasClicked == settingsButton.get())
    {
		auto result = settingsMenu.show();
		
		switch (result)
		{
		case audioSettings: engine.showAudioSettings();
			break;
		default:
			break;
		}
    }
}


#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MenuComponent" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="40">
  <BACKGROUND backgroundColour="ff323e44">
    <RECT pos="0 0 100% 40" fill="solid: ff25292b" hasStroke="0"/>
  </BACKGROUND>
  <TEXTBUTTON name="fileButton" id="dfff51d1e0928e6d" memberName="fileButton"
              virtualName="" explicitFocusOrder="0" pos="8 8 65 24" bgColOff="ff346160"
              buttonText="File" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="cloudButton" id="39d454aa00ad3aae" memberName="cloudButton"
              virtualName="" explicitFocusOrder="0" pos="80 8 65 24" bgColOff="ff346160"
              buttonText="Cloud" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="settingsButton" id="d856cdd1bdec7358" memberName="settingsButton"
              virtualName="" explicitFocusOrder="0" pos="152 8 65 24" bgColOff="ff346160"
              buttonText="Settings" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="userButton" id="4a4f478291026393" memberName="userButton"
              virtualName="" explicitFocusOrder="0" pos="224 8 65 24" bgColOff="ff346160"
              buttonText="User" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="logo" id="561bb0f60f809385" memberName="logo" virtualName=""
         explicitFocusOrder="0" pos="568 6 166.154% 32" posRelativeW="4a4f478291026393"
         edTextCol="ff000000" edBkgCol="0" labelText="CloudJam" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Levenim MT"
         fontsize="26.4" kerning="-0.03" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

