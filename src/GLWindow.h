#pragma once

#include "opengl.h"

class GLWindow {
	int _width, _height;
	bool _resized;

	void hintContext();
	void activateContext();
	void initGLEW();
	void initGLFW(const int width, const int height);
	void open(const int width, const int height);
	void printInfo();
	void checkVersion();

	static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
public:
	GLFWwindow* window;

	GLWindow(const int width, const int height);
	~GLWindow();

	void setTitle(const char* title);
	void swap();
	bool shouldClose() const;
	void close();
	bool resized();
	int width() const;
	int height() const;
};
