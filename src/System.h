#pragma once
#include "GLWindow.h"
#include "Timer.h"

class System {
	Timer _timer;
	GLWindow* _window;
public:
	static System& inst();
	
	void init();
	void kill();
	void update();
	void endFrame();
	bool shouldClose() const;

	/**
	 * Frame delta.
	 * \param abs if true the delta will never be nagative.
	 * \return the frame delta.
	 */
	float getDelta(bool abs=false) const;
	inline double getTime() const {
		return _timer.getTime();
	}
	void setPaused(const bool paused);
	void changeTime(double time);

	inline void setTitle(const char* title) {
		_window->setTitle(title);
	}

	inline bool keyPressed(const int key) const {
		return _window->keyPressed(key);
	}

	inline bool keyDown(const int key) const {
		return _window->keyDown(key);
	}

	inline bool keyUp(const int key) const {
		return _window->keyUp(key);
	}
};
