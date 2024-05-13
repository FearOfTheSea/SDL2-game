#include "environment.h"
#include <iostream>
#include <utility>
Environment::Environment(SDL_Renderer* renderer)
	: renderer(renderer)
{
}
Environment::~Environment()
{
	for (const auto& pair : environmentTextures)
	{
		SDL_DestroyTexture(pair.second);
	}
}
SDL_Texture* Environment::loadTextureFromBMP(const std::string& filePath)
{
	SDL_Surface* surface = SDL_LoadBMP(filePath.c_str());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	return texture;
}
void Environment::importAssets()
{
	environmentTextures['0'] = loadTextureFromBMP("ASSETS/Grass.bmp");
	environmentTextures['1'] = loadTextureFromBMP("ASSETS/Desert.bmp");
	environmentTextures['2'] = loadTextureFromBMP("ASSETS/Mountain.bmp");
	environmentTextures['3'] = loadTextureFromBMP("ASSETS/Forest.bmp");
}
SDL_Texture* Environment::getTextureFromID(const char& ID) const
{
	auto it = environmentTextures.find(ID);
	if (it != environmentTextures.end()) {
		return it->second;
	}
	return nullptr;
}
