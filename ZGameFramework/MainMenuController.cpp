#include <fstream>
#include <iostream>

#include "Config.h"
#include "Input.h"
#include "Loader.h"
#include "MainController.h"
#include "MainMenuController.h"
#include "Position.h"
#include "Utils.h"

//Constructor
MainMenuController::MainMenuController(
	MainController* mainController, 
	SDL_Renderer* renderer) :
		IController(
			mainController, 
			renderer) {

	//We load the textures
	Loader::loadFiles("Resources");

	//We get the textures
	this->borderTexture = Loader::getTexture("TitleBorder");
	this->selectorTexture = Loader::getTexture("TitleSelector");

	//We define the color of the options
	SDL_Color textColor;
	textColor.r = 0;
	textColor.b = 255;
	textColor.g = 0;
	textColor.a = 255;

	//We define the color of the title
	SDL_Color titleTextColor;
	titleTextColor.r = 255;
	titleTextColor.b = 0;
	titleTextColor.g = 0;
	titleTextColor.a = 255;

	//We open the file
	std::wifstream file;
	file.open("Resources/Text/" + Config::getConfig("Language") + "/MainMenuText.txt");

	//String where the different lines of the file will be stored
	std::wstring line;

	//We get the name of the game
	getline(file, line);
	this->titleTexture = Loader::getText("ComputerFont", line, titleTextColor, FontSize::Title);

	//Start game line
	getline(file, line);
	this->startGameTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::VeryBig));
	this->startGameTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Big));
	this->startGameTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Medium));

	//Options line
	getline(file, line);
	this->optionsTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::VeryBig));
	this->optionsTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Big));
	this->optionsTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Medium));

	//Exit line
	getline(file, line);
	this->exitTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::VeryBig));
	this->exitTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Big));
	this->exitTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Medium));

	//We close the file
	file.close();

	//We get the sounds
	this->changeSelectionSound = Loader::getSound("ChangeSelectionBeep");
	this->selectionSound = Loader::getSound("SelectionBeep");

	//We get the main theme
	//this->mainMenuTheme = Loader::getSong("MainMenuTheme");
	//Utils::startSong(this->mainMenuTheme);
}

//Destroyer
MainMenuController::~MainMenuController() {
	delete(this->titleTexture);

	for (Texture* texture : startGameTexture) {
		delete(texture);
	}

	for (Texture* texture : optionsTexture) {
		delete(texture);
	}

	for (Texture* texture : exitTexture) {
		delete(texture);
	}
}

//Function to manage the input
void MainMenuController::manageInput() {

	//We check if down is pressed
	if (Input::inputPressed(InputType::Down)) {
		this->selectedOption++;
		Utils::playSound(this->changeSelectionSound);

		if (this->selectedOption > 2) {
			this->selectedOption = 0;
		}
	}

	//We check if up is pressed
	if (Input::inputPressed(InputType::Up)) {
		this->selectedOption--;
		Utils::playSound(this->changeSelectionSound);

		if (this->selectedOption < 0) {
			this->selectedOption = 2;
		}
	}

	//We check if the mouse has moved
	if (Input::mouseMoved()) {
		//If it has, we must select the option over which the mouse is hovering

		//We get the position of the mouse inside the scroll
		Position titleScreenPosition = Utils::getCenteredPosition(Position(0, 0), Utils::getScreenWidth(), Utils::getScreenHeight(), 1000, 700);
		Position mousePosition = Input::getMousePosition();
		Position mouseScrollPosition = Position(mousePosition.x - titleScreenPosition.x, mousePosition.y - titleScreenPosition.y);

		//We check if it's generally over the options area
		if (mouseScrollPosition.x >= 250 && mouseScrollPosition.x < 750) {
			//We check over which area it is
			if (mouseScrollPosition.y >= 250 && mouseScrollPosition.y < 350) {
				if (this->selectedOption != 0) {
					Utils::playSound(this->changeSelectionSound);
				}
				this->selectedOption = 0;
			}
			else if (mouseScrollPosition.y >= 350 && mouseScrollPosition.y < 450) {
				if (this->selectedOption != 1) {
					Utils::playSound(this->changeSelectionSound);
				}
				this->selectedOption = 1;
			}
			else if (mouseScrollPosition.y >= 450 && mouseScrollPosition.y < 550) {
				if (this->selectedOption != 2) {
					Utils::playSound(this->changeSelectionSound);
				}
				this->selectedOption = 2;
			}
		}
	}

	//We check if the input is pressed
	if (Input::inputPressed(InputType::Selection) || Input::mouseLeftInputPressed()) {
		Utils::playSound(this->changeSelectionSound);

		switch (this->selectedOption) {
		case 0:
			this->mainController->openNewGame();
			break;
		case 1:
			this->mainController->openOptions();
			break;
		case 2:
			this->mainController->endGame();
			break;
		}
	}
}

//Function to draw a frame
void MainMenuController::drawframe() {
	//We get the screen position of the title screen
	Position titleScreenPosition = Utils::getCenteredPosition(Position(0, 0), Utils::getScreenWidth(), Utils::getScreenHeight(), 1000, 700);
	this->borderTexture->draw(titleScreenPosition);

	//We draw the title of the game
	Utils::drawCenteredTextureAt(Position(titleScreenPosition.x + 50, titleScreenPosition.y), 900, 300, this->titleTexture);

	//We draw the different options
	Utils::drawFirstFittingTextureCenteredAt(Position(titleScreenPosition.x + 250, titleScreenPosition.y + 250), 500, 100, this->startGameTexture);
	Utils::drawFirstFittingTextureCenteredAt(Position(titleScreenPosition.x + 250, titleScreenPosition.y + 350), 500, 100, this->optionsTexture);
	Utils::drawFirstFittingTextureCenteredAt(Position(titleScreenPosition.x + 250, titleScreenPosition.y + 450), 500, 100, this->exitTexture);

	//We draw the selector
	this->selectorTexture->draw(Position(titleScreenPosition.x + 250, titleScreenPosition.y + 250 + this->selectedOption * 100));
}

//changes the language of the main menu
void MainMenuController::changeLanguage(std::string newLanguageCode) {
	for (Texture* texture : this->startGameTexture) {
		delete(texture);
	}
	this->startGameTexture.clear();

	for (Texture* texture : this->optionsTexture) {
		delete(texture);
	}
	this->optionsTexture.clear();

	for (Texture* texture : this->exitTexture) {
		delete(texture);
	}
	this->exitTexture.clear();

	//We define the color of the options
	SDL_Color textColor;
	textColor.r = 0;
	textColor.b = 255;
	textColor.g = 0;
	textColor.a = 255;

	//We open the file
	std::wifstream file;
	file.open("Resources/Text/" + newLanguageCode + "/MainMenuText.txt");

	//String where the different lines of the file will be stored
	std::wstring line;

	//We get the name of the game
	getline(file, line);

	//Start game line
	getline(file, line);
	this->startGameTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::VeryBig));
	this->startGameTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Big));
	this->startGameTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Medium));

	//Options line
	getline(file, line);
	this->optionsTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::VeryBig));
	this->optionsTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Big));
	this->optionsTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Medium));

	//Exit line
	getline(file, line);
	this->exitTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::VeryBig));
	this->exitTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Big));
	this->exitTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Medium));

	//We close the file
	file.close();
}