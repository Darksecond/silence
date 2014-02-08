#pragma once

class Timer {
	double _previous;
	double _elapsed;
	float _delta;
	bool _paused;
public:
	Timer();
	void update();
	double getTime() const;
	void setPaused(const bool paused);
	float getDelta() const;

	//TODO sync
};
