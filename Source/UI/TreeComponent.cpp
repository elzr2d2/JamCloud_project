#include "TreeComponent.h"

TreeComponent::TreeComponent()
{
	startTimerHz(60);
	markForUpdate();
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
