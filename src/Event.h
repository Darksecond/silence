#pragma once

class Event {
	double _start;
	float _duration;
public:
	Event(double start, float duration);

	float getValue() const;
	bool hasPassed() const;
	bool isOver() const;
};
