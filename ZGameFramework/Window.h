#pragma once

#include <SDL.h>

class MainController;

//Class that represents the window the game is executed in.
//Is the one that starts the program. main() is contained in its .cpp
class Window {

	private:
		//SDL classes used to show the game to the player
		SDL_Window* window;
		SDL_Renderer* renderer;

		//Main controller of the game. Is the one in charge to controll the flow of the game
		MainController* mainController;

	public:
		//Constructor
		Window();

		//Getters
		SDL_Renderer* getRenderer() { return this->renderer; }
		SDL_Window* getWindow() { return this->window; }

		//Starts the game loop
		void startGameLoop();
};