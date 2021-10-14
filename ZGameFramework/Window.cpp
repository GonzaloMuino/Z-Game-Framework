#include <SDL.h>
#include <SDL_net.h>
#include <time.h>
#include <locale>
#include <codecvt>

#include "Config.h"
#include "MainController.h"
#include "Window.h"

//Constructor
Window::Window() {
	//We Load the configuration
	Config::loadConfigs();

	//We create the Window

	//First we check if it has to be fullscreen or not
	int fullScreen = std::atoi(Config::getConfig("FullScreen").c_str());

	//We have to get the width and height from the configuration
	int resolutionWidth = std::atoi(Config::getConfig("ResolutionWidth").c_str());
	int resolutionHeight = std::atoi(Config::getConfig("ResolutionHeight").c_str());

	if (fullScreen == 0) {
		//Not fullscreen. 
		//We create the window
		this->window = SDL_CreateWindow("Project Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, resolutionWidth, resolutionHeight, NULL);
	}else{
		if (resolutionWidth == -1) {
			//If ResolutionWidth is -1, that means it's the first time we execute the game. We create a fullscreen with the resolution of the screen and
			//then save that resolution
			this->window = SDL_CreateWindow("Project Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, NULL, NULL, SDL_WINDOW_FULLSCREEN_DESKTOP);
			SDL_GetWindowSize(this->window, &resolutionWidth, &resolutionHeight);

			Config::setConfig("ResolutionWidth", std::to_string(resolutionWidth));
			Config::setConfig("ResolutionHeight", std::to_string(resolutionHeight));

			Config::saveConfig();
		}
		else {
			//We create the fullscreen window
			this->window = SDL_CreateWindow("Project Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, resolutionWidth, resolutionHeight, SDL_WINDOW_FULLSCREEN);
		}
	}

	//We create the renderer and set the background to black
	this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);

	//We capture the cursor so it doesn't leave the screen
	SDL_SetWindowGrab(this->window, SDL_TRUE);

	//We set render logical size so we can always assume 1920x1080 screen
	SDL_RenderSetLogicalSize(this->renderer, 1920, 1080);

	//We Create main controller of the game
	this->mainController = new MainController(this);
}

//Starts the game loop
void Window::startGameLoop() {
	//We simplye send the function to the main controller
	this->mainController->startGameLoop();
}

//Entry point of program
int main(int argc, char**argv) {

	//UTF-8 to make sure we have most of the symbols
	std::locale::global(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));

	//Initiate all of SDL [Basic SDL, Net, TTF and we open the audio channel]
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0 || SDLNet_Init() == -1 || TTF_Init() < 0 || Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return 1;
	}

	//We start the text input so it works always when accepting text input. IT does not interfiere with the standard input
	SDL_StartTextInput();

	//We seed the random generator so it's different every time
	srand(time(NULL));

	//Create window and start game
	Window* window = new Window();
	window->startGameLoop();

	//Close everything
	SDL_Quit();
	return 0;
}