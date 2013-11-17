#pragma once

#include "opengl.h"
#include "Bitmap.h"

class Texture {
	GLuint _obj;
	
	void destroy();
public:
	/**
	 * Creates a new Texture, will bind() automatically.
	 */
	Texture();
	Texture(Texture&& other);
	Texture(const Texture&) = delete;
	~Texture();

	Texture& operator=(Texture&& other);
	Texture& operator=(const Texture&) = delete;

	bool loadFromBitmap(const Bitmap& bitmap, const int level=0);

	/**
	 * Generate mipmaps.
	 * A level 0 bitmap is required.
	 */
	void generateMipmaps();

	void bind(const GLenum unit = 0) const;
};
