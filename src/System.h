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

	inline void setTitle(const char* title) {
		_window->setTitle(title);
	}
};