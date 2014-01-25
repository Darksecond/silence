#include <cassert>
#include <iostream>
#include "GLWindow.h"

void GLWindow::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	GLWindow* gl_window = static_cast<GLWindow*>(glfwGetWindowUserPointer(window));
	if(gl_window) {
		gl_window->_width = width;
		gl_window->_height = height;
		gl_window->_resized = true;
	}
}

GLWindow::GLWindow(const int width, const int height) : window(nullptr), _resized(false) {
	open(width, height);
}

GLWindow::~GLWindow() {
	close();
}

void GLWindow::printInfo() {
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION)                  << std::endl;
	std::cout << "GLSL Version: "   << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	std::cout << "Vendor: "         << glGetString(GL_VENDOR)                   << std::endl;
	std::cout << "Renderer: "       << glGetString(GL_RENDERER)                 << std::endl;
}

void GLWindow::hintContext() {
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

void GLWindow::checkVersion() {
	if(!GLEW_VERSION_3_3) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
}

void GLWindow::initGLEW() {
	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glGetError(); // Ignore first error from GLEW
	checkVersion();
	printInfo();
}

void GLWindow::initGLFW(const int width, const int height) {
	hintContext();
	window = glfwCreateWindow(width, height, "OpenGL Window", NULL, NULL);
	if(!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	activateContext();
}

void GLWindow::open(const int width, const int height) {
	assert(window == nullptr);
	initGLFW(width, height);
	initGLEW();

	// Size callback stuff, and user pointer
	// TODO Move to own (private) method
	glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window, GLWindow::framebufferSizeCallback);
	glfwGetFramebufferSize(window, &_width, &_height);
	_resized = true;
}

void GLWindow::close() {
	if(window)
		glfwDestroyWindow(window);
	window = nullptr;
}

void GLWindow::setTitle(const char* title) {
	if(!window) return;
	glfwSetWindowTitle(window, title);
}

void GLWindow::swap() {
	if(!window) return;
	glfwSwapBuffers(window);
	glfwPollEvents();
}

bool GLWindow::shouldClose() const {
	if(!window) return true;
	return glfwWindowShouldClose(window);
}

bool GLWindow::resized() {
	bool r = _resized;
	_resized = false;
	return r;
}

int GLWindow::width() const {
	return _width;
}

int GLWindow::height() const {
	return _height;
}

void GLWindow::activateContext() {
	glfwMakeContextCurrent(window);
}
