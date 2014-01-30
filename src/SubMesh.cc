#include <cassert>
#include "SubMesh.h"

void SubMesh::destroy() {
	if(_obj) {
		glDeleteBuffers(1, &_obj);
		_obj = 0;
	}
}

int SubMesh::indice_size(const GLenum type) {
	switch(type) {
		case GL_UNSIGNED_BYTE:
			return sizeof(GLubyte);
		case GL_UNSIGNED_SHORT:
			return sizeof(GLushort);
		case GL_UNSIGNED_INT:
			return sizeof(GLuint);
		default:
			assert(0);
	}
}

SubMesh::SubMesh(const int count) : _obj(0), _count(count) {
}


SubMesh::SubMesh(SubMesh&& other) : _obj(other._obj), _count(other._count), _type(other._type) {
	other._obj = 0;
	other._count = 0;
}

SubMesh::~SubMesh() {
	destroy();
}

SubMesh& SubMesh::operator=(SubMesh&& other) {
	destroy();

	_obj = other._obj;
	_count = other._count;
	_type = other._type;
	
	other._obj = 0;
	other._count = 0;

	return *this;
}

//TODO Make GL_STATIC_DRAW specifyable
void SubMesh::loadIndices(const void* data, const GLenum type) {
	destroy();
	
	glGenBuffers(1, &_obj);
	bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indice_size(type), data, GL_STATIC_DRAW);
}

void SubMesh::bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _obj);
}

void SubMesh::draw() {
	if(_obj) {
		glDrawElements(GL_TRIANGLES, _count, _type, 0);
	} else {
		glDrawArrays(GL_TRIANGLES, 0, _count);
	}
}
