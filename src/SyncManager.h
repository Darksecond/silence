#pragma once

#include <map>
#include "util/string_hash.h"
#include "Event.h"
#include "Sequence.h"

class SyncManager {
	std::map<core::string_hash, Event> _events;
	std::map<core::string_hash, Sequence> _sequences;
public:
	static SyncManager& inst();

	void createEvent(const char* name, double start, float duration);
	const Event& getEvent(const char* name) const;

	Sequence& createSequence(const char* name);
	const Sequence& getSequence(const char* name) const;
};
