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

void err() {
	GLenum err = glGetError();
	if(err != GL_NO_ERROR) {
		printf("OpenGL Error %i.\n",err);
		exit(-1);
	}
}

// http://www.glfw.org/docs/latest/quick.html
int main() {
	initOpenGL();

	GLWindow window(800, 600);
	glfwSetKeyCallback(window.window, key_callback);
	//glfwSwapInterval(0); // Disable VSYNC
	
	//TEXTURE TESTS
	Bitmap b;
	if(!b.loadFromFilename("/Users/darksecond/build/assets/textures/wooden-crate.jpg")) {
		printf("Bitmap loading unsuccessful\n");
		exit(-1);
	}

	Texture tex;
	if(!tex.loadFromBitmap(b)) {
		printf("Texture loading failed\n");
		exit(-1);
	}
	tex.generateMipmaps();

	err();
	//END TEXTURE TESTS
	
	//TEXTURE MANAGER TESTS
	TextureManager::inst().setRoot("/Users/darksecond/build/assets/textures/");
	TextureManager::inst().loadFromFilename("wooden-crate.jpg");
	Texture& tx = TextureManager::inst().get("wooden-crate.jpg");
	tx.bind();
	err();
	TextureManager::inst().unloadAll();
	//END TEXTURE MANAGER TESTS
	
	//SHADER TESTS
	Shader vs(GL_VERTEX_SHADER);
	vs.loadFromString(
			"#version 330\n"
			"\n"
			"in vec2 position;\n"
			"\n"
			"void main() {\n"
			"gl_Position = vec4(position, 0.0, 1.0);\n"
			"}\n"
			);
	if(!vs.compile()) {
		printf("VS Compile failed: %s\n",vs.log());
		exit(-1);
	}
	Shader fs(GL_FRAGMENT_SHADER);
	fs.loadFromString(
			"#version 330\n"
			"\n"
			"out vec4 g_diff;\n"
			"void main() {\n"
			"g_diff = vec4(1.0, 1.0, 1.0, 1.0);\n"
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
	
	//MESH TEST
	float vertices[] = {
		0.0f,  0.5f, // Vertex 1 (X, Y)
		0.5f, -0.5f, // Vertex 2 (X, Y)
		-0.5f, -0.5f  // Vertex 3 (X, Y)
	};

	Mesh m;
	m.addStream(vertices, 3, sizeof(float)*2);
	m.stream(0).addAttribute("position", 2, GL_FLOAT, GL_FALSE, 0);
	m.addSubMesh(3);
	
	p.bind();

	//CREATE & BIND VAO
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	m.bind(p); //requires a VAO to be bound.
	m.subMesh(0).bind();
	//END MESH TEST
	
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

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		m.subMesh(0).draw();

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
