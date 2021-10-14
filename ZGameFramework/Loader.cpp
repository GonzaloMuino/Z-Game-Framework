#include <iostream>
#include <fstream>
#include <SDL_image.h>
#include <comdef.h>
#include <string>

#include "Loader.h"
#include "Utils.h"

SDL_Renderer* Loader::renderer;

std::unordered_map<std::string, Texture*> Loader::textures;
std::unordered_map<std::string, Mix_Music*> Loader::songs;
std::unordered_map<std::string, Mix_Chunk*> Loader::sounds;
std::unordered_map<std::string, TTF_Font*> Loader::fonts;
std::unordered_map<std::string, SDL_Cursor*> Loader::cursors;

//Initiates the loader by providing the renderer
void Loader::initLoader(SDL_Renderer* renderer) {
	//We asign the renderer
	Loader::renderer = renderer;

	//We load the placeholders
	SDL_Surface* surface = IMG_Load("Resources/Placeholder.png");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Loader::renderer, surface);
	
	Texture* texturePlaceholder = new Texture(Loader::renderer, texture);
	Mix_Music* musicPlaceholder = Mix_LoadMUS("Resources/Placeholder.wav");
	Mix_Chunk* soundPlaceholder = Mix_LoadWAV("Resources/Placeholder.wav");
	TTF_Font* fontPlaceholder = TTF_OpenFont("Resources/Placeholder.ttf", 10);
	SDL_Cursor* mousePointerPlaceholder = SDL_CreateColorCursor(surface, 0, 0);

	Loader::textures.insert({ "Placeholder", texturePlaceholder });
	Loader::songs.insert({ "Placeholder", musicPlaceholder });
	Loader::sounds.insert({ "Placeholder", soundPlaceholder });
	Loader::fonts.insert({ "Placeholder", fontPlaceholder });
	Loader::cursors.insert({ "Placeholder", mousePointerPlaceholder });

	SDL_FreeSurface(surface);
}

