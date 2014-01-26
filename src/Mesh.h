#pragma once

#include <vector>
#include "util/string_hash.h"
#include "opengl.h"
#include "Program.h"

//TODO Move to it's own file (same goes for the stuff in Mesh.cc)
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

class Mesh {
	void destroy();

	std::vector<MeshStream> _streams;
public:
	Mesh();
	Mesh(Mesh&& other);
	Mesh(const Mesh&) = delete;
	~Mesh();

	Mesh& operator=(Mesh&& other);
	Mesh& operator=(const Mesh&) = delete;

	/**
	 * This adds and loads a stream into the mesh and into (GPU) memory.
	 * We need count and stride to calculate the data size to load.
	 * We seperate count and stride so we can save stride to use later with addAttribute.
	 * \return index of the added stream.
	 */
	int addStream(const void* data, const int count, const int stride);

	/**
	 * This will return a stream created by 'addStream'.
	 * You can use this to add attributes to stream.
	 */
	MeshStream& stream(int index);

	/**
	 * Bind all attributes from all streams.
	 * using glVertexAttribPointer, glEnableVertexAttribArray
	 * and others.
	 */
	void bind(Program& program) const;

	/**
	 * Draw this mesh
	 * using glDrawElements or glDrawArrays, or others.
	 * Requires the mesh to be bound first, using bind().
	 */
	//TODO IBO&SubMeshes
	void draw(/*count*/) const;

	//TODO AABB aabb() const;
};
