#include <cstdio>
#include "Program.h"

Program::Program() : _log(nullptr) {
	_obj = glCreateProgram();
}

Program::Program(Program&& other) : _obj(other._obj), _shaders(other._shaders), _log(other._log) {
	other._obj = 0;
	other._shaders.clear();
	other._log = nullptr;
}

Program::~Program() {
	destroy();
}

Program& Program::operator=(Program&& other) {
	destroy();

	_obj = other._obj;
	other._obj = 0;
	_shaders = other._shaders;
	other._shaders.clear();
	_log = other._log;
	other._log = nullptr;
	return *this;
}

void Program::attachShader(const Shader* shader) {
	_shaders.insert(shader);
}

bool Program::link() {
	for(const Shader* shader : _shaders)
		glAttachShader(_obj, shader->obj());

	glLinkProgram(_obj);

	for(const Shader* shader : _shaders)
		glDetachShader(_obj, shader->obj());

	_shaders.clear();

	// Check for link errors
	GLint status;
	glGetProgramiv(_obj, GL_LINK_STATUS, &status);
	if(status == GL_FALSE) {
		GLint length;
		glGetProgramiv(_obj, GL_INFO_LOG_LENGTH, &length);
		if(_log)
			delete [] _log;
		_log = new char[length+1];
		glGetProgramInfoLog(_obj, length, NULL, _log);
		return false;
	}

	// Cache attribute and uniform locations
	// Cache attributes
	GLint num_attributes;
	glGetProgramiv(_obj, GL_ACTIVE_ATTRIBUTES, &num_attributes);
	for(int i=0;i<num_attributes;++i) {
		char name[256];
		GLenum type;
		GLint size;
		glGetActiveAttrib(_obj, i, 256, NULL, &size, &type, name);
		_attributes[name] = glGetAttribLocation(_obj, name);
	}

	// Cache uniforms
	GLint num_uniforms;
	glGetProgramiv(_obj, GL_ACTIVE_UNIFORMS, &num_uniforms);
	for(int i=0;i<num_uniforms;++i) {
		char name[256];
		glGetActiveUniformName(_obj, i, 256, NULL, name);
		_uniforms[name] = glGetUniformLocation(_obj, name);
	}

	return true;
}

const char* Program::log() const {
	return _log;
}

void Program::destroy() {
	if(_obj) {
		glDeleteProgram(_obj);
		_obj = 0;
	}
	if(_log) {
		delete [] _log;
		_log = nullptr;
	}
}