#include <cstdio>
#include <algorithm>
#include "Demo.h"
#include "System.h"
#include "Scene.h"
#include "Math.h"

Demo::Demo() : _ft(1.0/60) {
}

void Demo::init() {
	for(auto it : _scenes) {
		it.second->init();
	}
}

void Demo::kill() {
	for(auto it : _scenes) {
		it.second->kill();
		delete it.second;
	}
	_scenes.clear();
	_timeline.clear();
}

void Demo::update() {
	float delta = System::inst().getDelta(true);
	const double time = System::inst().getTime();

	_fps.update(delta);
	_ft.update(delta);
	while(_ft.shouldStep()) {
		for(Entry& e : _timeline) {
			if(time >= e.start && time < e.end) { // Scene is active, update
				e.scene->position = Math::rangePosition(time, e.start, e.end);
				e.scene->update(_ft.dt);
			}
		}
		_ft.endStep();
	}
}

void Demo::render() {
	_fps.step();
	const double time = System::inst().getTime();

	// Render scenes
	for(Entry& e : _timeline) {
		if(time >= e.start && time < e.end) {
			//active scene
			e.scene->render(_ft.getAlpha());
		}
	}

	char title[1024];
	sprintf(title, "UFPS: %f RFPS: %f alpha: %f", _ft.getFPS(), _fps.getFPS(), _ft.getAlpha());
	System::inst().setTitle(title);
}

void Demo::addScene(const char* name, Scene* scene) {
	printf("Added scene %s\n", name);
	_scenes[name] = scene;
}

void Demo::createEntry(const char* scene, double start, double end, int prio) {
	auto it = _scenes.find(scene);
	if(it != _scenes.end()) {
		Entry e{it->second, start, end, prio};
		_timeline.push_back(e);
		std::sort(_timeline.begin(), _timeline.end());
		printf("Created entry for %s at [%f,%f] with %i priority\n", scene, start, end, prio);
	} else {
		printf("Scene %s does not exist.\n", scene);
	}
}

