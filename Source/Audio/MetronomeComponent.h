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
    
private:
    int mTotalSamples { 0 };
    double mSampleRate { 0 };
    double mBpm { 132.0 };
    int mUpdateInterval { 0 };
    int mSamplesRemaining { 0 };
    
    AudioFormatManager mFormatManager;
    std::unique_ptr <AudioFormatReaderSource> pMetronomeSample { nullptr };


};

