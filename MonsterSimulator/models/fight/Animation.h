#pragma once
class Animation
{
private:
	float _value;
	int _currentDuration;
	int _duration;

public:

	Animation(const float value, const int duration);

	bool IsFinished() const { return _currentDuration >= _duration; }
	float GetPercent() const { return static_cast<float>(_currentDuration) / static_cast<float>(_duration); }
	float GetValue() const { return _value; }

	void Update();
};

