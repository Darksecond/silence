#pragma once

#include <unordered_set>
#include <map>
#include <GLM/gtc/type_ptr.hpp>
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
	void cache_attributes();
	void cache_uniforms();
	bool check_errors();
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

	/**
	 * Bind the Program for rendering
	 */
	void bind() const;

	GLint uniform(const char* name);
	GLint attribute(const char* name);

	/// Unknown uniforms will silently be ignored.
	/// These require the shader to be bound, using bind()
	//TODO check if uniform(...) returns -1, then don't do the glUniform* call
	inline void setUniform(const char* name, GLint value)   { glUniform1i(uniform(name), value); }
	inline void setUniform(const char* name, GLfloat value) { glUniform1f(uniform(name), value); }
	inline void setUniform(const char* name, const glm::mat3& m) { glUniformMatrix3fv(uniform(name), 1, GL_FALSE, glm::value_ptr(m)); }
	inline void setUniform(const char* name, const glm::mat4& m) { glUniformMatrix4fv(uniform(name), 1, GL_FALSE, glm::value_ptr(m)); }
	inline void setUniform(const char* name, const glm::vec2& v) { glUniform2fv(uniform(name), 1, glm::value_ptr(v)); }
	inline void setUniform(const char* name, const glm::vec3& v) { glUniform3fv(uniform(name), 1, glm::value_ptr(v)); }
	inline void setUniform(const char* name, const glm::vec4& v) { glUniform4fv(uniform(name), 1, glm::value_ptr(v)); }
};
