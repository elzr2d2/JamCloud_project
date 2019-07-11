#pragma once

#include "JuceHeader.h"


using namespace tracktion_engine;
namespace te = tracktion_engine;

class AudioEngine
{
public :

    AudioEngine();
    ~AudioEngine();

    void addChannel();
    void removeChannel();

    void removeTrack(te::AudioTrack& track);
	TrackList& getTrackList() { return edit->getTrackList(); }
	void addNewClipFromFile(const File& editFile, AudioTrack& track);

	void changeVolume(AudioTrack& track, float newVolume);
	void changePan(AudioTrack& track, float newPan);
	void muteChannel(AudioTrack& track);
	void soloChannel(AudioTrack& track);

    void play();
	//void loop();
    void stop();
    void pause();
	void recording();
	bool isRecording();
	bool isPlaying();
	void exportFile();
	
	void createTracksAndAssignInputs();
	void changeListenerCallback(ChangeBroadcaster* source);

	void showAudioSettings();
	void audioSettings();

	void inputMonitoring(AudioTrack* at);

	void deleteSelectedClips();

	void activeMetro();

	void enableInputMonitoring(te::AudioTrack& t, bool im, int position = 0);
	bool trackHasInput(te::AudioTrack& t, int position = 0);
	bool isInputMonitoringEnabled(te::AudioTrack& t, int position = 0);
	//void exportFile();
	void armTrack(te::AudioTrack& t, bool arm, int position = 0);
	bool isTrackArmed(te::AudioTrack& t, int position = 0);

	TransportControl& getTransport() const;

	bool isDirty() { return dirty; }
	void setDirty(bool inDirty) { dirty = inDirty; }

private:

    te::WaveAudioClip::Ptr loadAudioFileAsClip(const File& file, AudioTrack& track);
    void removeAllClips(te::AudioTrack& track);
    void adjustClipProperties(tracktion_engine::WaveAudioClip& clip) const;
	void removeAllTracks();
	void addVolumeAndPanPlugin(AudioTrack& track) const;
	te::AudioTrack* getOrInsertAudioTrackAt(te::Edit& edit, int index);
	void toggleRecord();

    te::Engine engine{ProjectInfo::projectName};
    AudioFormatManager formatManager;
    std::unique_ptr<AudioFormatReaderSource> playSource;
    std::unique_ptr<te::Edit> edit;
	std::unique_ptr<te::SelectionManager> selectionManager;
	std::unique_ptr<te::ClickNode> click;
	std::unique_ptr<te::AudioNodeProperties> clickAudioNodeProperties;
	std::unique_ptr <te::VolumeAndPanPlugin> volumeAndPanPlugin;
	std::unique_ptr<SynthesiserSound> synthSound;

	bool channelSelected = false;
    bool dirty = true;
    int trackN = 0;

	File lastRecording;
	
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioEngine)
};