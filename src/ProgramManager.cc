#include "ProgramManager.h"
#include <cassert>
#include <string>
#include "Shader.h"

ProgramManager::ProgramManager() : _root("") {
}

ProgramManager& ProgramManager::inst() {
	static ProgramManager instance;
	return instance;
}

void ProgramManager::loadFromFilename(const char* filename) {
	// Create full paths by appending filename to _root and then appending either ".vs" or ".fs"
	std::string vs_path(_root);
	vs_path.append(filename);
	vs_path.append(".vs");

	std::string fs_path(_root);
	fs_path.append(filename);
	fs_path.append(".fs");

	Shader vs(GL_VERTEX_SHADER);
	if(!vs.loadFromFilename(vs_path.c_str())) {
		printf("VS Load failed");
		exit(-1);
	}
	if(!vs.compile()) {
		printf("VS Compile failed: %s\n",vs.log());
		exit(-1);
	}

	Shader fs(GL_FRAGMENT_SHADER);
	if(!fs.loadFromFilename(fs_path.c_str())) {
		printf("FS Load failed");
		exit(-1);
	}
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

	_programs.emplace(filename, std::move(p));
}

void ProgramManager::unload(core::string_hash id) {
	_programs.erase(id);
}

void ProgramManager::unloadAll() {
	_programs.clear();
}

void ProgramManager::setRoot(const char* root) {
	_root = root;
}

Program& ProgramManager::get(core::string_hash id) {
	auto it = _programs.find(id);
	assert(it != _programs.end());
	return it->second;
}
