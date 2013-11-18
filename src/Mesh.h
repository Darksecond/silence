#pragma once

class Mesh {
public:
	Mesh();
	Mesh(Mesh&& other);
	Mesh(const Mesh&) = delete;

	Mesh& operator=(Mesh&& other);
	Mesh& operator=(const Mesh&) = delete;

	bool loadFromGeometry(const Geometry& geometry);

	void bind() const;
	void draw(Program& program) const;

	//AABB aabb() const;
};
