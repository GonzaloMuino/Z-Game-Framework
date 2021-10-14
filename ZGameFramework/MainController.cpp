#include "MainController.h"

#include "Config.h"
#include "IController.h"
#include "Input.h"
#include "Loader.h"
#include "MainMenuController.h"
#include "OptionsController.h"
#include "Window.h"

//Used to force 60Hz
#define TICK_INTERVAL 17

//Used to force 60hz
static Uint32 next_time;

//Used to force 60hz
Uint32 time_left(void){
	Uint32 now;

	now = SDL_GetTicks();
	if (next_time <= now) {
		return 0;
	}else{
		return next_time - now;
	}
}

//Constructor
MainController::MainController(Window* window) {
	//Direct assignment
	this->renderer = window->getRenderer();

	//We initiate the loader 
	Loader::initLoader(this->renderer);

	//We indicate that the game hasn't ended
	this->continueGame = true;

	//The starting state is always the main menu. We indicate the state
	this->currentState = MainControllerState::MainMenu;

	//We initiate the input controller
	Input::initInput();

	//We create de main menu controller
	this->mainMenuController = new MainMenuController(this, this->renderer);

	//At the beginning there is no controller to be free'd
	this->controllerToBeFreed = nullptr;

	//We set the volume of the music and the sound effects
	Mix_VolumeMusic(std::atoi(Config::getConfig("MusicVolume").c_str()));
	Mix_Volume(-1, std::atoi(Config::getConfig("SoundVolume").c_str()));
	
	//We set the mouse
	Loader::setCursor("MousePointer");
}

//Controlls the game loop
void MainController::startGameLoop() {
	IController* activeController = nullptr;
	next_time = SDL_GetTicks() + TICK_INTERVAL;

	while (this->continueGame) {
		//We check if we have to free any controller
		if (this->controllerToBeFreed != nullptr) {
			switch (this->controllerToBeFreed->getControllerType()) {
				case ControllerType::MainMenuController:
					delete((MainMenuController*)this->controllerToBeFreed);
					break;
				case ControllerType::OptionsController:
					delete((OptionsController*)this->controllerToBeFreed);
					break;
			}
			this->controllerToBeFreed = nullptr;
		}

		//We get the active controller
		switch (this->currentState) {
			case MainControllerState::MainMenu:
				activeController = (IController*)this->mainMenuController;
				break;
			case MainControllerState::Options:
				activeController = (IController*)this->optionsController;
				break;
		}

		//We update the input and manage it
		Input::updateInput();
		activeController->manageInput();

		//We advance the state of the game
		activeController->advanceGameState();
		
		//We clear the renderer
		this->resetRenderer();
		
		//We draw this frame
		activeController->drawframe();

		//We render the information
		this->renderPresent();
	}
}

//Ends the game
void MainController::endGame() {
	this->continueGame = false;
}

//Opens the main menu
void MainController::openMainMenu() {
	//We change state
	this->currentState = MainControllerState::MainMenu;
}

//Opens the options
void MainController::openOptions() {
	this->currentState = MainControllerState::Options;
	this->optionsController = new OptionsController(this, this->renderer);
}

//Opens the options
void MainController::openNewGame() {

}

//Draws the current information on the render
void MainController::renderPresent() {
	//We render what the active controller rendered
	SDL_RenderPresent(this->renderer);

	//We wait to force the 60hz
	SDL_Delay(time_left());
	next_time += TICK_INTERVAL;
}

//Resets the render so that we can draw a new image
void MainController::resetRenderer() {
	//We clear the renderer
	SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
	SDL_RenderClear(this->renderer);
}

//Assigns a controller as to be free'd
void MainController::freeController(IController* controllerToBeFreed) {
	this->controllerToBeFreed = controllerToBeFreed;
}

//changes the language of the main menu
void MainController::changeMainMenuLanguage(std::string newLanguageCode) {
	this->mainMenuController->changeLanguage(newLanguageCode);
}