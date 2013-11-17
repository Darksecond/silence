#include "Texture.h"
#include <cassert>

Texture::Texture() {
	glGenTextures(1, &_obj);
	bind();

	// Default parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

Texture::Texture(Texture&& other) : _obj(other._obj) {
	other._obj = 0;
}

Texture::~Texture() {
	destroy();
}

Texture& Texture::operator=(Texture&& other) {
	destroy();

	_obj = other._obj;
	other._obj = 0;
	return *this;
}

bool Texture::loadFromBitmap(const Bitmap& bitmap, const int level) {
	if((bitmap.width() & (bitmap.width() - 1)) != 0) return false;
	if((bitmap.height() & (bitmap.height() - 1)) != 0) return false;

	GLenum format;
	switch(bitmap.channels()) {
		case 1:
			format = GL_LUMINANCE;
			break;
		case 2:
			format = GL_LUMINANCE_ALPHA;
			break;
		case 3:
			format = GL_RGB;
			break;
		case 4:
			format = GL_RGBA;
			break;
	}

	glTexImage2D(GL_TEXTURE_2D, level, format, (GLsizei)bitmap.width(),
			(GLsizei)bitmap.height(), 0, format,
			GL_UNSIGNED_BYTE, bitmap.pixels());

	return true;
}

void Texture::generateMipmaps() {
	glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::bind(const GLenum unit) const {
	if(unit)
		glActiveTexture(unit);
	glBindTexture(GL_TEXTURE_2D, _obj);
}

void Texture::destroy() {
	if(_obj) {
		glDeleteTextures(1, &_obj);
		_obj = 0;
	}
}
