#pragma once

#include <cstdint>

class Bitmap {
	int _width;
	int _height;
	int _channels;
	uint8_t* _pixels;

	void destroy();
public:
	Bitmap();
	Bitmap(Bitmap&& other);
	Bitmap(const Bitmap&) = delete;
	~Bitmap();

	Bitmap& operator=(Bitmap&& other);
	Bitmap& operator=(const Bitmap&) = delete;

	/**
	 * Load a bitmap from a filename using standard filesystem library functions (fopen, fread, etc)
	 * This will use stb_image, so it can accept tga, jpeg and png files (amongst others).
	 * \returns true if loaded successfully, false if not.
	 */
	bool loadFromFilename(const char* filename);

	const uint8_t* pixels() const;
	int width() const;
	int height() const;

	/**
	 * Get the number of channels for this bitmap.
	 * 1 = Grayscale
	 * 2 = Grayscale with Alpha
	 * 3 = RGB
	 * 4 = RGBA
	 */
	int channels() const;
};
