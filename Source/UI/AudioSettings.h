


#pragma once
#include "JuceHeader.h"
#include "Audio/AudioEngine.h"
//==============================================================================
class AudioSettings   : public AudioAppComponent,
                        public ChangeListener,
                        private Timer
{
public:
    //==============================================================================
	AudioSettings(AudioEngine& inEngine);
    ~AudioSettings();

    void prepareToPlay (int, double) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    void paint (Graphics& g) override;
    void resized() override;

private:

    void changeListenerCallback (ChangeBroadcaster*) override;
    static String getListOfActiveBits (const BigInteger& b);
    void timerCallback() override;
    void dumpDeviceInfo();
    void logMessage (const String& m);
  
    //==========================================================================
    Random random;
    AudioDeviceSelectorComponent audioSetupComp;
    Label cpuUsageLabel;
    Label cpuUsageText;
    TextEditor diagnosticsBox;

	AudioEngine& engine;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioSettings)
};
