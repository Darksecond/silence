#include "FPS.h"

FPS::FPS() {
	_fps = 0.0;
	_t = 0.0;
	_steps = 0;
}

void FPS::update(float delta) {
	_t += delta;

	//TODO This can be improved, we could use a moving average for example.
	if(_t > 1.0) {
		_fps = _steps/_t;
		_steps = 0;
		_t = 0.0;
	}
}
