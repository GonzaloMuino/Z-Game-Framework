#pragma once

#include <queue>
#include <string>
#include <vector>

#include <SDL_mixer.h>
#include <SDL_net.h>

#include "Position.h"
#include "Texture.h"

//Functions used in various points of the program that have a general usage
class Utils {
	public:
		//Gets the logical screen width
		static int getScreenWidth() {
			return 1920;
		}

		//Gets the logical screen height
		static int getScreenHeight() {
			return 1080;
		}

		//Function to determine if the string pased is a number.
		static bool isNumber(std::string string) {
			return !string.empty() && std::all_of(string.begin(), string.end(), ::isdigit);
		}

		//Function to split a string
		static std::vector<std::string> splitString(std::string line, std::string separator) {
			std::vector<std::string> output;
			std::size_t current, previous = 0;

			//We find the first separator
			current = line.find(separator);

			//We search for segments while we aren't at the final position
			while (current != std::string::npos) {
				//We get the next segment of the string
				output.push_back(line.substr(previous, current - previous));
				//We get the starting position of the next segment
				previous = current + 1;
				//We find the next separator
				current = line.find(separator, previous);
			}
		
			//We have to get the final segment
			output.push_back(line.substr(previous, current - previous));

			return output;
		}

		//Function to split a wstring
		static std::vector<std::wstring> splitString(std::wstring line, std::wstring separator) {
			std::vector<std::wstring> output;
			std::size_t current, previous = 0;

			//We find the first separator
			current = line.find(separator);

			//We search for segments while we aren't at the final position
			while (current != std::string::npos) {
				//We get the next segment of the string
				output.push_back(line.substr(previous, current - previous));
				//We get the starting position of the next segment
				previous = current + 1;
				//We find the next separator
				current = line.find(separator, previous);
			}

			//We have to get the final segment
			output.push_back(line.substr(previous, current - previous));

			return output;
		}

		//Function to return the centered screen position for a given texture on a given background.
		static Position getCenteredPosition(Position backgroundScreenPosition, int backgroundWidth, int backgroundHeight, int textureWidth, int textureHeight) {
			int xDisplacement = (backgroundWidth - textureWidth) / 2;
			int yDisplacement = (backgroundHeight - textureHeight) / 2;

			return Position(backgroundScreenPosition.x + xDisplacement, backgroundScreenPosition.y + yDisplacement);
		}

		//Gives a randome number between lowest and highest (BOTH INCLUDED)
		static int randomNumber(int lowest, int highest) {
			return lowest + (std::rand() % (highest - lowest + 1));
		}

		//Draws the given texture centered in the given rectangle
		//The given rectangle is given by the upperLeftPosition and its width and height
		static void drawCenteredTextureAt(Position backgroundScreenPosition, int backgroundWidth, int backgroundHeight, Texture* texture) {
			texture->draw(Utils::getCenteredPosition(backgroundScreenPosition, backgroundWidth, backgroundHeight, texture->width, texture->height));
		}

		//Draws the first Texture from the given that fits centered in the given rectangle
		//The given rectangle is given by the upperLeftPosition and its width and height
		static void drawFirstFittingTextureCenteredAt(Position backgroundScreenPosition, int backgroundWidth, int backgroundHeight, std::vector<Texture*> textures) {
			bool found = false;
			int position = -1;

			for (int i = 0; i < textures.size() && !found; i++) {
				Texture* texture = textures.at(i);
				if (texture->width <= backgroundWidth && texture->height <= backgroundHeight) {
					found = true;
					position = i;
				}
			}

			if (found) {
				drawCenteredTextureAt(backgroundScreenPosition, backgroundWidth, backgroundHeight, textures.at(position));
			}
			else {
				//If none fit, we draw the last [Expected to be the smallest]
				drawCenteredTextureAt(backgroundScreenPosition, backgroundWidth, backgroundHeight, textures.at(textures.size()-1));
			}
		}

		//Function to start a song
		static void startSong(Mix_Music* song) {
			if (Mix_PlayingMusic() == 0) {
				Mix_HaltMusic();
			}
			Mix_PlayMusic(song, -1);
		}

		//Function to start a song that repeats repetitions times
		static void startSong(Mix_Music* song, int repetitions) {
			if (Mix_PlayingMusic() == 0) {
				Mix_HaltMusic();
			}
			Mix_PlayMusic(song, repetitions);
		}

		//Function to stop the current song
		static void stopSong() {
			Mix_HaltMusic();
		}

		//Function to play a sound
		static void playSound(Mix_Chunk* sound) {
			Mix_PlayChannel(-1, sound, 0);
		}

		//Function to stop any sounds
		static void stopSound() {
			Mix_HaltChannel(-1);
		}

		//Function to show the mouse
		static void showMouse() {
			SDL_ShowCursor(SDL_ENABLE);
		}

		//Function to hide the mouse
		static void hideMouse() {
			SDL_ShowCursor(SDL_DISABLE);
		}
};