#include "FrameTimer.h"
#include "System.h"

FrameTimer::FrameTimer(const float target_dt, const int target_frameskip) : dt(target_dt), frameskip(target_frameskip) {
	_acc = 0.0;
}

void FrameTimer::update(float delta) {
	// Delta may never be smaller than zero, we can't go back in time.
	if(delta < 0)
		delta = 0;

	_loops = 0;
	_acc += delta;
	
	_fps.update(delta);
}

float FrameTimer::getAlpha() const {
	return _acc/dt;
}

bool FrameTimer::shouldStep() const {
	return _acc >= dt && _loops < frameskip;
}

void FrameTimer::endStep() {
	_acc -= dt;
	_fps.step();
	++_loops;
}

float FrameTimer::getFPS() const {
	return _fps.getFPS();
}
