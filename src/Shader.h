#pragma once

#include "opengl.h"

class Shader {
	GLuint _obj;
	char* _log;

	void destroy();
public:
	/**
	 * Create a shader of type
	 */
	Shader(const GLenum type);
	Shader(Shader&& other);
	Shader(const Shader&) = delete;
	~Shader();

	Shader& operator=(Shader&& other);
	Shader& operator=(const Shader&) = delete;

	/**
	 * Load the shader source from a source string.
	 * You need to call compile to actually compile the shader, this only sets the source.
	 * \returns true if loaded successfully, false if not.
	 */
	void loadFromString(const char* source);
	
	//TODO bool loadFromFile(File& file);
	//TODO bool loadFromFilename(const char* filename);

	/**
	 * Compile the shader
	 * \returns true if successful, false is not successful.
	 */
	bool compile();

	/**
	 * Get the log, or nullptr
	 * The returned log is valid until the Shader is destroyed.
	 * \returns nullptr if there is no log available, otherwise it returns a log
	 */
	const char* log() const;
	
	/**
	 * Get the underlying opengl object
	 */
	GLuint obj() const;
};
