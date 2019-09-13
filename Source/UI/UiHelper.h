#pragma once

constexpr int numOfChannels = 5;

constexpr int channelHeight = 70;
constexpr int channelWidth = 200;

constexpr double gridWidth = 60000;
constexpr int gridHight = numOfChannels * channelHeight;
constexpr double trackLength = 600;//seconds
constexpr double trackLengthInMin = trackLength/60;


class UiHelper
{
public:
	
	static double timeToX(double timeLength)
	{		
		double relativeTime = timeLength / trackLength;
		return gridWidth * relativeTime;
	}

	static double xToTime(double x)
	{
		double relativeX = x / gridWidth;
		return relativeX * trackLength;
	}

	static double getBeatDistanceByBPM(double bpm)
	{
		double numOfBeats = bpm * trackLengthInMin;
		double beatDis = gridWidth / numOfBeats;
		return beatDis;
	}

	static double getNumOfBeats(double bpm)
	{
		return bpm * trackLengthInMin;
	}

	static int numChannels()
	{
		return numOfChannels;
	}

	static int getChannelHeight()
	{
		return channelHeight;
	}

	static int getPlayheadHeight()
	{
		int timelineHeight = 20;
		return numOfChannels * channelHeight+ timelineHeight;
	}

	static double getGridWidth()
	{
		return gridWidth;
	}
	
private:

};



