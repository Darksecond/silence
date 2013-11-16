#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cassert>

#include "GLWindow.h"
#include "Program.h"
#include "Shader.h"

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
	//glfwSwapInterval(0); // Disable VSYNC
	
	//SHADER TESTS
	Shader vs(GL_VERTEX_SHADER);
	vs.loadFromString(
			"#version 330\n"
			"uniform mat4 projection;\n"
			"uniform mat4 view;\n"
			"in vec3 vert;\n"
			"in vec2 vertTexCoord;\n"
			"out vec2 fragTexCoord;\n"
			"void main() {\n"
			"fragTexCoord = vertTexCoord;\n"
			"gl_Position = projection * view * vec4(vert, 1.0);\n"
			"}\n"
			);
	if(!vs.compile()) {
		printf("VS Compile failed: %s\n",vs.log());
		exit(-1);
	}
	Shader fs(GL_FRAGMENT_SHADER);
	fs.loadFromString(
			"#version 330\n"
			"uniform sampler2D diffuse;\n"
			"in vec2 fragTexCoord;\n"
			"out vec4 g_diff;\n"
			"void main() {\n"
			"g_diff = texture(diffuse, fragTexCoord);\n"
			"}\n"
			);
	if(!fs.compile()) {
		printf("FS Compile failed: %s\n",fs.log());
		exit(-1);
	}
	Program p;
	p.attachShader(&vs);
	p.attachShader(&fs);
	if(!p.link()) {
		printf("Link failed: %s\n",p.log());
		exit(-1);
	}

	//END SHADER TESTS
	
	double previous = glfwGetTime();
	double acc = 0.0;
	double dt = 1.0/25; //run updates at 25FPS
	double t = 0.0;
	int rf = 0;
	int uf = 0;
	int frameskip = 5;
	while (!window.shouldClose()) {
		double now = glfwGetTime();
		double delta = now - previous;
		previous = now;
		//if(delta > 0.25) delta = 0.25;
		acc += delta;
		int loops = 0;
		while(acc >= dt && loops < frameskip) {
			//update(dt)
			acc -= dt;
			//t += dt;
			++uf;
			++loops;
		}
		double alpha = acc / dt; // Alpha is [0,1] and is the amount we are into the next frame, we can use this for timestep smoothing.
		//render(alpha)
		t += delta;
		++rf;

		char title[1024];
		sprintf(title, "UFPS: %f RFPS: %f alpha: %f", uf/t, rf/t, alpha);
		window.setTitle(title);

		window.swap();
	}

	window.close();
	terminateOpenGL();
	return 0;
}
