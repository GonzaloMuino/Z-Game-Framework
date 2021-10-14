#pragma once

#include <string>
#include <vector>

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "IController.h"
#include "Texture.h"

class MainController;

//Controller of the main menu of the game
class MainMenuController : IController{

	private:

		//Selected option
		int selectedOption = 0;

		//Border Texture
		Texture* borderTexture;

		//Selector texture
		Texture* selectorTexture;

		//Title Texture
		Texture* titleTexture;

		//Continue Texture
		std::vector<Texture*> startGameTexture;

		//Options Texture
		std::vector<Texture*> optionsTexture;

		//Options Texture
		std::vector<Texture*> exitTexture;

		//Selected option change sound
		Mix_Chunk* changeSelectionSound;
		Mix_Chunk* selectionSound;

		//Main Menu theme
		Mix_Music* mainMenuTheme;

	public:
		//Constructor
		MainMenuController(MainController* mainController, SDL_Renderer* renderer);

		//Destroyer
		~MainMenuController();

		virtual ControllerType getControllerType() {
			return ControllerType::MainMenuController;
		}

		//Function to manage the input
		void manageInput();

		//Function to draw a frame
		void drawframe();

		//changes the language of the main menu
		void changeLanguage(std::string newLanguageCode);
};  