//Loads all the resources specified in the given file
void Loader::loadFiles(std::string filePath) {
	//We open the file
	std::ifstream file;
	filePath = "Resources/" + filePath + ".txt";
	file.open(filePath);
	std::string line;

	//We iterate over the file
	while (getline(file, line)) {
		//We check if it's a comment (They start with //)
		if (line.size() > 2 && line.at(0) != '/' && line.at(1) != '/') {
			//It is not a comment. We divide the line in before and after the ;
			std::vector<std::string> lineParts = Utils::splitString(line, ";");

			//We get filetype, which is before the ;, and the file location
			int fileType = atoi(lineParts.at(0).c_str());
			lineParts.at(1) = "Resources/" + lineParts.at(1);

			switch (fileType) {
				case 1: //Texture
				{
					//We get all the information
					std::string pathTexture = lineParts.at(1);
					std::vector<std::string> pathParts = Utils::splitString(pathTexture, "/");
					std::string IDTexture = pathParts.at(pathParts.size() - 1);

					//We create the texture
					pathTexture.append(".png");
					SDL_Surface* surface = IMG_Load(pathTexture.c_str());
					SDL_Texture* SDLtexture = SDL_CreateTextureFromSurface(Loader::renderer, surface);

					SDL_SetTextureBlendMode(SDLtexture, SDL_BLENDMODE_BLEND);

					SDL_FreeSurface(surface);
					Texture* texture = new Texture(Loader::renderer, SDLtexture);

					//We save the texture
					Loader::textures.insert({ IDTexture.c_str(), texture });
					break;
				}

				case 2: //Song
				{
					//We load the song
					std::string songPath = lineParts.at(1);
					songPath.append(".wav");

					Mix_Music* song = Mix_LoadMUS(songPath.c_str());
					
					std::vector<std::string> pathParts = Utils::splitString(lineParts.at(1), "/");
					std::string IDSong = pathParts.at(pathParts.size() - 1);

					//We save the song
					Loader::songs.insert({ IDSong.c_str(),song });
					break;
				}

				case 3: //Sound effect
				{
					//We load the sound
					std::string soundPath = lineParts.at(1);
					soundPath.append(".wav");
					Mix_Chunk* sound = Mix_LoadWAV(soundPath.c_str());

					std::vector<std::string> pathParts = Utils::splitString(lineParts.at(1), "/");
					std::string IDSound = pathParts.at(pathParts.size() - 1);

					//We save the sound
					Loader::sounds.insert({ IDSound.c_str(),sound });
					break;
				}

				case 4: //TTF
				{
					//We load the Font
					std::string pathTTF = lineParts.at(1);
					pathTTF.append(".ttf");

					std::vector<std::string> pathParts = Utils::splitString(lineParts.at(1), "/");
					std::string IDTTF= pathParts.at(pathParts.size() - 1);

					//We are going to create now different fonts with different sizes

					//Title size
					std::string titleID = IDTTF + "-Title";
					TTF_Font* titleFont = TTF_OpenFont(pathTTF.c_str(), static_cast<int>(FontSize::Title));
					Loader::fonts.insert({titleID, titleFont});

					//Title size
					std::string veryBigID = IDTTF + "-VeryBig";
					TTF_Font* veryBigFont = TTF_OpenFont(pathTTF.c_str(), static_cast<int>(FontSize::VeryBig));
					Loader::fonts.insert({ veryBigID, veryBigFont });

					//Title size
					std::string bigID = IDTTF + "-Big";
					TTF_Font* bigFont = TTF_OpenFont(pathTTF.c_str(), static_cast<int>(FontSize::Big));
					Loader::fonts.insert({ bigID, bigFont });

					//Title size
					std::string mediumID = IDTTF + "-Medium";
					TTF_Font* mediumFont = TTF_OpenFont(pathTTF.c_str(), static_cast<int>(FontSize::Medium));
					Loader::fonts.insert({ mediumID, mediumFont });

					//Title size
					std::string smallID = IDTTF + "-Small";
					TTF_Font* smallFont = TTF_OpenFont(pathTTF.c_str(), static_cast<int>(FontSize::Small));
					Loader::fonts.insert({ smallID, smallFont });

					//Title size
					std::string verySmallID = IDTTF + "-VerySmall";
					TTF_Font* verySmallFont = TTF_OpenFont(pathTTF.c_str(), static_cast<int>(FontSize::VerySmall));
					Loader::fonts.insert({ verySmallID, verySmallFont });
					break;
				}

				case 5: //Mouse Pointer Texture
				{
					//We get all the information
					std::string pathTexture = lineParts.at(1);
					std::vector<std::string> pathParts = Utils::splitString(pathTexture, "/");
					std::string IDTexture = pathParts.at(pathParts.size() - 1);

					int alpha = 255;
					if (lineParts.size() == 3) {
						alpha = atoi(lineParts.at(2).c_str());
					}

					//We create the texture
					pathTexture.append(".png");
					SDL_Surface* surface = IMG_Load(pathTexture.c_str());
					SDL_Cursor* SDLCursor = SDL_CreateColorCursor(surface,0,0);

					Loader::cursors.insert({ IDTexture.c_str(), SDLCursor });
					break;
				}
			}
		}
	}
	file.close();
}

