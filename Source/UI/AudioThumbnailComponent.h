#pragma once

#include "JuceHeader.h"
#include "Audio/AudioEngine.h"

//==============================================================================
class AudioThumbnailComponent : public Component,
                                private ChangeListener
{
public:
    explicit AudioThumbnailComponent(tracktion_engine::Clip& inClip);
    ~AudioThumbnailComponent();

    void paint(Graphics& g) override;
    void changeListenerCallback(ChangeBroadcaster* source) override;

    Clip& getClip() const { return clip; }

	void mouseDown(const MouseEvent& event) override;
	void mouseDrag(const MouseEvent& event) override;
	void mouseUp(const MouseEvent& event) override;
	bool isSelected() { return selected; };
private:

    void initSource();
    void thumbnailChanged();
    void paintIfNoFileLoaded(Graphics& g, const Rectangle<int>& thumbnailBounds);
    void paintIfFileLoaded(Graphics& g, const Rectangle<int>& thumbnailBounds);

	

    AudioFormatManager formatManager;
    AudioThumbnailCache thumbnailCache;
    AudioThumbnail thumbnail;
	
	ComponentDragger dragger;
	ComponentBoundsConstrainer * boundsConstrainer;
	bool selected = false;

    tracktion_engine::Clip& clip;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioThumbnailComponent)
};
