#pragma once

class Animation
{
private:
	float _value;
	// The duration of the animation in nanoseconds
	int _currentDuration;
	// The max duration of the animation in nanoseconds
	int _duration;

public:
	/**
	 * \brief Create a new animation
	 * \param value The value needed to animate (as needed by the animation)
	 * \param duration The max duration of the animation in milliseconds
	 */
	Animation(const float value, const int duration);

	/**
	 * \brief Check if the animation is finished
	 * \return True if the animation is finished
	 */
	bool IsFinished() const { return _currentDuration >= _duration; }
	/**
	 * \brief Get the percent of completion of the animation (between 0 and 1)
	 * \return The percent of completion of the animation
	 */
	float GetPercent() const { return static_cast<float>(_currentDuration) / static_cast<float>(_duration); }
	float GetValue() const { return _value; }

	/**
	 * \brief Update the animation by one tick
	 * \param deltaTime The time since the last update in nanoseconds
	 */
	void Update(int deltaTime);
};

