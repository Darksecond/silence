#pragma once
#include "Mesh.h"
#include "FrameTimer.h"
#include "FPS.h"

class Demo {
	FrameTimer _ft;
	Mesh _m;
	FPS _fps;
public:
	Demo();
	void init();
	void kill();
	void update();
	void render();
};
