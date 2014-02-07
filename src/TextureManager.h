#pragma once

#include <map>
#include "util/string_hash.h"
#include "Texture.h"

class TextureManager {
	std::map<core::string_hash, Texture> _textures;
	const char* _root;
public:
	TextureManager();
	static TextureManager& inst();

	/**
	 * Load a texture from disk, based on filename.
	 * \param filename will also be the id.
	 */
	void loadFromFilename(const char* filename);

	void unload(core::string_hash id);

	void unloadAll();
	void setRoot(const char* root);

	Texture& get(core::string_hash id);

	//TODO void reloadFromFile();
	//     This will use a array of filenames stored, so it knows how and what to reload.
};
