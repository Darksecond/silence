#pragma once
#include "FPS.h"

class FrameTimer {
	double _acc;
	int _loops;
	FPS _fps;
public:
	FrameTimer(/*dt, frameskip*/);
	void update(float delta);
	float getAlpha() const;
	float getFPS() const;
	bool shouldStep() const;
	void endStep();
};
