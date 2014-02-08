#include "System.h"
#include "TextureManager.h"
#include "ProgramManager.h"

#include <stdio.h>

static void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

static void initOpenGL() {
	glfwSetErrorCallback(error_callback);

	if(!glfwInit()) {
		exit(EXIT_FAILURE);
	}
}

static void terminateOpenGL() {
	glfwTerminate();
}

System& System::inst() {
	static System instance;
	return instance;
}

void System::init() {
	initOpenGL();
	_window = new GLWindow(800, 600);
	TextureManager::inst().setRoot("/Users/darksecond/build/assets/textures/");
	ProgramManager::inst().setRoot("/Users/darksecond/build/assets/shaders/");
}

void System::kill() {
	TextureManager::inst().unloadAll();
	ProgramManager::inst().unloadAll();
	delete _window;
	terminateOpenGL();
}

void System::update() {
	_timer.update();
	//TODO sync Timer to Song
	//TODO update SyncManager
}

void System::endFrame() {
	_window->swap();
}

bool System::shouldClose() const {
	bool window = _window->shouldClose();
	bool escape = keyPressed(GLFW_KEY_ESCAPE);
	return window || escape;
}

float System::getDelta(bool abs) const {
	float delta = _timer.getDelta();
	if(abs) {
		if(delta < 0)
			delta = 0;
	}
	return delta;
}
