#include "AudioEngine.h"

std::unique_ptr<te::Engine> tracktionEngine;

te::Engine& getTracktionEngine()
{
    if (tracktionEngine == nullptr)
        tracktionEngine = std::make_unique<te::Engine>("JamCloud");
	
    return *tracktionEngine;
}

constexpr int NumberOfChannels = 5;

AudioEngine::AudioEngine(ValueTree projectToLoad)
{
    getTracktionEngine(); //makes sure an engine exists;

    if (projectToLoad.isValid())
        initEditFromProject(projectToLoad);
    else
    {
        initEditFromProject(createEmptyEdit());
        removeAllTracks();
        createNewProject();
    }
}


void AudioEngine::initEditFromProject(ValueTree projectFile)
{
    edit = std::make_unique<Edit>(getTracktionEngine(), projectFile, Edit::forEditing, nullptr, 0);
    createTracksAndAssignInputs();
    edit->playInStopEnabled = true;

    tempoSequence = std::make_unique<TempoSequence>(*edit.get());
    tempoSetting = std::make_unique<TempoSetting>(*tempoSequence.get(), projectFile);
	
}

AudioEngine::~AudioEngine()
{
    getTracktionEngine().getTemporaryFileManager().getTempDirectory().deleteRecursively();
}

void AudioEngine::removeAllTracks()
{
    if (!getTrackList().isEmpty())
    {
        for (auto track : getTrackList())
        {
            edit->deleteTrack(track);
        }
    }

}

void AudioEngine::removeChannel()
{
    if (trackN > 0)
    {
        auto track = getOrInsertAudioTrackAt(*edit, --trackN);
        removeTrack(*track);
    }
}

te::AudioTrack* AudioEngine::getOrInsertAudioTrackAt(te::Edit& inEdit, int index)
{
    inEdit.ensureNumberOfAudioTracks(index + 1);
    return te::getAudioTracks(inEdit)[index];
}

void AudioEngine::removeTrack(te::AudioTrack& track)
{
    auto& clips = track.getClips();

    clips.getUnchecked(trackN)->removeFromParentTrack();
}

te::WaveAudioClip::Ptr AudioEngine::loadAudioFileAsClip(const File& file, AudioTrack& track)
{
    // Add a new clip to this track
    AudioFile audioFile(file);

    if (audioFile.isValid())
    {
        auto name = file.getFileNameWithoutExtension();

        auto tracklen = track.getLength();
        auto audioFilelen = audioFile.getLength();

        EditTimeRange timeRange(track.getLength(), track.getLength() + audioFile.getLength());
        ClipPosition position = { timeRange, 0 };

        auto newClip = track.insertWaveClip(name, file, position, false);

        if (newClip != nullptr)
            return newClip;
    }

    return nullptr;
}

void AudioEngine::addNewClipFromFile(const File& editFile, AudioTrack& track)
{
    auto clip = loadAudioFileAsClip(editFile, track);

    if (clip != nullptr)
    {
        adjustClipProperties(*clip);
    }

}

void AudioEngine::armTrack(te::AudioTrack& t, bool arm, int position)
{
    auto& currentEdit = t.edit;

    for (auto instance : currentEdit.getAllInputDevices())
        if (instance->getTargetTrack() == &t && instance->getTargetIndex() == position)
            instance->setRecordingEnabled(arm);

}

bool AudioEngine::isTrackArmed(te::AudioTrack& t, int position)
{
    auto& currentEdit = t.edit;

    for (auto instance : currentEdit.getAllInputDevices())
        if (instance->getTargetTrack() == &t && instance->getTargetIndex() == position)
            return instance->isRecordingEnabled();

    return false;
}


bool AudioEngine::isInputMonitoringEnabled(te::AudioTrack& t, int position)
{
    auto& currentEdit = t.edit;

    for (auto instance : currentEdit.getAllInputDevices())
        if (instance->getTargetTrack() == &t && instance->getTargetIndex() == position)
            return instance->getInputDevice().isEndToEndEnabled();

    return false;
}

void AudioEngine::enableInputMonitoring(te::AudioTrack& t, bool im, int position)
{
    if (isInputMonitoringEnabled(t, position) != im)
    {
        auto& currentEdit = t.edit;

        for (auto instance : currentEdit.getAllInputDevices())
            if (instance->getTargetTrack() == &t && instance->getTargetIndex() == position)
                instance->getInputDevice().flipEndToEnd();
    }
}

