#pragma once

constexpr int numOfChannels = 5;

constexpr int channelHight = 70;
constexpr int channelWidth = 200;


constexpr int gridWidth = 60000; 
constexpr int gridHight = numOfChannels * channelHight;
constexpr int trackLength = 300;//seconds
constexpr int trackLengthInMin = trackLength/60;

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
	static double bpmToX(double bpm)
	{

	}
	static double xToBpm()
	{

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

};



