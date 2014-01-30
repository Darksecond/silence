#pragma once

#include "opengl.h"

class SubMesh {
	int indice_size(GLenum type);
	void destroy();

	GLuint _obj;
	int _count;
	GLenum _type;
public:
	SubMesh(const int count);
	SubMesh(SubMesh&& other);
	SubMesh(const SubMesh&) = delete;
	~SubMesh();

	SubMesh& operator=(SubMesh&& other);
	SubMesh& operator=(const SubMesh&) = delete;

	/**
	 * Load and use indices.
	 * This will make draw use glDrawElements instead glDrawArrays.
	 * \param type must be GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT or GL_UNSIGNED_INT.
	 */
	void loadIndices(const void* data, const GLenum type);

	/**
	 * Bind the current submesh.
	 * This needs to be called before a submesh can be drawn.
	 */
	void bind();

	/**
	 * Draw a submesh.
	 * Requires Mesh (or accompanying VAO) to be bound first.
	 * Requires bind() to be called first.
	 * Currently this will always draw in GL_TRIANGLES mode.
	 */
	void draw();
};
