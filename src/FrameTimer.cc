#include "FrameTimer.h"
#include "System.h"

static const double dt = 1.0/25;
static const int frameskip = 5;

FrameTimer::FrameTimer() {
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