//Unloads all the resources specified in the given path
void Loader::unloadFiles(std::string filePath) {
	std::ifstream file;
	filePath = "Resources/" + filePath + ".txt";
	file.open(filePath);

	std::string line;

	while (getline(file, line)) {
		//We check if it's a comment (They start with //)
		if (line.size() > 2 && line.at(0) != '/' && line.at(1) != '/') {
			//It is not a comment
			std::vector<std::string> lineParts = Utils::splitString(line, ";");

			//We get filetype:
			int fileType = atoi(lineParts.at(0).c_str());

			switch (fileType) {
				case 1: //Texture
				{
					//We get all the information
					std::string pathTexture = lineParts.at(1);
					std::vector<std::string> pathParts = Utils::splitString(pathTexture, "/");
					std::string IDTexture = pathParts.at(pathParts.size() - 1);

					std::unordered_map<std::string, Texture*>::const_iterator iterator = Loader::textures.find(IDTexture);
					if (iterator != Loader::textures.end()) {
						//First we destroy the SDL_Texture, then we liberate the memory of our own Texture.
						delete(iterator->second);
						Loader::textures.erase(iterator);
					}

					break;
				}

				case 2: //Song
				{
					std::vector<std::string> pathParts = Utils::splitString(lineParts.at(1), "/");
					std::string IDSong = pathParts.at(pathParts.size() - 1);

					std::unordered_map<std::string, Mix_Music*>::const_iterator iterator = Loader::songs.find(IDSong);
					if (iterator != Loader::songs.end()) {
						Mix_FreeMusic(iterator->second);
						Loader::songs.erase(iterator);
					}

					break;
				}

				case 3: //Sound effect
				{
					std::vector<std::string> pathParts = Utils::splitString(lineParts.at(1), "/");
					std::string IDSound = pathParts.at(pathParts.size() - 1);

					std::unordered_map<std::string, Mix_Chunk*>::const_iterator iterator = Loader::sounds.find(IDSound);
					if (iterator != Loader::sounds.end()) {
						Mix_FreeChunk(iterator->second);
						Loader::sounds.erase(iterator);
					}
					break;
				}

				case 4: //TTF
				{
					//We load the Font
					std::string pathTTF = lineParts.at(1);
					pathTTF.append(".ttf");
					int size = std::atoi(lineParts.at(2).c_str());

					std::vector<std::string> pathParts = Utils::splitString(lineParts.at(1), "/");
					std::string IDTTF = pathParts.at(pathParts.size() - 1);

					std::unordered_map<std::string, TTF_Font*>::const_iterator iterator = Loader::fonts.find(IDTTF);
					if (iterator != Loader::fonts.end()) {
						TTF_CloseFont(iterator->second);
						Loader::fonts.erase(iterator);
					}
					break;
				}

				case 5: //Texture
				{
					//We get all the information
					std::string pathTexture = lineParts.at(1);
					std::vector<std::string> pathParts = Utils::splitString(pathTexture, "/");
					std::string IDTexture = pathParts.at(pathParts.size() - 1);

					std::unordered_map<std::string, SDL_Cursor*>::const_iterator iterator = Loader::cursors.find(IDTexture);
					if (iterator != Loader::cursors.end()) {
						Loader::cursors.erase(iterator);
					}

					break;
				}
			}
		}
	}
	file.close();
}

//Gets a texture
Texture* Loader::getTexture(std::string textureID) {
	std::unordered_map<std::string, Texture*>::const_iterator iterator = Loader::textures.find(textureID);
	if (iterator == Loader::textures.end()) {
		//If we don't find the texture we return the placeholder
		return Loader::textures.at("Placeholder");
	}else{
		return iterator->second;
	}
}

void Loader::setCursor(std::string cursorID) {
	std::unordered_map<std::string, SDL_Cursor*>::const_iterator iterator = Loader::cursors.find(cursorID);
	if (iterator != Loader::cursors.end()) {
		//If we don't find the texture we return the placeholder
		SDL_SetCursor(iterator->second);
	}
}

//Gets a song
Mix_Music* Loader::getSong(std::string songID) {
	std::unordered_map<std::string, Mix_Music*>::const_iterator iterator = Loader::songs.find(songID);
	if (iterator == Loader::songs.end()) {
		//If we don't find the song we return the placeholder
		return Loader::songs.at("Placeholder");
	}
	else {
		return iterator->second;
	}
}

//Gets a sound
Mix_Chunk* Loader::getSound(std::string soundID) {
	std::unordered_map<std::string, Mix_Chunk*>::const_iterator iterator = Loader::sounds.find(soundID);
	if (iterator == Loader::sounds.end()) {
		//If we don't find the sound we return the placeholder
		return Loader::sounds.at("Placeholder");
	}
	else {
		return iterator->second;
	}
}

