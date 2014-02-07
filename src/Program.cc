#include <cstdio>
#include "Program.h"

Program::Program() : _log(nullptr) {
	_obj = glCreateProgram();
}

Program::Program(Program&& other) : _obj(other._obj), _shaders(other._shaders), _log(other._log), _attributes(other._attributes), _uniforms(other._uniforms) {
	other._obj = 0;
	other._shaders.clear();
	other._attributes.clear();
	other._uniforms.clear();
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
	_attributes = std::move(other._attributes);
	other._attributes.clear();
	_uniforms = std::move(other._uniforms);
	other._uniforms.clear();
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
	if(check_errors() == false) return false;

	cache_attributes();
	cache_uniforms();

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
	_attributes.clear();
	_uniforms.clear();
}

void Program::cache_attributes() {
	GLint num_attributes;
	glGetProgramiv(_obj, GL_ACTIVE_ATTRIBUTES, &num_attributes);
	for(int i=0;i<num_attributes;++i) {
		char name[256];
		GLenum type;
		GLint size;
		glGetActiveAttrib(_obj, i, 256, NULL, &size, &type, name);
		_attributes[name] = glGetAttribLocation(_obj, name);
	}
}

void Program::cache_uniforms() {
	GLint num_uniforms;
	glGetProgramiv(_obj, GL_ACTIVE_UNIFORMS, &num_uniforms);
	for(int i=0;i<num_uniforms;++i) {
		char name[256];
		glGetActiveUniformName(_obj, i, 256, NULL, name);
		_uniforms[name] = glGetUniformLocation(_obj, name);
	}
}

bool Program::check_errors() {
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
	return true;
}

void Program::bind() const {
	glUseProgram(_obj);
}

GLint Program::uniform(core::string_hash name) {
	auto u = _uniforms.find(name);
	if(u != _uniforms.end()) {
		return u->second;
	}
	return -1;
}

GLint Program::attribute(core::string_hash name) {
	auto a = _attributes.find(name);
	if(a != _attributes.end()) {
		return a->second;
	}
	return -1;
}