bool AudioEngine::trackHasInput(te::AudioTrack& t, int position)
{
    auto& currentEdit = t.edit;

    for (auto instance : currentEdit.getAllInputDevices())
        if (instance->getTargetTrack() == &t && instance->getTargetIndex() == position)
            return true;

    return false;
}

TransportControl& AudioEngine::getTransport() const
{
    return edit->getTransport();
}

TempoSetting & AudioEngine::getTempoSetting() const
{
	return *tempoSetting;
}

Edit* AudioEngine::getEdit() const
{
    return edit.get();
}

void AudioEngine::play()
{
    getTransport().play(false);
}

void AudioEngine::pause()
{
    //stop recording in case Record is on
    if (isRecording())
    {
        getTransport().stop(true, false, true, false);
    }
    else
    {
        getTransport().stop(false, false, true, false);
    }

}

void AudioEngine::stop()
{
    getTransport().stop(false, false, true, true);
    getTransport().setCurrentPosition(0);
}

void AudioEngine::recording()
{
    bool wasRecording = edit->getTransport().isRecording();
    toggleRecord();

    if (wasRecording)
        te::EditFileOperations(*edit).save(true, true, false);
}

void AudioEngine::toggleArm(AudioTrack& track)
{
	bool shouldArm = !isTrackArmed(track);
	armTrack(track, shouldArm);
}

void AudioEngine::loop()
{
    auto endLoopPos = edit->getTransport().getCurrentPosition();
    EditTimeRange timeRange { 0, endLoopPos };

    if (isLooping())
    {
        getTransport().looping.setValue(false, nullptr);
    }
    else
    {
        edit->getTransport().setLoopRange(timeRange);
        getTransport().looping.setValue(true, nullptr);
    }
}


void AudioEngine::toggleRecord()
{
    auto& transport = edit->getTransport();

    if (transport.isRecording())
        transport.stop(false, false);
    else
        transport.record(false);
}

void AudioEngine::removeAllClips(te::AudioTrack& track)
{
    auto& clips = track.getClips();

    for (int i = clips.size(); --i >= 0;)
        clips.getUnchecked(i)->removeFromParentTrack();
}

void AudioEngine::adjustClipProperties(tracktion_engine::WaveAudioClip& clip) const
{
    // Disable auto tempo and pitch, we'll handle these manually
    clip.setAutoTempo(false);
    clip.setAutoPitch(false);
    clip.setTimeStretchMode(TimeStretcher::defaultMode);
	
}

void AudioEngine::addChannel()
{
    auto numTracks = edit->getTrackList().size();
    auto track = getOrInsertAudioTrackAt(*edit, numTracks - 1);

    addVolumeAndPanPlugin(*track);

}

void AudioEngine::addVolumeAndPanPlugin(AudioTrack& track) const
{
    auto plugins = track.getAllPlugins();

    PluginDescription description;
    auto newPlugin = edit->getPluginCache().createNewPlugin("volume", description);

    plugins.add(newPlugin);
}


void AudioEngine::changeVolume(AudioTrack& track, float newVolume)
{
    auto plugins = track.getAllPlugins();

    for (int index = 0; index < plugins.size(); ++index)
    {
        auto plugin = plugins.getObjectPointer(index);

        auto volume = dynamic_cast<VolumeAndPanPlugin*>(plugin);

        if (volume != nullptr)
            volume->setVolumeDb(newVolume);
    }
}

void AudioEngine::changePan(AudioTrack& track, float newPan)
{
    auto plugins = track.getAllPlugins();

    for (int index = 0; index < plugins.size(); ++index)
    {
        auto plugin = plugins.getObjectPointer(index);

        auto pan = dynamic_cast<VolumeAndPanPlugin*>(plugin);

        if (pan != nullptr)
            pan->setPan(newPan);
    }
}

void AudioEngine::muteChannel(AudioTrack& track)
{
    if (track.isMuted(false))
    {
        track.setMute(false);
    }
    else
    {
		track.setMute(true);
		if (track.isSolo(true))
			track.setSolo(false);
    }
}

void AudioEngine::soloChannel(AudioTrack& track)
{
    if (track.isSolo(true))
    {
        track.setSolo(false);
    }
    else
    {
		track.setSolo(true);
		if (track.isMuted(true))
			track.setMute(false);
    }
}


bool AudioEngine::isPlaying()
{
    return getTransport().isPlaying();
}

bool AudioEngine::isLooping()
{
    return getTransport().looping.get();
}



void AudioEngine::saveAsFile()
{
    File editFile {};

    if (editFile == File())
    {
        FileChooser fc("New Edit", File::getSpecialLocation(File::userDocumentsDirectory), "*.jam");
        if (fc.browseForFileToSave(true))
        {
            editFile = fc.getResult();
            edit->editFileRetriever = [editFile]
            { return editFile; };
        }

        te::EditFileOperations(*edit).saveAs(editFile, false);
    }
}