//Gets a texture based on a string
Texture* Loader::getText(std::string fontID, std::string text, SDL_Color color, FontSize size) {
	std::string sizeIndicator;
	switch (size) {
		case FontSize::Title:
			sizeIndicator = "-Title";
			break;
		case FontSize::VeryBig:
			sizeIndicator = "-VeryBig";
			break;
		case FontSize::Big:
			sizeIndicator = "-Big";
			break;
		case FontSize::Medium:
			sizeIndicator = "-Medium";
			break;
		case FontSize::Small:
			sizeIndicator = "-Small";
			break;
		case FontSize::VerySmall:
			sizeIndicator = "-VerySmall";
			break;
	}

	TTF_Font* font;

	//Get Font
	std::unordered_map<std::string, TTF_Font*>::const_iterator iterator = Loader::fonts.find(fontID + sizeIndicator);
	if (iterator == Loader::fonts.end()) {
		//If we don't find the font we return the placeholder
		font=Loader::fonts.at("Placeholder");
	}
	else {
		font=iterator->second;
	}

	//Create texture
	if (text.compare("") == 0) {
		text = " ";
	}
	
	SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.c_str(), color);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(Loader::renderer, textSurface);

	Texture* finalTexture = new Texture(Loader::renderer, textTexture);

	SDL_FreeSurface(textSurface);

	return finalTexture;
}

//Gets a texture based on a string
Texture* Loader::getText(std::string fontID, std::wstring text, SDL_Color color, FontSize size) {
	std::string sizeIndicator;
	switch (size) {
	case FontSize::Title:
		sizeIndicator = "-Title";
		break;
	case FontSize::VeryBig:
		sizeIndicator = "-VeryBig";
		break;
	case FontSize::Big:
		sizeIndicator = "-Big";
		break;
	case FontSize::Medium:
		sizeIndicator = "-Medium";
		break;
	case FontSize::Small:
		sizeIndicator = "-Small";
		break;
	case FontSize::VerySmall:
		sizeIndicator = "-VerySmall";
		break;
	}
	TTF_Font* font;

	//Get Font
	std::unordered_map<std::string, TTF_Font*>::const_iterator iterator = Loader::fonts.find(fontID + sizeIndicator);
	if (iterator == Loader::fonts.end()) {
		//If we don't find the font we return the placeholder
		font = Loader::fonts.at("Placeholder");
	}
	else {
		font = iterator->second;
	}

	//Create texture
	if (text.compare(L"") == 0) {
		text = L" ";
	}

	_bstr_t b(text.c_str());

	SDL_Surface* textSurface = TTF_RenderText_Blended(font, b, color);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(Loader::renderer, textSurface);

	Texture* finalTexture = new Texture(Loader::renderer, textTexture);

	SDL_FreeSurface(textSurface);

	return finalTexture;
}


Texture* Loader::getText(std::string fontID, std::string text, SDL_Color color, FontSize size, int maxWidth) {
	std::string sizeIndicator;
	switch (size) {
	case FontSize::Title:
		sizeIndicator = "-Title";
		break;
	case FontSize::VeryBig:
		sizeIndicator = "-VeryBig";
		break;
	case FontSize::Big:
		sizeIndicator = "-Big";
		break;
	case FontSize::Medium:
		sizeIndicator = "-Medium";
		break;
	case FontSize::Small:
		sizeIndicator = "-Small";
		break;
	case FontSize::VerySmall:
		sizeIndicator = "-VerySmall";
		break;
	}
	TTF_Font* font;

	//Get Font
	std::unordered_map<std::string, TTF_Font*>::const_iterator iterator = Loader::fonts.find(fontID + sizeIndicator);
	if (iterator == Loader::fonts.end()) {
		//If we don't find the font we return the placeholder
		font = Loader::fonts.at("Placeholder");
	}
	else {
		font = iterator->second;
	}

	//Create texture
	if (text.compare("") == 0) {
		text = " ";
	}

	SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(font, text.c_str(), color, maxWidth);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(Loader::renderer, textSurface);

	Texture* finalTexture = new Texture(Loader::renderer, textTexture);

	SDL_FreeSurface(textSurface);

	return finalTexture;
}


