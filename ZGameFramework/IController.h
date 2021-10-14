#pragma once

#include <string>

#include <SDL.h>

#include "ControllerType.h"
#include "Position.h"
#include "Texture.h"

class MainController;

//Base class of the controllers of the game
class IController {
protected:
	//Main controller
	MainController* mainController;

	//Renderer. Used in drawFrame().
	SDL_Renderer* renderer;

public:
	//Constructor
	IController(MainController* mainController, SDL_Renderer* renderer);

	//Function to manage the input
	virtual void manageInput();

	//Function to advance the game state
	virtual void advanceGameState();

	//Function to draw a frame
	virtual void drawframe();

	//Gives the controller type
	virtual ControllerType getControllerType() {
		return ControllerType::IController;
	}

	//Function to draw a line
	void drawLine(Position position1, Position position2, SDL_Color color);
};