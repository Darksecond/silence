#pragma once

#include <map>
#include "util/string_hash.h"
#include "Event.h"

class SyncManager {
	std::map<core::string_hash, Event> _events;
public:
	static SyncManager& inst();

	void createEvent(const char* name, double start, float duration);
	const Event& getEvent(const char* name) const;
};
