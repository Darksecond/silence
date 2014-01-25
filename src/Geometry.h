#pragma once

#include "util/string_hash.h"

//TODO I could reverse the interface and instead of providing access to streams and attributes, let the Geometry add streams and attributes to a mesh.
//     This might be more OO-esque because we know less about the inner working of geometry and instead trust it to do the right thing.
//     Mesh would get a couple of methods like 'addStream' and 'addAttribute', which would do the right thing.
//     The more i think about it, the more it seems like a good idea.
//     Geometry would get a 'loadIntoMesh' method, or maybe 'getMesh', or 'generateMesh', or something like it.
//
//     In Irrlicht, a Mesh has MeshBuffers.
//     A Meshbuffer has a VBO and an IBO, by the looks of it.
//     http://irrlicht.sourceforge.net/docu/classirr_1_1scene_1_1_i_mesh_buffer.html
//     http://irrlicht.sourceforge.net/docu/classirr_1_1scene_1_1_i_mesh.html
class Geometry {
public:
	struct Attribute {
		int stream;
		core::string_hash name;
		int size;
		GLenum type;
		size_t stride;
		size_t offset;
	};

	// Streams
	// Streams will be converted into VBO's in Mesh.
	int stream_count() const;
	//TODO Maybe move stride into a Stream struct, as it's more a general Stream thing than anything else.
	void* stream(int i);

	// Attributes
	// Attributes is what defines the vertex format.
	// They use a stream for their data.
	int attribute_count() const;
	const Attribute& attribute(int i) const;

	//TODO Don't really like this, as it basically tells you you _are_ going to use a vector, but it's an option.
	//std::vector<Attribute> attributes() const;
	
	//TODO IBO (indexes)
};
