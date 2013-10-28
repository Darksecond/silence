#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class GLWindow {
	int _width, _height;
	bool _resized;

	void hintContext();
	void initGLEW();
	void initGLFW(int width, int height);
	void open(int width, int height);
	void printInfo();
	void checkVersion();

	static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
public:
	GLFWwindow* window;

	GLWindow(int width, int height);
	~GLWindow();

	void setTitle(const char* title);
	void swap();
	bool shouldClose();
	void close();
	bool resized();
	int width();
	int height();
};
