#include <cassert>
#include "Mesh.h"
#include "MeshStream.h"
#include "Program.h"

void Mesh::destroy() {
	_streams.clear();
}

Mesh::Mesh() {
}

Mesh::Mesh(Mesh&& other) : _streams(std::move(other._streams)) {
	other._streams.clear();
}

Mesh::~Mesh() {
	destroy();
}

Mesh& Mesh::operator=(Mesh&& other) {
	destroy();

	_streams = std::move(other._streams);
	other._streams.clear(); //TODO Do we need to call this after std::move?

	return *this;
}

int Mesh::addStream(const void* data, const int count, const int stride) {
	_streams.emplace_back(data,count,stride);
	return _streams.size() - 1;
}

void Mesh::bind(Program& program) const {
	for(const MeshStream& stream : _streams) {
		stream.bind(program);
	}
}

void Mesh::draw(/*count*/) const {
	//TODO glDrawArrays
	//TODO IBO & glDrawElements
	//TODO Modes other than GL_TRIANGLES
	//TODO get count from somewhere.
}

MeshStream& Mesh::stream(int index) {
	assert(index >= 0 && index < _streams.size());
	return _streams[index];
}
