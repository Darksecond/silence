#pragma once

#include "Program.h"

class Mesh {
	void destroy();
public:
	Mesh();
	Mesh(Mesh&& other);
	Mesh(const Mesh&) = delete;

	Mesh& operator=(Mesh&& other);
	Mesh& operator=(const Mesh&) = delete;

	void addStream(void* data, int count, int stride);
	void addAttribute(int stream_index, core::string_hash name, ...);

	void draw(Program& program) const;

	//AABB aabb() const;
};
