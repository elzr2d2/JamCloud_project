#pragma once

#include "JuceHeader.h"
#include <atomic> 

using namespace tracktion_engine;
namespace te = tracktion_engine;

class AudioEngine
{
public:

	AudioEngine();
	~AudioEngine();

	/* Channel Actions */
	void addChannel();
	void removeChannel();

	/* Track Actions */
	void removeTrack(te::AudioTrack& track);
	TrackList& getTrackList() { return edit->getTrackList(); }
	void createTracksAndAssignInputs();

	/* Clip Actions */
	void addNewClipFromFile(const File& editFile, AudioTrack& track);
	void deleteSelectedClips();

	/* Channel Sliders */
	void changeVolume(AudioTrack& track, float newVolume);
	void changePan(AudioTrack& track, float newPan);
	void muteChannel(AudioTrack& track);
	void soloChannel(AudioTrack& track);

	/* Transport Actions */
	void play();
	void loop();
	void stop();
	void pause();
	void recording();
	void setBpm(double bpm);
	double getBpm();

	/* Transport Checks */
	bool isRecording();
	bool isPlaying();
	bool isLooping();

	/* File Actions */
	void saveAsFile();
	void loadFile();
	void exportFile();
	void createNewProject(String name, double bpm);

	/* Audio Settings */
	void showAudioSettings();
	void audioSettings();

	/* Input Actions */
	void inputMonitoring(AudioTrack* at);
	void enableInputMonitoring(te::AudioTrack& t, bool im, int position = 0);
	void armTrack(te::AudioTrack& t, bool arm, int position = 0);
	/* Input Checks */
	bool trackHasInput(te::AudioTrack& t, int position = 0);
	bool isInputMonitoringEnabled(te::AudioTrack& t, int position = 0);
	bool isTrackArmed(te::AudioTrack& t, int position = 0);

	void activeMetro();
	void changeListenerCallback(ChangeBroadcaster* source);
	TransportControl& getTransport() const;
	Edit * getEdit() const;

private:

    te::WaveAudioClip::Ptr loadAudioFileAsClip(const File& file, AudioTrack& track);
	te::AudioTrack* getOrInsertAudioTrackAt(te::Edit& edit, int index);
    void removeAllClips(te::AudioTrack& track);
    void adjustClipProperties(tracktion_engine::WaveAudioClip& clip) const;
	void removeAllTracks();
	void addVolumeAndPanPlugin(AudioTrack& track) const;

	void toggleRecord();

    te::Engine engine{ProjectInfo::projectName};
    AudioFormatManager formatManager;
    std::unique_ptr<AudioFormatReaderSource> playSource;
    std::unique_ptr<te::Edit> edit;
	std::unique_ptr<te::SelectionManager> selectionManager;
	std::unique_ptr<te::ClickNode> click;
	std::unique_ptr<te::AudioNodeProperties> clickAudioNodeProperties;
	std::unique_ptr <te::VolumeAndPanPlugin> volumeAndPanPlugin;
	
	std::unique_ptr <te::TempoSequence> tempoSequence;
	std::unique_ptr <te::TempoSetting> tempoSetting;
	bool channelSelected = false;
    int trackN = 0;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioEngine)
};