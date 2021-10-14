#pragma once

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <unordered_map>

#include "Texture.h"

//Enum with the possible font sizes
enum class FontSize {
	Title = 150,
	VeryBig = 50,
	Big = 40,
	Medium = 30,
	Small = 20,
	VerySmall = 10
};

//Class to load and store all kinds of resources
class Loader {

	private:
		//Renderer of the game.
		static SDL_Renderer* renderer;

		//Loaded textures
		static std::unordered_map<std::string, Texture*> textures;

		//Loaded songs
		static std::unordered_map<std::string, Mix_Music*> songs;

		//Loaded sounds
		static std::unordered_map<std::string, Mix_Chunk*> sounds;

		//Loaded fonts
		static std::unordered_map<std::string, TTF_Font*> fonts;

		//Loaded pointers
		static std::unordered_map<std::string, SDL_Cursor*> cursors;

	public:
		//Initiates the loader by providing the renderer
		static void initLoader(SDL_Renderer* renderer);

		//Loads all the resources specified in the given path
		static void loadFiles(std::string filePath);
	
		//Unloads all the resources specified in the given path
		static void unloadFiles(std::string filePath);

		//Gets a texture
		static Texture* getTexture(std::string textureID);

		//Gets a song
		static Mix_Music* getSong(std::string songID);

		//Gets a sound
		static Mix_Chunk* getSound(std::string soundID);

		//Gets a texture based on a string
		static Texture* getText(std::string fontID, std::string text, SDL_Color color, FontSize size);
		static Texture* getText(std::string fontID, std::wstring text, SDL_Color color, FontSize size);

		static Texture* getText(std::string fontID, std::string text, SDL_Color color, FontSize size, int maxWidth);
		static Texture* getText(std::string fontID, std::wstring text, SDL_Color color, FontSize size, int maxWidth);

		static Texture* getUnderlineText(std::string fontID, std::string text, SDL_Color color, FontSize size);
		static Texture* getUnderlineText(std::string fontID, std::wstring text, SDL_Color color, FontSize size);

		static Texture* getUnderlineText(std::string fontID, std::string text, SDL_Color color, FontSize size, int maxWidth);
		static Texture* getUnderlineText(std::string fontID, std::wstring text, SDL_Color color, FontSize size, int maxWidth);

		//Sets the cursor texture
		static void setCursor(std::string cursorID);
};