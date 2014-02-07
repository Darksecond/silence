#include "Shader.h"
#include <cstdio>

Shader::Shader(const GLenum type) : _log(nullptr) {
	_obj = glCreateShader(type);
}

Shader::Shader(Shader&& other) : _obj(other._obj), _log(other._log) {
	other._obj = 0;
	other._log = nullptr;
}

Shader::~Shader() {
	destroy();
}

Shader& Shader::operator=(Shader&& other) {
	destroy();

	_obj = other._obj;
	other._obj = 0;
	_log = other._log;
	other._log = nullptr;
	return *this;
}

void Shader::loadFromString(const char* source) {
	glShaderSource(_obj, 1, &source, NULL);
}

bool Shader::loadFromFilename(const char* filename) {
	FILE* shader;
	if(!(shader = fopen(filename, "r"))) {
		return false;
	}

	// Find out file size
	fseek(shader, 0, SEEK_END);
	long len = ftell(shader);
	fseek(shader, 0, SEEK_SET);

	char* str = new char[len];
	long r = fread(str, 1, len, shader);
	str[r - 1] = '\0';
	
	loadFromString(str);

	delete [] str;

	fclose(shader);
	return true;
}

bool Shader::compile() {
	glCompileShader(_obj);

	// Check for compile errors
	GLint status;
	glGetShaderiv(_obj, GL_COMPILE_STATUS, &status);
	if(status == GL_FALSE) {
		GLint length;
		glGetShaderiv(_obj, GL_INFO_LOG_LENGTH, &length);
		if(_log) {
			delete [] _log;
		}
		_log = new char[length+1];
		glGetShaderInfoLog(_obj, length, NULL, _log);
		return false;
	}
	return true;
}

const char* Shader::log() const {
	return _log;
}

GLuint Shader::obj() const {
	return _obj;
}

void Shader::destroy() {
	if(_obj) {
		glDeleteShader(_obj);
		_obj = 0;
	}
	if(_log) {
		delete [] _log;
		_log = 0;
	}
}
