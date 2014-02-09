#include "SyncManager.h"
#include <cstdio>
#include <cassert>

SyncManager& SyncManager::inst() {
	static SyncManager instance;
	return instance;
}

void SyncManager::createEvent(const char* name, double start, float duration) {
	_events.emplace(name, Event(start, duration));
}

const Event& SyncManager::getEvent(const char* name) const {
	auto it = _events.find(name);
	assert(it != _events.end());
	return it->second;
}
