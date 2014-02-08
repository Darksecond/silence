#pragma once

class FPS {
	float _fps;
	float _t;
	int _steps;
public:
	FPS();

	/**
	 * Assumes delta is never negative.
	 */
	void update(float delta);

	inline void step() {
		++_steps;
	}

	inline float getFPS() const {
		return _fps;
	}
};
