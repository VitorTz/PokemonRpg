#include "../include/texture_pool.h"
#include "../include/util.h"


poke::TexturePool::TexturePool() {
	this->textureMap.reserve(512);
}


poke::TexturePool::~TexturePool() {
	for (auto& pair : this->textureMap) {
		UnloadTexture(pair.second);
	}
}


Texture2D poke::TexturePool::load(const char* file_name) {
	const unsigned long h = poke::hash(file_name);
	if (this->textureMap.find(h) == this->textureMap.end()) {
		this->textureMap.insert({ h, LoadTexture(file_name) });
	}
	return this->textureMap[h];
}


void poke::TexturePool::erase(const char* file_name) {
	const unsigned long h = poke::hash(file_name);
	if (this->textureMap.find(h) != this->textureMap.end()) {
		UnloadTexture(this->textureMap[h]);
	}
	this->textureMap.erase(h);
}


void poke::TexturePool::clear() {
	for (auto& pair : this->textureMap) {
		UnloadTexture(pair.second);
	}
	this->textureMap.clear();
}


std::size_t poke::TexturePool::size() const {
	return this->textureMap.size();
}