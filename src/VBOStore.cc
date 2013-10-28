#include "VBOStore.h"
#include <cassert>

VBOStore::VBOStore(const size_t num_vbos) : _num_vbos(num_vbos) {
	_vbos = new GLuint[num_vbos];
	_generations = new int[num_vbos];
}

VBOStore::~VBOStore() {
	for(int i = 0; i < _num_vbos; ++i) {
		if(_vbos[i] != 0) {
			// TODO Move to (private) method
			glDeleteBuffers(1, &_vbos[i]);
			_vbos[i] = 0;
		}
	}

	delete [] _vbos;
	delete [] _generations;
}

VBOHandle VBOStore::create(const size_t data_size, const void* data) {
	for(int i = 0; i < _num_vbos; ++i) {
		if(_vbos[i] == 0) {

			// TODO Move to (private) method
			glGenBuffers(1, &_vbos[i]);
			glBindBuffer(GL_ARRAY_BUFFER, _vbos[i]);
			glBufferData(GL_ARRAY_BUFFER, data_size, data, GL_STATIC_DRAW);

			return VBOHandle{static_cast<uint32_t>(i), static_cast<uint32_t>(_generations[i])};
		}
	}
	return invalidVBOHandle;
}

void VBOStore::destroy(const VBOHandle handle) {
	assert(valid(handle));

	// TODO Move to (private) method
	glDeleteBuffers(1, &_vbos[handle.index]);
	_vbos[handle.index] = 0;

	++_generations[handle.index];
}

bool VBOStore::valid(const VBOHandle handle) {
	if(handle.index > _num_vbos) return false;

	return handle.generation == _generations[handle.index];
}
