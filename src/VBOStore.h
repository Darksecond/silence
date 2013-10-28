#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "GenericHandle.h"

typedef GenericHandle<12, 20> VBOHandle;

// Max values for 12 and 20 bit unsigned integers, this is most probably an invalid handle.
constexpr VBOHandle invalidVBOHandle{4095,1048575}; 

class VBOStore {
	GLuint* _vbos;
	int* _generations;
	const size_t _num_vbos;
public:
	VBOStore(const size_t num_vbos);
	~VBOStore();

	VBOHandle create(const size_t data_size, const void* data);
	void destroy(const VBOHandle handle);
	bool valid(const VBOHandle handle);
};
