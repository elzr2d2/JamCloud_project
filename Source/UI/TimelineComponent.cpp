#include "TimelineComponent.h"

TimelineComponent::TimelineComponent ()
{
    setSize (60000,70*5+20);
}

TimelineComponent::~TimelineComponent()
{

}


void TimelineComponent::paint (Graphics& g)
{


    g.fillAll (Colours::red);
	//background
    {
        float x = 0.0f, y = 0.0f, width = proportionOfWidth(1.0f), height = 20.0f;
        Colour fillColour = Colour (0xffd9791a);
        g.setColour (fillColour);
        g.fillRoundedRectangle (0 , 70 * 5, width, height, 3.500f);
    }

	//text
	/*
    {
        int x = 4, y = 4, width = 100, height = 20;
        String text (TRANS("|"));
        Colour fillColour = Colours::black;
        g.setColour (fillColour);
        g.setFont (Font (20.00f, Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    Justification::bottomRight, true);
    }
	*/

}

void TimelineComponent::resized()
{
	
}

void TimelineComponent::mouseDown (const MouseEvent& e)
{

}






//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="TimelineComponent" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="60000" initialHeight="100">
  <METHODS>
    <METHOD name="mouseDown (const MouseEvent&amp; e)"/>
  </METHODS>
  <BACKGROUND backgroundColour="ff323e44">
    <ROUNDRECT pos="0 0 1000 25" cornerSize="3.5" fill="solid: ffd9791a" hasStroke="0"/>
    <TEXT pos="4 4 100 20" fill="solid: ff000000" hasStroke="0" text="|"
          fontname="Default font" fontsize="20.0" kerning="0.0" bold="0"
          italic="0" justification="18"/>
  </BACKGROUND>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

