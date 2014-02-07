#include "TextureManager.h"
#include <cassert>
#include <string>

static void err() {
	GLenum err = glGetError();
	if(err != GL_NO_ERROR) {
		printf("OpenGL Error %i.\n",err);
		exit(-1);
	}
}

TextureManager::TextureManager() : _root("") {
}

TextureManager& TextureManager::inst() {
	static TextureManager instance;
	return instance;
}

void TextureManager::loadFromFilename(const char* filename) {
	// Create full path by appending filename to _root
	std::string full_path(_root);
	full_path.append(filename);

	// Load a bitmap from disk, using full_path
	Bitmap b;
	if(!b.loadFromFilename(full_path.c_str())) {
		printf("Bitmap loading unsuccessful\n");
		exit(-1);
	}

	// Create Texture from Bitmap
	Texture tex;
	if(!tex.loadFromBitmap(b)) {
		printf("Texture loading failed\n");
		exit(-1);
	}
	tex.generateMipmaps();
	err();

	// Save Texture into _textures
	_textures.emplace(filename, std::move(tex));
}

void TextureManager::unload(core::string_hash id) {
	_textures.erase(id);
}

void TextureManager::unloadAll() {
	_textures.clear();
}

void TextureManager::setRoot(const char* root) {
	_root = root;
}

Texture& TextureManager::get(core::string_hash id) {
	auto it = _textures.find(id);
	assert(it != _textures.end());
	return it->second;
}
