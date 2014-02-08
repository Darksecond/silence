#include <cstdio>
#include "Demo.h"
#include "System.h"
#include "TextureManager.h"
#include "ProgramManager.h"

Demo::Demo() {
}

void Demo::init() {
	ProgramManager::inst().loadFromFilename("simple");
	TextureManager::inst().loadFromFilename("wooden-crate.jpg");

	float vertices[] = {
		0.0f,  0.5f, // Vertex 1 (X, Y)
		0.5f, -0.5f, // Vertex 2 (X, Y)
		-0.5f, -0.5f  // Vertex 3 (X, Y)
	};

	_m.addStream(vertices, 3, sizeof(float)*2);
	_m.stream(0).addAttribute("position", 2, GL_FLOAT, GL_FALSE, 0);
	_m.addSubMesh(3);

	Program& p = ProgramManager::inst().get("simple");
	p.bind();

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	_m.bind(p); //requires a VAO to be bound.
	_m.subMesh(0).bind();
}

void Demo::kill() {
}

void Demo::update() {
	float delta = System::inst().getDelta(true);

	_fps.update(delta);
	_ft.update(delta);
	while(_ft.shouldStep()) {
		//TODO update(dt)
		_ft.endStep();
	}
}

void Demo::render() {
	_fps.step();

	//render stuff
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	_m.subMesh(0).draw();

	char title[1024];
	sprintf(title, "UFPS: %f RFPS: %f alpha: %f", _ft.getFPS(), _fps.getFPS(), _ft.getAlpha());
	System::inst().setTitle(title);
}
