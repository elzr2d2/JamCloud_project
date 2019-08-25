/*
  ==============================================================================

    Metronome.h
    Created: 13 Apr 2019 3:29:47pm
    Author:  Joshua Hodge

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class MetronomeComponent
{
public:
	MetronomeComponent();
    
    // public methods
    void prepareToPlay (int samplesPerBlock, double sampleRate);
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill);
    void reset();

	void setBpm(double bpm=132.0);
	double getBpm();
    
private:
	double bpm = 132.0;
    int mTotalSamples { 0 };
    double mSampleRate { 0 };
    double mBpm { getBpm() };
    int mUpdateInterval { 0 };
    int mSamplesRemaining { 0 };
    
    AudioFormatManager mFormatManager;
    std::unique_ptr <AudioFormatReaderSource> pMetronomeSample { nullptr };

	File hiBeat{ "C:/CODE/JamCloud/JamCloud/JamCloud_project/Source/Metronome_Sounds/cowbell.wav" };
	File loBeat{ "C:/CODE/JamCloud/JamCloud/JamCloud_project/Source/Metronome_Sounds/sticks.wav" };
};

