#pragma once

#include <unordered_set>
#include <map>
#include "util/string_hash.h"
#include "opengl.h"
#include "Shader.h"

class Program {
	GLuint _obj;
	char* _log;
	std::unordered_set<const Shader*> _shaders;

	std::map<core::string_hash, GLint> _attributes;
	std::map<core::string_hash, GLint> _uniforms;

	void destroy();
public:
	Program();
	Program(Program&& other);
	Program(const Program&) = delete;
	~Program();

	Program& operator=(Program&& other);
	Program& operator=(const Program&) = delete;

	/**
	 * Attach a shader object
	 * Program will keep a pointer to shader around until link() is called, or the program is deleted.
	 * \returns false is attachment failed
	 */
	void attachShader(const Shader* shader);

	/**
	 * Link the program.
	 * \returns false if linking failed.
	 */
	bool link();

	/**
	 * Returns the log, or nullptr
	 * \returns a nullptr, or a log if there is one available.
	 */
	const char* log() const;

	//TODO bind(),unbind(),obj()
	//TODO setAttribute(...), setUniform(...), setUniformBlock(...)
};
