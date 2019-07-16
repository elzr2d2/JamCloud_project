/*
  ==============================================================================

    TreeComponent.cpp
    Created: 16 Jul 2019 8:57:11pm
    Author:  Jordan

  ==============================================================================
*/

#include "TreeComponent.h"

TreeComponent::TreeComponent()
{
	startTimerHz(60);
}

void TreeComponent::timerCallback()
  {
	if (shouldUpdate.load())
	{
		shouldUpdate.store(false);
		update();
	}
  }

void TreeComponent::update()
{
}