void AudioEngine::exportFile()
{

	Renderer renderer;
	File outputFile{};
	Range<double> range(0, getTransport().getCurrentPosition());
	BigInteger bigInt;
	bigInt.clear();

	bigInt.setRange(0, getTrackList().size(), true);

	if (outputFile == File())
	{
		FileChooser fc("Exporting to Wav File", File::getSpecialLocation(File::userDocumentsDirectory), "*.wav");
		if (fc.browseForFileToSave(true))
		{
			outputFile = fc.getResult();

			if (renderer.renderToFile("Exporting to Wav File", outputFile, *edit, range, bigInt, true, nullptr, false))
			{

				DBG("\nrendering\n");
			}

			else
			{
				DBG("\n!rendering\n");

			}



		}
	}
}

void AudioEngine::saveFile()
{
	te::EditFileOperations(*edit).save(true, true, true);
}

void AudioEngine::createNewProject()
{
	for (int i = 0; i < NumberOfChannels; i++)
	{
		addChannel();
	}

}


bool AudioEngine::isRecording()
{
    return getTransport().isRecording();
}

void AudioEngine::createTracksAndAssignInputs()
{
    auto& dm = getTracktionEngine().getDeviceManager();

    for (int i = 0; i < dm.getNumWaveInDevices(); i++)
        if (auto wip = dm.getWaveInDevice(i))
            wip->setStereoPair(false);

    for (int i = 0; i < dm.getNumWaveInDevices(); i++)
    {
        if (auto wip = dm.getWaveInDevice(i))
        {
            wip->setEndToEnd(true);
            wip->setEnabled(true);
        }
    }

    edit->restartPlayback();

    int trackNum = 0;
    for (auto instance : edit->getAllInputDevices())
    {
        if (instance->getInputDevice().getDeviceType() == te::InputDevice::waveDevice)
        {
            if (auto t = getOrInsertAudioTrackAt(*edit, trackNum))
            {
                instance->setTargetTrack(t, 0);
                instance->setRecordingEnabled(true);

                trackNum++;
            }
        }
    }

    edit->restartPlayback();
}

void AudioEngine::changeListenerCallback(ChangeBroadcaster* /*source*/)
{

}

void AudioEngine::showAudioSettings()
{
    audioSettings();
}

void AudioEngine::audioSettings()
{
    DialogWindow::LaunchOptions o;
    o.dialogTitle = TRANS("Audio Settings");
    o.dialogBackgroundColour = LookAndFeel::getDefaultLookAndFeel().findColour(ResizableWindow::backgroundColourId);
    o.content.setOwned(
            new AudioDeviceSelectorComponent(getTracktionEngine().getDeviceManager().deviceManager, 2, 2, 0, 2, false,
                                             false, true,
                                             true));
    o.content->setSize(400, 600);
    o.launchAsync();
}

void AudioEngine::inputMonitoring(AudioTrack* at)
{
    PopupMenu m;
	constexpr int inputMonitoring = 1000;
    if (trackHasInput(*at))
    {
        bool ticked = isInputMonitoringEnabled(*at);
        m.addItem(inputMonitoring, "Input Monitoring", true, ticked);
        m.addSeparator();
    }

    int id = 1;
    for (auto instance : at->edit.getAllInputDevices())
    {
        if (instance->getInputDevice().getDeviceType() == te::InputDevice::waveDevice)
        {
            bool ticked = instance->getTargetTrack() == at;
            m.addItem(id++, instance->getInputDevice().getName(), true, ticked);
        }
    }

    int res = m.show();

    if (res == inputMonitoring)
    {
        enableInputMonitoring(*at, !isInputMonitoringEnabled(*at));
    }
    else if (res > 0)
    {
        id = 1;
        for (auto instance : at->edit.getAllInputDevices())
        {
            if (instance->getInputDevice().getDeviceType() == te::InputDevice::waveDevice)
            {
                if (id == res)
                    instance->setTargetTrack(at, 0);
                id++;
            }
        }
    }

}

void AudioEngine::deleteSelectedClips()
{
    auto allSelectedObjects = selectionManager->getSelectedObjects();

    allSelectedObjects.clear();

}


void AudioEngine::setBpm(double bpm)
{
    tempoSetting->setBpm(bpm);
	

}

double AudioEngine::getBpm()
{
    return tempoSetting->getBpm();
}


