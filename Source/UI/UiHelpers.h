#pragma once

#include "JuceHeader.h"
#include "Audio/AudioEngine.h"

namespace HelpersIDs
{
#define DECLARE_ID(name)  const juce::Identifier name (#name);
	DECLARE_ID(EDITVIEWSTATE)
	DECLARE_ID(showGlobalTrack)
	DECLARE_ID(showMarkerTrack)
	DECLARE_ID(showChordTrack)
	DECLARE_ID(viewX1)
	DECLARE_ID(viewX2)
	DECLARE_ID(viewY)
	DECLARE_ID(drawWaveforms)
#undef DECLARE_ID
}
namespace te = tracktion_engine;
//==============================================================================
class EditViewState
{
public:
	EditViewState(AudioEngine& inEngine):engine(inEngine)
	{
		auto traspornt = &engine.getTransport();
		state = traspornt->edit.state.getOrCreateChildWithName(HelpersIDs::EDITVIEWSTATE, nullptr);
		
		auto um = &engine.getTransport().edit.getUndoManager();

		showGlobalTrack.referTo(state, HelpersIDs::showGlobalTrack, um, false);
		showMarkerTrack.referTo(state, HelpersIDs::showMarkerTrack, um, false);
		showChordTrack.referTo(state, HelpersIDs::showChordTrack, um, false);
		drawWaveforms.referTo(state, HelpersIDs::drawWaveforms, um, true);

		viewX1.referTo(state, HelpersIDs::viewX1, um, 0);
		viewX2.referTo(state, HelpersIDs::viewX2, um, 60);
		viewY.referTo(state, HelpersIDs::viewY, um, 0);
	}

	int timeToX(double time, int width) const
	{
		return roundToInt(((time - viewX1) * width) / (viewX2 - viewX1));
	}

	double xToTime(int x, int width) const
	{
		return (double(x) / width) * (viewX2 - viewX1) + viewX1;
	}

	//te::Edit& edit;
	//te::SelectionManager& selectionManager;
	AudioEngine &engine;

	CachedValue<bool> showGlobalTrack, showMarkerTrack, showChordTrack, drawWaveforms;
	CachedValue<double> viewX1, viewX2, viewY;

	ValueTree state;
};
