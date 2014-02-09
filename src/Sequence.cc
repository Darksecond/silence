#include <algorithm>
#include "Sequence.h"
#include "System.h"

void Sequence::createTrigger(double start, float duration) {
	_triggers.push_back(Trigger{start, duration});
	sort(_triggers.begin(), _triggers.end());
}

int Sequence::getPosition() const {
	double time = System::inst().getTime();
	int count = 0;
	for(const Trigger& trigger : _triggers) {
		if(time < trigger.start) break;
		++count;
	}
	return count;
}

float Sequence::getValue() const {
	double time = System::inst().getTime();
	float value = 0.0;
	for(const Trigger& trigger : _triggers) {
		if(time >= trigger.start && time < trigger.start + trigger.duration) {
			 float pos = 1.0 - (time - trigger.start) / trigger.duration;
			 value += pos;
		}
	}
	value = std::min(value, 1.0f);
	return value;
}
