#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cassert>

#include "GLWindow.h"
#include "Program.h"
#include "Shader.h"
#include "Bitmap.h"
#include "Texture.h"
#include "Mesh.h"

#include "TextureManager.h"
#include "ProgramManager.h"
#include "SyncManager.h"

#include "Timer.h"
#include "System.h"
#include "Demo.h"

#include "scenes/TestTriangle.h"

#include <stdio.h>
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void err() {
	GLenum err = glGetError();
	if(err != GL_NO_ERROR) {
		printf("OpenGL Error %i.\n",err);
		exit(-1);
	}
}

// http://www.glfw.org/docs/latest/quick.html
int main() {
	System::inst().init();

	//TODO move to System ->: glfwSetKeyCallback(System::inst()._window->window, key_callback);
	//glfwSwapInterval(0); // Disable VSYNC
	
	Demo demo;
	demo.addScene("test",new TestTriangle());
	demo.createEntry("test", 0, 10, 100);

	demo.init();
	while (!System::inst().shouldClose()) {
		System::inst().update();
		demo.update();
		demo.render();
		System::inst().endFrame();
	}
	demo.kill();

	System::inst().kill();
	return 0;
}
