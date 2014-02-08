#pragma once

class Scene {
public:
	double position;

	Scene();
	virtual ~Scene() = 0;

	virtual void init() = 0;
	virtual void kill() = 0;
	virtual void update(float delta) = 0;
	virtual void render(float alpha) = 0;
};
