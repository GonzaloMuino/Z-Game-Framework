#pragma once

#include <string>
#include <vector>

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "ControllerType.h"
#include "Position.h"

class IController;
class MainMenuController;
class OptionsController;
class Window;

//Possible states of the main controller
enum class MainControllerState {
	MainMenu,
	Options
};

//Main controller of the game. Handles which controller is active
class MainController {
private:

	//Indicates the current state of the game. Used to select the controller that must draw the frame, handle the input, etc.
	MainControllerState currentState;

	//Indicates whether or not the game has ended or if we must continue
	bool continueGame = true;

	//Renderer
	SDL_Renderer* renderer;

	//Different controllers of the game. Each one is used for one of the states

		//Controller of the starting main menu of the game
		MainMenuController* mainMenuController;

		//Controller of options
		OptionsController* optionsController;

	//Indicates a controller that needs to be free'd
	IController* controllerToBeFreed;

public:
	//Constructor
	MainController(Window* window);

	//Starts the game loop
	void startGameLoop();

	//Ends the game
	void endGame();

	//Functions used to open different controllers

		//Opens the main menu
		void openMainMenu();

		//Opens the options
		void openOptions();

		//Starts a new game
		void openNewGame();

	//Functions to reset and render the present information

		//Draws the current information on the render
		void renderPresent();

		//Resets the render so that we can draw a new image
		void resetRenderer();

	//Assigns a controller as to be free'd
	void freeController(IController* controllerToBeFreed);

	//changes the language of the main menu
	void changeMainMenuLanguage(std::string newLanguageCode);
};