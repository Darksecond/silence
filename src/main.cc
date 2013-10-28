#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cassert>

#include "GLWindow.h"

#include <stdio.h>
static void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void initOpenGL() {
	glfwSetErrorCallback(error_callback);

	if(!glfwInit()) {
		exit(EXIT_FAILURE);
	}
}

void terminateOpenGL() {
	glfwTerminate();
}

// http://www.glfw.org/docs/latest/quick.html
int main() {
	initOpenGL();

	GLWindow window(800, 600);
	glfwSetKeyCallback(window.window, key_callback);

	while (!window.shouldClose()) {
		if(window.resized()) {
			printf("resized to: %i, %i\n", window.width(), window.height());
		}
		window.swap();
	}

	window.close();
	terminateOpenGL();
	return 0;
}
