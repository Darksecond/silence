#pragma once
#include "FPS.h"

class FrameTimer {
	double _acc;
	int _loops;
	FPS _fps;
public:
	const float dt;
	const int frameskip;

	FrameTimer(const float dt = 1.0/30, const int frameskip = 5);
	void update(float delta);
	float getAlpha() const;
	float getFPS() const;
	bool shouldStep() const;
	void endStep();
};
