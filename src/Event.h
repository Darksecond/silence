#pragma once

class Event {
	double _start;
	float _duration;
public:
	Event(double start, float duration);

	/**
	 * Get the current value of the Event. This will go from 0 to 1 over the duration of the event.
	 * It will be zero before the event is started and one after it is over.
	 *            
	 *            /----------
	 *           /
	 * ---------/
	 */
	float getValue() const;
	bool hasPassed() const;
	bool isOver() const;
};
