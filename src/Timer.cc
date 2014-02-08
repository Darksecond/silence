#include "Timer.h"
#include "opengl.h"

Timer::Timer() {
	_previous = glfwGetTime();
	_elapsed = 0;
	_delta = 0;
	_paused = false;
}

void Timer::update() {
	double current = glfwGetTime();
	double delta = current - _previous;
	_previous = current;

	if(!_paused) {
		_elapsed += delta;
		_delta = delta;
	} else {
		_delta = 0;
	}
}

double Timer::getTime() const {
	return _elapsed;
}

void Timer::setPaused(const bool paused) {
	_paused = paused;
}

float Timer::getDelta() const {
	return _delta;
}

void Timer::setTime(double time) {
	_elapsed = time;

	if(_elapsed < 0)
		_elapsed = 0;
}

void Timer::changeTime(float delta) {
	_elapsed += delta;

	if(_elapsed < 0)
		_elapsed = 0;
}
