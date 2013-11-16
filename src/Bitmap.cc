#include "Bitmap.h"
#include "stb_image.h"

Bitmap::Bitmap() : _pixels(nullptr) {
}

Bitmap::Bitmap(Bitmap&& other) : _width(other._width), _height(other._height), _channels(other._channels), _pixels(other._pixels) {
	other._pixels = nullptr;
}

Bitmap::~Bitmap() {
	destroy();
}

Bitmap& Bitmap::operator=(Bitmap&& other) {
	destroy();

	_width = other._width;
	_height = other._height;
	_channels = other._channels;
	_pixels = other._pixels;
	other._pixels = nullptr;
	return *this;
}

bool Bitmap::loadFromFilename(const char* filename) {
	destroy();

	_pixels = stbi_load(filename, &_width, &_height, &_channels, 0);
	if(_pixels)
		return true;
	else
		return false;
}

const uint8_t* Bitmap::pixels() const {
	return _pixels;
}

int Bitmap::width() const {
	return _width;
}

int Bitmap::height() const {
	return _height;
}

int Bitmap::channels() const {
	return _channels;
}

void Bitmap::destroy() {
	if(_pixels) {
		stbi_image_free(_pixels);
		_pixels = nullptr;
	}
}
