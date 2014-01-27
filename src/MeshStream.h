#pragma once

#include <vector>
#include "opengl.h" // GLenum, GLboolean, GLuint
#include "util/string_hash.h"

class Program;

class MeshStream {
	GLuint _obj;
	int _stride;

	struct Attribute {
		core::string_hash name;
		int count;
		GLenum type;
		GLboolean normalized;
		int offset;
	};

	std::vector<Attribute> _attributes;

	void destroy();
public:
	MeshStream(const void* data, const int count, const int stride);
	MeshStream(MeshStream&& other);
	MeshStream(const MeshStream&) = delete;
	~MeshStream();

	MeshStream& operator=(MeshStream&& other);
	MeshStream& operator=(const MeshStream&) = delete;

	/**
	 * Adds an attribute to the mesh.
	 * Stride is taken from the stream being used.
	 * \param name is the name of the attribute (to link to shader)
	 * \param count is the number of elements in this attribute (3 for vec3)
	 * \param type is the type of element (GL_FLOAT, GL_SHORT, GL_INT, etc)
	 * \param normalized true if the value needs to be normalized.
	 * \param offset is the location of the attribute within each vertex
	*/
	void addAttribute(const core::string_hash name, const int count, const GLenum type, const GLboolean normalized, const int offset);

	/**
	 * Bind all attributes
	 * using glVertexAttribPointer, glEnableVertexAttribArray
	 * and others.
	 */
	void bind(Program& program) const;
};
