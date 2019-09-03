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

	static double bpmToX(double bpm)
	{
		return 0;
	}

	static double xToBpm()
	{
		return 0;
	}

	static double getBeatDistanceByBPM(double bpm)
	{
		double numOfBeats = bpm * trackLengthInMin;
		double beatDis = gridWidth / numOfBeats;
		return beatDis ;
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

	 void setZoomIndex(int zoom)
	{
		zoomIndex = zoom;
	}

	 int  zoomIndex = 0;
private:
/*
	double zoomFactor()
	{
		switch (zoomIndex)
		{
		case 0:return 1;
		case 1:return 1.4f;
		case 2:return 2;
		case 3:return 4;
		default:return 1;
			break;
		}
	}
*/
	
};



