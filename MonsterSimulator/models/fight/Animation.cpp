#include "Animation.h"

Animation::Animation(const float value, const int duration)
{
	_value = value;
	_currentDuration = 0;
	_duration = duration;
}

void Animation::Update()
{
	if (!IsFinished())
	{
		_currentDuration += 50;
	}
}
