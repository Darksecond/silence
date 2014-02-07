#pragma once

#include <map>
#include "util/string_hash.h"
#include "Program.h"

class ProgramManager {
	std::map<core::string_hash, Program> _programs;
	const char* _root;
public:
	ProgramManager();
	static ProgramManager& inst();

	void loadFromFilename(const char* filename);
	//TODO void loadFromString(const char* vs, const char* fs);

	void unload(core::string_hash id);

	void unloadAll();
	void setRoot(const char* root);

	Program& get(core::string_hash id);

	//TODO void reloadFromFilename();
};
