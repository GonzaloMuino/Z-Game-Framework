#include "Config.h"
#include "IController.h"
#include "Loader.h"
#include "MainController.h"
#include "Window.h"

//Constructor
IController::IController(MainController* mainController, SDL_Renderer* renderer) {
	//Direct assignments
	this->mainController = mainController;
	this->renderer = renderer;
}

//Function to manage the input
void IController::manageInput() {

}

//Function to advance the game state
void IController::advanceGameState() {

}

//Function to draw a frame
void IController::drawframe() {

}
	
//Function to draw a line
void IController::drawLine(Position position1, Position position2, SDL_Color color) {
	SDL_SetRenderDrawColor(this->renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawLine(this->renderer, position1.x, position1.y, position2.x, position2.y);
	SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
}