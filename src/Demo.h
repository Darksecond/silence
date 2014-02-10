#pragma once

#include <map>
#include "util/string_hash.h"
#include "Mesh.h"
#include "FrameTimer.h"
#include "FPS.h"

class Scene;

class Demo {
	struct Entry {
		Scene* scene;
		double start;
		double end;
		int prio;

		inline bool operator<(const Entry& other) const {
			return prio < other.prio;
		}
	};

	FrameTimer _ft;
	FPS _fps;
	std::map<core::string_hash, Scene*> _scenes;
	std::vector<Entry> _timeline;
	bool _paused;

	struct {
		double start;
		double end;
		bool active;
	} _looping;

	void handleInput();
public:
	Demo();
	void init();
	void kill();
	void update();
	void render();

	void addScene(const char* name, Scene* scene);

	/**
	 * \param scene scene to create a entry for
	 * \param start start time in seconds
	 * \param end end time in seconds
	 * \param prio render/update priority, higher priorities get used first
	 */
	void createEntry(const char* scene, double start, double end, int prio);
};
