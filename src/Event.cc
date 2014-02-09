#include "Event.h"
#include "System.h"

Event::Event() : _start(0.0), _duration(0.0) {
}

Event::Event(double start, float duration) : _start(start), _duration(duration) {
}

float Event::getValue() const {
	double time = System::inst().getTime();
	if(time >= _start && time < _start + _duration) {
		return (time - _start)  / _duration;
	} else if(time >= _start + _duration) {
		return 1.0;
	} else {
		return 0.0;
	}
}

bool Event::hasPassed() const {
	double time = System::inst().getTime();
	return time >= _start;
}

bool Event::isOver() const {
	double time = System::inst().getTime();
	return time >= _start + _duration;
}