Texture* Loader::getText(std::string fontID, std::wstring text, SDL_Color color, FontSize size, int maxWidth) {
	std::string sizeIndicator;
	switch (size) {
	case FontSize::Title:
		sizeIndicator = "-Title";
		break;
	case FontSize::VeryBig:
		sizeIndicator = "-VeryBig";
		break;
	case FontSize::Big:
		sizeIndicator = "-Big";
		break;
	case FontSize::Medium:
		sizeIndicator = "-Medium";
		break;
	case FontSize::Small:
		sizeIndicator = "-Small";
		break;
	case FontSize::VerySmall:
		sizeIndicator = "-VerySmall";
		break;
	}
	TTF_Font* font;

	//Get Font
	std::unordered_map<std::string, TTF_Font*>::const_iterator iterator = Loader::fonts.find(fontID + sizeIndicator);
	if (iterator == Loader::fonts.end()) {
		//If we don't find the font we return the placeholder
		font = Loader::fonts.at("Placeholder");
	}
	else {
		font = iterator->second;
	}

	//Create texture
	if (text.compare(L"") == 0) {
		text = L" ";
	}

	_bstr_t b(text.c_str());

	SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(font, b, color, maxWidth);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(Loader::renderer, textSurface);

	Texture* finalTexture = new Texture(Loader::renderer, textTexture);

	SDL_FreeSurface(textSurface);

	return finalTexture;
}

//Gets a texture based on a string
Texture* Loader::getUnderlineText(std::string fontID, std::string text, SDL_Color color, FontSize size) {
	std::string sizeIndicator;
	switch (size) {
	case FontSize::Title:
		sizeIndicator = "-Title";
		break;
	case FontSize::VeryBig:
		sizeIndicator = "-VeryBig";
		break;
	case FontSize::Big:
		sizeIndicator = "-Big";
		break;
	case FontSize::Medium:
		sizeIndicator = "-Medium";
		break;
	case FontSize::Small:
		sizeIndicator = "-Small";
		break;
	case FontSize::VerySmall:
		sizeIndicator = "-VerySmall";
		break;
	}
	TTF_Font* font;

	//Get Font
	std::unordered_map<std::string, TTF_Font*>::const_iterator iterator = Loader::fonts.find(fontID + sizeIndicator);
	if (iterator == Loader::fonts.end()) {
		//If we don't find the font we return the placeholder
		font = Loader::fonts.at("Placeholder");
	}
	else {
		font = iterator->second;
	}

	//Create texture
	if (text.compare("") == 0) {
		text = " ";
	}

	TTF_SetFontStyle(font, TTF_STYLE_UNDERLINE);

	SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.c_str(), color);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(Loader::renderer, textSurface);

	Texture* finalTexture = new Texture(Loader::renderer, textTexture);

	TTF_SetFontStyle(font, TTF_STYLE_NORMAL);
	SDL_FreeSurface(textSurface);

	return finalTexture;
}

