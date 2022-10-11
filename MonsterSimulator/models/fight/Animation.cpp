#include "Animation.h"

Animation::Animation(const float value, const int duration)
{
	_value = value;
	_currentDuration = 0;
	_duration = duration * 1000000;
}

void Animation::Update(const int deltaTime)
{
	if (!IsFinished())
	{
		// Increment the current duration by deltaTime
		_currentDuration += deltaTime;
	}
}
