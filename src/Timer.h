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
	
	void setTime(double time);
	void changeTime(float delta);

	//TODO sync
};
