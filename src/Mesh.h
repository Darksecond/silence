#pragma once

#include <vector>
#include "MeshStream.h"
#include "SubMesh.h"

class Program;

class Mesh {
	void destroy();

	std::vector<MeshStream> _streams;
	std::vector<SubMesh> _sub_meshes;
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
	MeshStream& stream(const int index);

	/**
	 * Bind all attributes from all streams.
	 * using glVertexAttribPointer, glEnableVertexAttribArray
	 * and others.
	 */
	void bind(Program& program) const;

	/**
	 * Adds a submesh.
	 * \param count the number of vertices (or indices) to draw
	 * \return index of the added stream.
	 */
	//TODO Name instead of index?
	int addSubMesh(const int count);

	/**
	 * Get a submesh by index.
	 */
	//TODO Name instead of index?
	SubMesh& subMesh(const int index);

	//TODO AABB aabb() const;
};
