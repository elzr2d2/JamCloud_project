/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.3

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "FXInsertComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
FXInsertComponent::FXInsertComponent ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    insertFXButton.reset (new TextButton ("insertFXButton"));
    addAndMakeVisible (insertFXButton.get());
    insertFXButton->setButtonText (TRANS("Insert FX"));
    insertFXButton->addListener (this);
    insertFXButton->setColour (TextButton::buttonColourId, Colour (0x44808080));
    insertFXButton->setColour (TextButton::buttonOnColourId, Colours::black);
    insertFXButton->setColour (TextButton::textColourOffId, Colours::black);

    insertFXButton->setBounds (392, 312, 120, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

FXInsertComponent::~FXInsertComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    insertFXButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void FXInsertComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    {
        float x = 392.0f, y = 308.0f, width = 120.0f, height = 192.0f;
        Colour fillColour1 = Colour (0xff7878ff), fillColour2 = Colours::grey;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (ColourGradient (fillColour1,
                                       448.0f - 392.0f + x,
                                       496.0f - 308.0f + y,
                                       fillColour2,
                                       504.0f - 392.0f + x,
                                       312.0f - 308.0f + y,
                                       true));
        g.fillRoundedRectangle (x, y, width, height, 2.000f);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void FXInsertComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void FXInsertComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == insertFXButton.get())
    {
        //[UserButtonCode_insertFXButton] -- add your button handler code here..
        //[/UserButtonCode_insertFXButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="FXInsertComponent" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ff323e44">
    <ROUNDRECT pos="392 308 120 192" cornerSize="2.0" fill=" radial: 448 496, 504 312, 0=ff7878ff, 1=ff808080"
               hasStroke="0"/>
  </BACKGROUND>
  <TEXTBUTTON name="insertFXButton" id="6c0b37056b9ad851" memberName="insertFXButton"
              virtualName="" explicitFocusOrder="0" pos="392 312 120 24" bgColOff="44808080"
              bgColOn="ff000000" textCol="ff000000" buttonText="Insert FX"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

