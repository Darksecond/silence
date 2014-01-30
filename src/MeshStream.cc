#include "MeshStream.h"
#include "Program.h"

//TODO Make GL_STATIC_DRAW specifyable
MeshStream::MeshStream(const void* data, const int count, const int stride) {
	glGenBuffers(1, &_obj);
	_stride = stride;

	glBindBuffer(GL_ARRAY_BUFFER, _obj);
	size_t data_size = count*stride;
	glBufferData(GL_ARRAY_BUFFER, data_size, data, GL_STATIC_DRAW);
}

MeshStream::MeshStream(MeshStream&& other) : _obj(other._obj), _stride(other._stride), _attributes(std::move(other._attributes)) {
	other._attributes.clear();
	other._obj = 0;
}

MeshStream::~MeshStream() {
	destroy();
}

MeshStream& MeshStream::operator=(MeshStream&& other) {
	destroy();

	_obj = other._obj;
	_stride = other._stride;
	_attributes = std::move(other._attributes);

	other._obj = 0;
	other._attributes.clear(); //TODO Do we need to call this after std::move?
	return *this;
}

void MeshStream::destroy() {
	if(_obj) {
		glDeleteBuffers(1, &_obj);
		_obj = 0;
	}
	_attributes.clear();
}

void MeshStream::addAttribute(const core::string_hash name, const int count, const GLenum type, const GLboolean normalized, const int offset) {
	Attribute attrib = {name, count, type, normalized, offset};
	_attributes.push_back(attrib);
}

void MeshStream::bind(Program& program) const {
	glBindBuffer(GL_ARRAY_BUFFER, _obj);
	for(const Attribute& attrib : _attributes) {
		GLint program_attribute = program.attribute(attrib.name);
		glVertexAttribPointer(
				program_attribute,
				attrib.count,
				attrib.type,
				attrib.normalized,
				_stride,
				reinterpret_cast<const GLvoid *>(attrib.offset)
				);
		glEnableVertexAttribArray(program_attribute);
	}
}