Texture* Loader::getUnderlineText(std::string fontID, std::wstring text, SDL_Color color, FontSize size) {
	std::string sizeIndicator;
	switch (size) {
	case FontSize::Title:
		sizeIndicator = "-Title";
		break;
	case FontSize::VeryBig:
		sizeIndicator = "-VeryBig";
		break;
	case FontSize::Big:
		sizeIndicator = "-Big";
		break;
	case FontSize::Medium:
		sizeIndicator = "-Medium";
		break;
	case FontSize::Small:
		sizeIndicator = "-Small";
		break;
	case FontSize::VerySmall:
		sizeIndicator = "-VerySmall";
		break;
	}
	TTF_Font* font;

	//Get Font
	std::unordered_map<std::string, TTF_Font*>::const_iterator iterator = Loader::fonts.find(fontID + sizeIndicator);
	if (iterator == Loader::fonts.end()) {
		//If we don't find the font we return the placeholder
		font = Loader::fonts.at("Placeholder");
	}
	else {
		font = iterator->second;
	}

	//Create texture
	if (text.compare(L"") == 0) {
		text = L" ";
	}

	_bstr_t b(text.c_str());

	TTF_SetFontStyle(font, TTF_STYLE_UNDERLINE);

	SDL_Surface* textSurface = TTF_RenderText_Blended(font, b, color);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(Loader::renderer, textSurface);

	Texture* finalTexture = new Texture(Loader::renderer, textTexture);

	TTF_SetFontStyle(font, TTF_STYLE_NORMAL);
	SDL_FreeSurface(textSurface);

	return finalTexture;
}

Texture* Loader::getUnderlineText(std::string fontID, std::string text, SDL_Color color, FontSize size, int maxWidth) {
	std::string sizeIndicator;
	switch (size) {
	case FontSize::Title:
		sizeIndicator = "-Title";
		break;
	case FontSize::VeryBig:
		sizeIndicator = "-VeryBig";
		break;
	case FontSize::Big:
		sizeIndicator = "-Big";
		break;
	case FontSize::Medium:
		sizeIndicator = "-Medium";
		break;
	case FontSize::Small:
		sizeIndicator = "-Small";
		break;
	case FontSize::VerySmall:
		sizeIndicator = "-VerySmall";
		break;
	}
	TTF_Font* font;

	//Get Font
	std::unordered_map<std::string, TTF_Font*>::const_iterator iterator = Loader::fonts.find(fontID + sizeIndicator);
	if (iterator == Loader::fonts.end()) {
		//If we don't find the font we return the placeholder
		font = Loader::fonts.at("Placeholder");
	}
	else {
		font = iterator->second;
	}

	//Create texture
	if (text.compare("") == 0) {
		text = " ";
	}

	TTF_SetFontStyle(font, TTF_STYLE_UNDERLINE);

	SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(font, text.c_str(), color, maxWidth);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(Loader::renderer, textSurface);

	Texture* finalTexture = new Texture(Loader::renderer, textTexture);

	TTF_SetFontStyle(font, TTF_STYLE_NORMAL);
	SDL_FreeSurface(textSurface);

	return finalTexture;
}


Texture* Loader::getUnderlineText(std::string fontID, std::wstring text, SDL_Color color, FontSize size, int maxWidth) {
	std::string sizeIndicator;
	switch (size) {
	case FontSize::Title:
		sizeIndicator = "-Title";
		break;
	case FontSize::VeryBig:
		sizeIndicator = "-VeryBig";
		break;
	case FontSize::Big:
		sizeIndicator = "-Big";
		break;
	case FontSize::Medium:
		sizeIndicator = "-Medium";
		break;
	case FontSize::Small:
		sizeIndicator = "-Small";
		break;
	case FontSize::VerySmall:
		sizeIndicator = "-VerySmall";
		break;
	}
	TTF_Font* font;

	//Get Font
	std::unordered_map<std::string, TTF_Font*>::const_iterator iterator = Loader::fonts.find(fontID + sizeIndicator);
	if (iterator == Loader::fonts.end()) {
		//If we don't find the font we return the placeholder
		font = Loader::fonts.at("Placeholder");
	}
	else {
		font = iterator->second;
	}

	//Create texture
	if (text.compare(L"") == 0) {
		text = L" ";
	}

	_bstr_t b(text.c_str());

	TTF_SetFontStyle(font, TTF_STYLE_UNDERLINE);

	SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(font, b, color, maxWidth);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(Loader::renderer, textSurface);

	Texture* finalTexture = new Texture(Loader::renderer, textTexture);

	TTF_SetFontStyle(font, TTF_STYLE_NORMAL);
	SDL_FreeSurface(textSurface);

	return finalTexture;
}