#pragma once

#include <SDL.h>
#include <unordered_map>
#include <string>

class Environment
{
public:
	Environment() = default;
	Environment(SDL_Renderer* renderer);
	~Environment();
	void importAssets();
	SDL_Texture* getTextureFromID(const char& ID) const;
private:
	SDL_Texture* loadTextureFromBMP(const std::string& filePath);
	SDL_Renderer* renderer{ nullptr };
	std::unordered_map<char, SDL_Texture*> environmentTextures;
};