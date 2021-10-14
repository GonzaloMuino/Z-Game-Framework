#pragma once

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>

#include "IController.h"
#include "Input.h"
#include "Texture.h"

class Config;
class Loader;
class MainController;
class Window;

enum class OptionControllerState {
	NoOption,
	ConfirmChanges,
	GraphicsOptions,
	SoundOptions,
	OtherOptions
};

//Controller of options
class OptionsController : IController {
private:
	//Current state
	OptionControllerState currentState;

	//Currently selected Row
	int selectedRow;

	//Textures (Non Text)

	//Background texture
	Texture* backgroundTexture;

	//Selector texture
	Texture* selectorTexture;

	//Graphics separator
	Texture* graphicsOptionsSeparator;

	//Graphics Selector
	Texture* graphicsOptionsSelector;

	//Sound separator
	Texture* soundOptionsSeparator;

	//Sound Selector
	Texture* soundOptionsSelector;

	//Sound Selector
	Texture* soundOptionsSubSelector;

	//Other separator
	Texture* otherOptionsSeparator;

	//Other Selector
	Texture* otherOptionsSelector;

	//Other Selector
	Texture* otherOptionsDefaultSelector;

	//Confirm Selector
	Texture* confirmOptionsSelector;

	//Confirm Selector
	Texture* boolOptionsSelector;

	//Textures (With Text)
	std::vector<Texture*> optionsTexture;
	std::vector<Texture*> graphicsTexture;
	std::vector<Texture*> soundTexture;
	std::vector<Texture*> otherTexture;
	std::vector<Texture*> exitTexture;
	std::vector<Texture*> graphicsUnderlinedTexture;
	std::vector<Texture*> fullscreenTexture;
	std::vector<Texture*> screenWidthTexture;
	std::vector<Texture*> screenHeightTexture;
	std::vector<Texture*> minWidthTexture;
	std::vector<Texture*> minHeightTexture;
	std::vector<Texture*> soundUnderlinedTexture;
	std::vector<Texture*> musicTexture;
	std::vector<Texture*> soundsTexture;
	std::vector<Texture*> otherUnderlinedTexture;
	std::vector<Texture*> languageTexture;
	std::vector<Texture*> defaultTexture;
	std::vector<Texture*> confirmChangesTexture;
	std::vector<Texture*> yesTexture;
	std::vector<Texture*> noTexture;
	std::vector<Texture*> restartTexture;

	//Soundeffect

		//Selected option change sound
		Mix_Chunk* changeSelectionSound;
		Mix_Chunk* selectionSound;

	//Functions to draw each possible state of this controller

		//Draws the scroll when no option was selected
		void drawNoOptions(Position scrollPosition);

		//Draws the scroll when graphics was selected
		void drawGraphicsOptions(Position scrollPosition);

		//Draws the scroll when sound was selected
		void drawSoundOptions(Position scrollPosition);

		//Draws the scroll when other was selected
		void drawOtherOptions(Position scrollPosition);

		//Draws the scroll when confirming changes
		void drawConfirmOptions(Position scrollPosition);

	//Values that can be changed in the options and their corresponding textures

		//Fullscreen
		bool fullscreenValue;

	//Has no asigned texture

	//Resolution Width
	std::string resolutionWidthValue;
	std::vector<Texture*> resolutionWidthValueTexture;

	//Resolution Width
	std::string resolutionHeightValue;
	std::vector<Texture*> resolutionHeightValueTexture;

	//Music volume
	int musicVolume;

	//Sound volume
	int soundVolume;

	//Grid Input
	bool gridValue;

	//Field Animation Input
	bool fieldAnimationValue;

	//Language has a special selection process. We save the selected position of the language vectors
	int languageVectorPosition;

	std::vector<Texture*> languagesTextures;
	std::vector<std::string> languageCodes;

	//This variable indicates if a text is beeing input or not
	bool textBeingInput;

	//This variable indicates if the language is beeing changed
	bool languageBeeingChanged;

	//This variable indicates if the language is beeing changed
	bool volumeBeeingChanged;

	//Saves current changes
	void saveConfiguration();

	//Changes the Language
	void changeLanguage(std::string languageCode);

	//Saves current changes
	void defaultConfiguration();

public:
	//Constructor
	OptionsController(MainController* mainController, SDL_Renderer* renderer);

	//Destroyer
	~OptionsController();

	virtual ControllerType getControllerType() {
		return ControllerType::OptionsController;
	}

	//Function to manage the input
	void manageInput();

	//Function to draw a frame
	void drawframe();
};