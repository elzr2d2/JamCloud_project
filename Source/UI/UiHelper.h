#pragma once

constexpr int numOfChannels = 5;

constexpr int channelHight = 70;
constexpr int channelWidth = 200;


constexpr int gridWidth = 60000; 
constexpr int gridHight = numOfChannels * channelHight;

class UiHelper
{
public:
	static double timeToX(double timeLength)
	{		
		double relativeTime = timeLength / 300;//300sec = 5 min
		return gridWidth * relativeTime;	
	}

	static double xToTime(int x)
	{
		double relativeX = x / 300;
		return relativeX * gridWidth;
	}
};



