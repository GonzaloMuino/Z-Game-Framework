#include <iostream>
#include <fstream>

#include "Config.h"
#include "Input.h"
#include "Loader.h"
#include "MainController.h"
#include "OptionsController.h"
#include "Utils.h"

//Draws the scroll when no option was selected
void OptionsController::drawNoOptions(Position scrollPosition) {
	//We need to draw the options title and the 4 options types as well as the exit option

	//Options
	Utils::drawFirstFittingTextureCenteredAt(Position(scrollPosition.x + 310, scrollPosition.y + 26), 380, 90, this->optionsTexture);

	//graphics
	Utils::drawFirstFittingTextureCenteredAt(Position(scrollPosition.x + 310, scrollPosition.y + 136), 380, 90, this->graphicsTexture);

	//sound
	Utils::drawFirstFittingTextureCenteredAt(Position(scrollPosition.x + 310, scrollPosition.y + 246), 380, 90, this->soundTexture);

	//other
	Utils::drawFirstFittingTextureCenteredAt(Position(scrollPosition.x + 310, scrollPosition.y + 356), 380, 90, this->otherTexture);

	//exit
	Utils::drawFirstFittingTextureCenteredAt(Position(scrollPosition.x + 310, scrollPosition.y + 466), 380, 90, this->exitTexture);

	//Now we draw the selector. We get the position based on the selected row
	Position selectorPosition = Position(scrollPosition.x + 300, scrollPosition.y + 136 + this->selectedRow * 110);
	this->selectorTexture->draw(selectorPosition);
}

//Draws the scroll when graphics was selected
void OptionsController::drawGraphicsOptions(Position scrollPosition) {
	//We draw the separator for the graphics options
	this->graphicsOptionsSeparator->draw(scrollPosition);

	//Graphics Options Title
	Utils::drawFirstFittingTextureCenteredAt(Position(scrollPosition.x + 300, scrollPosition.y + 26), 380, 90, this->graphicsUnderlinedTexture);

	//Fullscreen
	Utils::drawFirstFittingTextureCenteredAt(Position(scrollPosition.x + 160, scrollPosition.y + 136), 300, 90, this->fullscreenTexture);

	//Resolution Width
	Utils::drawFirstFittingTextureCenteredAt(Position(scrollPosition.x + 160, scrollPosition.y + 246), 300, 90, this->screenWidthTexture);

	//Resolution Height
	Utils::drawFirstFittingTextureCenteredAt(Position(scrollPosition.x + 160, scrollPosition.y + 356), 300, 90, this->screenHeightTexture);

	//Min Resolution Width
	Utils::drawFirstFittingTextureCenteredAt(Position(scrollPosition.x + 160, scrollPosition.y + 473), 700, 90, this->minWidthTexture);

	//Min Resolution Height
	Utils::drawFirstFittingTextureCenteredAt(Position(scrollPosition.x + 160, scrollPosition.y + 583), 700, 90, this->minHeightTexture);

	//Now we draw the selector. We get the position based on the selected row
	Position graphicsSelectorPosition;
	if (this->textBeingInput) {
		//Text is being input, we draw the selector to the right
		graphicsSelectorPosition = Position(scrollPosition.x + 525, scrollPosition.y + 136 + this->selectedRow * 110);
	}
	else {
		graphicsSelectorPosition = Position(scrollPosition.x + 150, scrollPosition.y + 136 + this->selectedRow * 110);
	}
	this->graphicsOptionsSelector->draw(graphicsSelectorPosition);

	//Now we draw the information

	//Fullscreen Information
	if (this->fullscreenValue) {
		this->boolOptionsSelector->draw(Position(scrollPosition.x + 660, scrollPosition.y + 158));
	}

	//Resolution Width Value
	Utils::drawFirstFittingTextureCenteredAt(Position(scrollPosition.x + 525, scrollPosition.y + 246), 300, 90, this->resolutionWidthValueTexture);

	//Resolution Height Value
	Utils::drawFirstFittingTextureCenteredAt(Position(scrollPosition.x + 525, scrollPosition.y + 356), 300, 90, this->resolutionHeightValueTexture);
}

//Draws the scroll when graphics was selected
void OptionsController::drawSoundOptions(Position scrollPosition) {
	//We draw the separator for the sound options
	this->soundOptionsSeparator->draw(scrollPosition);

	//Sound Options Title
	Utils::drawFirstFittingTextureCenteredAt(Position(scrollPosition.x + 300, scrollPosition.y + 26), 380, 90, this->soundUnderlinedTexture);

	//Music
	Utils::drawFirstFittingTextureCenteredAt(Position(scrollPosition.x + 160, scrollPosition.y + 136), 300, 90, this->musicTexture);

	//Sounds
	Utils::drawFirstFittingTextureCenteredAt(Position(scrollPosition.x + 160, scrollPosition.y + 246), 300, 90, this->soundsTexture);

	//Now we draw the selector. We get the position based on the selected row and wether or not we are currently changing volume
	Position soundSelectorPosition;
	if (this->volumeBeeingChanged) {
		soundSelectorPosition = Position(scrollPosition.x + 525, scrollPosition.y + 136 + this->selectedRow * 110);
	}
	else {
		soundSelectorPosition = Position(scrollPosition.x + 150, scrollPosition.y + 136 + this->selectedRow * 110);
	}
	this->soundOptionsSelector->draw(soundSelectorPosition);

	//Now we draw the volume indicators

	//Music Volume
	switch (this->musicVolume) {
	case 128:
		this->soundOptionsSubSelector->draw(Position(scrollPosition.x + 525, scrollPosition.y + 136));
		break;
	case 100:
		this->soundOptionsSubSelector->draw(Position(scrollPosition.x + 587, scrollPosition.y + 136));
		break;
	case 75:
		this->soundOptionsSubSelector->draw(Position(scrollPosition.x + 649, scrollPosition.y + 136));
		break;
	case 50:
		this->soundOptionsSubSelector->draw(Position(scrollPosition.x + 711, scrollPosition.y + 136));
		break;
	case 25:
		this->soundOptionsSubSelector->draw(Position(scrollPosition.x + 773, scrollPosition.y + 136));
		break;
	case 0:
		this->soundOptionsSubSelector->draw(Position(scrollPosition.x + 835, scrollPosition.y + 136));
		break;
	}

	//Sound Volume
	switch (this->soundVolume) {
	case 128:
		this->soundOptionsSubSelector->draw(Position(scrollPosition.x + 525, scrollPosition.y + 246));
		break;
	case 100:
		this->soundOptionsSubSelector->draw(Position(scrollPosition.x + 587, scrollPosition.y + 246));
		break;
	case 75:
		this->soundOptionsSubSelector->draw(Position(scrollPosition.x + 649, scrollPosition.y + 246));
		break;
	case 50:
		this->soundOptionsSubSelector->draw(Position(scrollPosition.x + 711, scrollPosition.y + 246));
		break;
	case 25:
		this->soundOptionsSubSelector->draw(Position(scrollPosition.x + 773, scrollPosition.y + 246));
		break;
	case 0:
		this->soundOptionsSubSelector->draw(Position(scrollPosition.x + 835, scrollPosition.y + 246));
		break;
	}
}

//Draws the scroll when other was selected
void OptionsController::drawOtherOptions(Position scrollPosition) {
	//We draw the separator for the sound options
	this->otherOptionsSeparator->draw(scrollPosition);

	//Other Options Title
	Utils::drawFirstFittingTextureCenteredAt(Position(scrollPosition.x + 300, scrollPosition.y + 26), 380, 90, this->otherUnderlinedTexture);

	//Language
	Utils::drawFirstFittingTextureCenteredAt(Position(scrollPosition.x + 160, scrollPosition.y + 136), 300, 90, this->languageTexture);

	//Default
	Utils::drawFirstFittingTextureCenteredAt(Position(scrollPosition.x + 160, scrollPosition.y + 246), 680, 90, this->defaultTexture);

	//Now we draw the selector. We get the position based on the selected row
	//In this case it is special
	if (this->selectedRow == 0) {
		if (this->languageBeeingChanged) {
			//Language is beeing changed currently
			Position otherSelectorPosition = Position(scrollPosition.x + 525, scrollPosition.y + 136);
			this->otherOptionsSelector->draw(otherSelectorPosition);
		}
		else {
			Position otherSelectorPosition = Position(scrollPosition.x + 150, scrollPosition.y + 136);
			this->otherOptionsSelector->draw(otherSelectorPosition);
		}
	}
	else if (this->selectedRow == 1) {
		Position otherSelectorPosition = Position(scrollPosition.x + 150, scrollPosition.y + 246);
		this->otherOptionsDefaultSelector->draw(otherSelectorPosition);
	}

	//Grid Information
	if (this->gridValue) {
		this->boolOptionsSelector->draw(Position(scrollPosition.x + 660, scrollPosition.y + 268));
	}

	//Field Animation Information
	if (this->fieldAnimationValue) {
		this->boolOptionsSelector->draw(Position(scrollPosition.x + 660, scrollPosition.y + 378));
	}

	//We draw the language information
	Texture* languageValueTextureToDraw = this->languagesTextures.at(this->languageVectorPosition);
	Position languageValuePosition = Position(scrollPosition.x + 525, scrollPosition.y + 136);
	Utils::drawCenteredTextureAt(languageValuePosition, 325, 100, languageValueTextureToDraw);
}

//Draws the scroll when confirming changes
void OptionsController::drawConfirmOptions(Position scrollPosition) {
	//Confirm Text
	Utils::drawFirstFittingTextureCenteredAt(Position(scrollPosition.x + 200, scrollPosition.y + 216), 600, 90, this->confirmChangesTexture);

	//Restart Text
	Utils::drawFirstFittingTextureCenteredAt(Position(scrollPosition.x + 200, scrollPosition.y + 326), 600, 90, this->restartTexture);

	//Yes
	Utils::drawFirstFittingTextureCenteredAt(Position(scrollPosition.x + 260, scrollPosition.y + 445), 130, 94, this->yesTexture);

	//No
	Utils::drawFirstFittingTextureCenteredAt(Position(scrollPosition.x + 604, scrollPosition.y + 445), 130, 94, this->noTexture);

	//Now we draw the selector. We get the position based on the selected row
	//This is a special case
	Position confirmSelectorPosition = Position(scrollPosition.x + 250 + this->selectedRow * 344, scrollPosition.y + 450);
	this->confirmOptionsSelector->draw(confirmSelectorPosition);
}

//Saves current changes
void OptionsController::saveConfiguration() {
	//FullScreen
	if (this->fullscreenValue) {
		Config::setConfig("FullScreen", "1");
	}
	else {
		Config::setConfig("FullScreen", "0");
	}

	//Resolution Width
	Config::setConfig("ResolutionWidth", resolutionWidthValue);

	//Resolution Height
	Config::setConfig("ResolutionHeight", resolutionHeightValue);

	//Music Volume
	Config::setConfig("MusicVolume", std::to_string(this->musicVolume));

	//Sound Volume
	Config::setConfig("SoundVolume", std::to_string(this->soundVolume));

	//Language
	Config::setConfig("Language", this->languageCodes.at(this->languageVectorPosition));

	//We now save the configuration
	Config::saveConfig();
}

//Changes the Language
void OptionsController::changeLanguage(std::string newLanguageCode) {
	//First we liberate all the previously assigned textures
	for (Texture* texture : this->optionsTexture) {
		delete(texture);
	}
	this->optionsTexture.clear();

	for (Texture* texture : this->graphicsTexture) {
		delete(texture);
	}
	this->graphicsTexture.clear();

	for (Texture* texture : this->graphicsUnderlinedTexture) {
		delete(texture);
	}
	this->graphicsUnderlinedTexture.clear();

	for (Texture* texture : this->soundTexture) {
		delete(texture);
	}
	this->soundTexture.clear();

	for (Texture* texture : this->soundUnderlinedTexture) {
		delete(texture);
	}
	this->soundUnderlinedTexture.clear();

	for (Texture* texture : this->otherTexture) {
		delete(texture);
	}
	this->otherTexture.clear();

	for (Texture* texture : this->otherUnderlinedTexture) {
		delete(texture);
	}
	this->otherUnderlinedTexture.clear();

	for (Texture* texture : this->exitTexture) {
		delete(texture);
	}
	this->exitTexture.clear();

	for (Texture* texture : this->fullscreenTexture) {
		delete(texture);
	}
	this->fullscreenTexture.clear();

	for (Texture* texture : this->screenWidthTexture) {
		delete(texture);
	}
	this->screenWidthTexture.clear();

	for (Texture* texture : this->screenHeightTexture) {
		delete(texture);
	}
	this->screenHeightTexture.clear();

	for (Texture* texture : this->minWidthTexture) {
		delete(texture);
	}
	this->minWidthTexture.clear();

	for (Texture* texture : this->minHeightTexture) {
		delete(texture);
	}
	this->minHeightTexture.clear();

	for (Texture* texture : this->musicTexture) {
		delete(texture);
	}
	this->musicTexture.clear();

	for (Texture* texture : this->soundsTexture) {
		delete(texture);
	}
	this->soundsTexture.clear();

	for (Texture* texture : this->languageTexture) {
		delete(texture);
	}
	this->languageTexture.clear();

	for (Texture* texture : this->defaultTexture) {
		delete(texture);
	}
	this->defaultTexture.clear();

	for (Texture* texture : this->confirmChangesTexture) {
		delete(texture);
	}
	this->confirmChangesTexture.clear();

	for (Texture* texture : this->yesTexture) {
		delete(texture);
	}
	this->yesTexture.clear();

	for (Texture* texture : this->noTexture) {
		delete(texture);
	}
	this->noTexture.clear();

	for (Texture* texture : this->restartTexture) {
		delete(texture);
	}
	this->restartTexture.clear();

	//Now we create all of them again

	//We define the color (Red)
	SDL_Color textColor;
	textColor.r = 0;
	textColor.b = 255;
	textColor.g = 0;
	textColor.a = 255;

	//We open the file
	std::wifstream file;
	file.open("Resources/Text/" + newLanguageCode + "/OptionsText.txt");

	//String where the different lines of the file will be stored
	std::wstring line;

	//We get the line of Options
	getline(file, line);

	this->optionsTexture.push_back(Loader::getUnderlineText("ComputerFont", line, textColor, FontSize::VeryBig));
	this->optionsTexture.push_back(Loader::getUnderlineText("ComputerFont", line, textColor, FontSize::Big));
	this->optionsTexture.push_back(Loader::getUnderlineText("ComputerFont", line, textColor, FontSize::Medium));

	//We get the line of graphics
	getline(file, line);

	this->graphicsTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::VeryBig));
	this->graphicsTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Big));
	this->graphicsTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Medium));

	this->graphicsUnderlinedTexture.push_back(Loader::getUnderlineText("ComputerFont", line, textColor, FontSize::VeryBig));
	this->graphicsUnderlinedTexture.push_back(Loader::getUnderlineText("ComputerFont", line, textColor, FontSize::Big));
	this->graphicsUnderlinedTexture.push_back(Loader::getUnderlineText("ComputerFont", line, textColor, FontSize::Medium));

	//We get the line of sound
	getline(file, line);

	this->soundTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::VeryBig));
	this->soundTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Big));
	this->soundTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Medium));

	this->soundUnderlinedTexture.push_back(Loader::getUnderlineText("ComputerFont", line, textColor, FontSize::VeryBig));
	this->soundUnderlinedTexture.push_back(Loader::getUnderlineText("ComputerFont", line, textColor, FontSize::Big));
	this->soundUnderlinedTexture.push_back(Loader::getUnderlineText("ComputerFont", line, textColor, FontSize::Medium));

	//We get the line of other
	getline(file, line);

	this->otherTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::VeryBig));
	this->otherTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Big));
	this->otherTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Medium));

	this->otherUnderlinedTexture.push_back(Loader::getUnderlineText("ComputerFont", line, textColor, FontSize::VeryBig));
	this->otherUnderlinedTexture.push_back(Loader::getUnderlineText("ComputerFont", line, textColor, FontSize::Big));
	this->otherUnderlinedTexture.push_back(Loader::getUnderlineText("ComputerFont", line, textColor, FontSize::Medium));

	//We get the line of exit
	getline(file, line);

	this->exitTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::VeryBig));
	this->exitTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Big));
	this->exitTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Medium));

	//We get the line of Fullscreen
	getline(file, line);

	this->fullscreenTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::VeryBig));
	this->fullscreenTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Big));
	this->fullscreenTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Medium));

	//We get the line of Screen Width
	getline(file, line);

	this->screenWidthTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::VeryBig));
	this->screenWidthTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Big));
	this->screenWidthTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Medium));

	//We get the line of Screen Height
	getline(file, line);

	this->screenHeightTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::VeryBig));
	this->screenHeightTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Big));
	this->screenHeightTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Medium));

	//We get the line of Min Screen Width
	getline(file, line);

	this->minWidthTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::VeryBig));
	this->minWidthTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Big));
	this->minWidthTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Medium));

	//We get the line of Min Screen Height
	getline(file, line);

	this->minHeightTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::VeryBig));
	this->minHeightTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Big));
	this->minHeightTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Medium));

	//We get the line of Music
	getline(file, line);

	this->musicTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::VeryBig));
	this->musicTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Big));
	this->musicTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Medium));

	//We get the line of Sounds
	getline(file, line);

	this->soundsTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::VeryBig));
	this->soundsTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Big));
	this->soundsTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Medium));

	//We get the line of Language
	getline(file, line);

	this->languageTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::VeryBig));
	this->languageTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Big));
	this->languageTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Medium));

	//We get the line of Default
	getline(file, line);

	this->defaultTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::VeryBig));
	this->defaultTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Big));
	this->defaultTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Medium));

	//We get the line of Confirmg Changes
	getline(file, line);

	this->confirmChangesTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::VeryBig));
	this->confirmChangesTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Big));
	this->confirmChangesTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Medium));

	//We get the line of Yes
	getline(file, line);

	this->yesTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::VeryBig));
	this->yesTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Big));
	this->yesTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Medium));

	//We get the line of No
	getline(file, line);

	this->noTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::VeryBig));
	this->noTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Big));
	this->noTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Medium));

	//We get the line of Restarts
	getline(file, line);

	this->restartTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::VeryBig));
	this->restartTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Big));
	this->restartTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Medium));

	//We close the file
	file.close();

	//We change the language of the main menu
	this->mainController->changeMainMenuLanguage(newLanguageCode);
}

//Saves current changes
void OptionsController::defaultConfiguration() {
	//We define the color (Red)
	SDL_Color textColor;
	textColor.r = 0;
	textColor.b = 255;
	textColor.g = 0;
	textColor.a = 255;

	//Fullscreen
	if (std::atoi(Config::getDefaultConfig("FullScreen").c_str()) == 0) {
		//Not fullscreen
		this->fullscreenValue = false;
	}
	else {
		this->fullscreenValue = true;
	}

	//Resolution Width
	this->resolutionWidthValue = Config::getDefaultConfig("ResolutionWidth");

	for (Texture* texture : this->resolutionWidthValueTexture) {
		delete(texture);
	}

	this->resolutionWidthValueTexture.push_back(Loader::getText("ComputerFont", this->resolutionWidthValue, textColor, FontSize::VeryBig));
	this->resolutionWidthValueTexture.push_back(Loader::getText("ComputerFont", this->resolutionWidthValue, textColor, FontSize::Big));
	this->resolutionWidthValueTexture.push_back(Loader::getText("ComputerFont", this->resolutionWidthValue, textColor, FontSize::Medium));

	//Resolution Height
	this->resolutionHeightValue = Config::getDefaultConfig("ResolutionHeight");

	for (Texture* texture : this->resolutionHeightValueTexture) {
		delete(texture);
	}

	this->resolutionHeightValueTexture.push_back(Loader::getText("ComputerFont", this->resolutionHeightValue, textColor, FontSize::VeryBig));
	this->resolutionHeightValueTexture.push_back(Loader::getText("ComputerFont", this->resolutionHeightValue, textColor, FontSize::Big));
	this->resolutionHeightValueTexture.push_back(Loader::getText("ComputerFont", this->resolutionHeightValue, textColor, FontSize::Medium));

	//Music Volume
	this->musicVolume = std::atoi(Config::getDefaultConfig("MusicVolume").c_str());

	//Sound Volume
	this->soundVolume = std::atoi(Config::getDefaultConfig("SoundVolume").c_str());

	//Grid
	if (std::atoi(Config::getDefaultConfig("Grid").c_str()) == 0) {
		//Not fullscreen
		this->gridValue = false;
	}
	else {
		this->gridValue = true;
	}

	//Field Animations
	if (std::atoi(Config::getDefaultConfig("FieldAnimation").c_str()) == 0) {
		//Not fullscreen
		this->fieldAnimationValue = false;
	}
	else {
		this->fieldAnimationValue = true;
	}

	//We reset the music volumes
	Mix_VolumeMusic(this->musicVolume);
	Mix_Volume(-1, this->soundVolume);
}

//Constructor
OptionsController::OptionsController(MainController* mainController, SDL_Renderer* renderer) :IController(mainController, renderer) {
	//We get all the non text Textures
	this->backgroundTexture = Loader::getTexture("OptionsBackground");
	this->selectorTexture = Loader::getTexture("OptionsSelector");
	this->graphicsOptionsSeparator = Loader::getTexture("OptionsGraphicsSeparator");
	this->graphicsOptionsSelector = Loader::getTexture("OptionsGraphicsSelector");
	this->soundOptionsSeparator = Loader::getTexture("OptionsSoundSeparator");
	this->soundOptionsSelector = Loader::getTexture("OptionsSoundSelector");
	this->soundOptionsSubSelector = Loader::getTexture("OptionsSoundSubSelector");
	this->otherOptionsSeparator = Loader::getTexture("OptionsOtherSeparator");
	this->otherOptionsSelector = Loader::getTexture("OptionsOtherSelector");
	this->otherOptionsDefaultSelector = Loader::getTexture("OptionsOtherDefaultSelector");
	this->confirmOptionsSelector = Loader::getTexture("OptionsConfirmSelector");
	this->boolOptionsSelector = Loader::getTexture("OptionsBoolOptionSelector");

	//We create all the text textures. First we need to know the language
	std::string languageCode = Config::getConfig("Language");

	//We define the color (Red)
	SDL_Color textColor;
	textColor.r = 0;
	textColor.b = 255;
	textColor.g = 0;
	textColor.a = 255;

	//We open the file
	std::wifstream file;
	file.open("Resources/Text/" + languageCode + "/OptionsText.txt");

	//String where the different lines of the file will be stored
	std::wstring line;

	//We get the line of Options
	getline(file, line);

	this->optionsTexture.push_back(Loader::getUnderlineText("ComputerFont", line, textColor, FontSize::VeryBig));
	this->optionsTexture.push_back(Loader::getUnderlineText("ComputerFont", line, textColor, FontSize::Big));
	this->optionsTexture.push_back(Loader::getUnderlineText("ComputerFont", line, textColor, FontSize::Medium));

	//We get the line of graphics
	getline(file, line);

	this->graphicsTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::VeryBig));
	this->graphicsTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Big));
	this->graphicsTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Medium));

	this->graphicsUnderlinedTexture.push_back(Loader::getUnderlineText("ComputerFont", line, textColor, FontSize::VeryBig));
	this->graphicsUnderlinedTexture.push_back(Loader::getUnderlineText("ComputerFont", line, textColor, FontSize::Big));
	this->graphicsUnderlinedTexture.push_back(Loader::getUnderlineText("ComputerFont", line, textColor, FontSize::Medium));

	//We get the line of sound
	getline(file, line);

	this->soundTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::VeryBig));
	this->soundTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Big));
	this->soundTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Medium));

	this->soundUnderlinedTexture.push_back(Loader::getUnderlineText("ComputerFont", line, textColor, FontSize::VeryBig));
	this->soundUnderlinedTexture.push_back(Loader::getUnderlineText("ComputerFont", line, textColor, FontSize::Big));
	this->soundUnderlinedTexture.push_back(Loader::getUnderlineText("ComputerFont", line, textColor, FontSize::Medium));

	//We get the line of other
	getline(file, line);

	this->otherTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::VeryBig));
	this->otherTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Big));
	this->otherTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Medium));

	this->otherUnderlinedTexture.push_back(Loader::getUnderlineText("ComputerFont", line, textColor, FontSize::VeryBig));
	this->otherUnderlinedTexture.push_back(Loader::getUnderlineText("ComputerFont", line, textColor, FontSize::Big));
	this->otherUnderlinedTexture.push_back(Loader::getUnderlineText("ComputerFont", line, textColor, FontSize::Medium));

	//We get the line of exit
	getline(file, line);

	this->exitTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::VeryBig));
	this->exitTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Big));
	this->exitTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Medium));

	//We get the line of Fullscreen
	getline(file, line);

	this->fullscreenTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::VeryBig));
	this->fullscreenTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Big));
	this->fullscreenTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Medium));

	//We get the line of Screen Width
	getline(file, line);

	this->screenWidthTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::VeryBig));
	this->screenWidthTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Big));
	this->screenWidthTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Medium));

	//We get the line of Screen Height
	getline(file, line);

	this->screenHeightTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::VeryBig));
	this->screenHeightTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Big));
	this->screenHeightTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Medium));

	//We get the line of Min Screen Width
	getline(file, line);

	this->minWidthTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::VeryBig));
	this->minWidthTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Big));
	this->minWidthTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Medium));

	//We get the line of Min Screen Height
	getline(file, line);

	this->minHeightTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::VeryBig));
	this->minHeightTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Big));
	this->minHeightTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Medium));

	//We get the line of Music
	getline(file, line);

	this->musicTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::VeryBig));
	this->musicTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Big));
	this->musicTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Medium));

	//We get the line of Sounds
	getline(file, line);

	this->soundsTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::VeryBig));
	this->soundsTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Big));
	this->soundsTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Medium));

	//We get the line of Language
	getline(file, line);

	this->languageTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::VeryBig));
	this->languageTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Big));
	this->languageTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Medium));

	//We get the line of Default
	getline(file, line);

	this->defaultTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::VeryBig));
	this->defaultTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Big));
	this->defaultTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Medium));

	//We get the line of Confirmg Changes
	getline(file, line);

	this->confirmChangesTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::VeryBig));
	this->confirmChangesTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Big));
	this->confirmChangesTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Medium));

	//We get the line of Yes
	getline(file, line);

	this->yesTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::VeryBig));
	this->yesTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Big));
	this->yesTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Medium));

	//We get the line of No
	getline(file, line);

	this->noTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::VeryBig));
	this->noTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Big));
	this->noTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Medium));

	//We get the line of Restarts
	getline(file, line);

	this->restartTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::VeryBig));
	this->restartTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Big));
	this->restartTexture.push_back(Loader::getText("ComputerFont", line, textColor, FontSize::Medium));

	//We close the file
	file.close();

	//We get the sound effects
	this->changeSelectionSound = Loader::getSound("ChangeSelectionBeep");
	this->selectionSound = Loader::getSound("SelectionBeep");

	//We set the current state and the selected row
	this->currentState = OptionControllerState::NoOption;
	this->selectedRow = 0;

	//We get all the current options

	//Fullscreen
	if (std::atoi(Config::getConfig("FullScreen").c_str()) == 0) {
		//Not fullscreen
		this->fullscreenValue = false;
	}
	else {
		this->fullscreenValue = true;
	}

	//Resolution Width
	this->resolutionWidthValue = Config::getConfig("ResolutionWidth");

	this->resolutionWidthValueTexture.push_back(Loader::getText("ComputerFont", this->resolutionWidthValue, textColor, FontSize::VeryBig));
	this->resolutionWidthValueTexture.push_back(Loader::getText("ComputerFont", this->resolutionWidthValue, textColor, FontSize::Big));
	this->resolutionWidthValueTexture.push_back(Loader::getText("ComputerFont", this->resolutionWidthValue, textColor, FontSize::Medium));

	//Resolution Height
	this->resolutionHeightValue = Config::getConfig("ResolutionHeight");

	this->resolutionHeightValueTexture.push_back(Loader::getText("ComputerFont", this->resolutionHeightValue, textColor, FontSize::VeryBig));
	this->resolutionHeightValueTexture.push_back(Loader::getText("ComputerFont", this->resolutionHeightValue, textColor, FontSize::Big));
	this->resolutionHeightValueTexture.push_back(Loader::getText("ComputerFont", this->resolutionHeightValue, textColor, FontSize::Medium));

	//Music Volume
	this->musicVolume = std::atoi(Config::getConfig("MusicVolume").c_str());

	//Sound Volume
	this->soundVolume = std::atoi(Config::getConfig("SoundVolume").c_str());

	//Grid
	if (std::atoi(Config::getConfig("Grid").c_str()) == 0) {
		//Keyboard Input
		this->gridValue = false;
	}
	else {
		//Controller Input
		this->gridValue = true;
	}

	//Field Animation
	if (std::atoi(Config::getConfig("FieldAnimation").c_str()) == 0) {
		//Keyboard Input
		this->fieldAnimationValue = false;
	}
	else {
		//Controller Input
		this->fieldAnimationValue = true;
	}

	//We prepare the language

	//English
	this->languagesTextures.push_back(Loader::getText("ComputerFont", "English", textColor, FontSize::VeryBig));
	this->languageCodes.push_back("EN");

	//Spanish
	this->languagesTextures.push_back(Loader::getText("ComputerFont", "Español", textColor, FontSize::VeryBig));
	this->languageCodes.push_back("ES");

	for (int i = 0; i < languageCodes.size(); i++) {
		if (languageCodes.at(i).compare(languageCode) == 0) {
			this->languageVectorPosition = i;
		}
	}

	//At the beginning there is no text or controll beeing input or language beeing changed
	this->textBeingInput = false;
	this->languageBeeingChanged = false;
}

//Destroyer
OptionsController::~OptionsController() {
	//We have to unload all the loaded Textures
	Loader::unloadFiles("Options/OptionsResources");

	//Now we have to free all the created Text Textures

	for (Texture* texture : this->optionsTexture) {
		delete(texture);
	}
	this->optionsTexture.clear();

	for (Texture* texture : this->graphicsTexture) {
		delete(texture);
	}
	this->graphicsTexture.clear();

	for (Texture* texture : this->graphicsUnderlinedTexture) {
		delete(texture);
	}
	this->graphicsUnderlinedTexture.clear();

	for (Texture* texture : this->soundTexture) {
		delete(texture);
	}
	this->soundTexture.clear();

	for (Texture* texture : this->soundUnderlinedTexture) {
		delete(texture);
	}
	this->soundUnderlinedTexture.clear();

	for (Texture* texture : this->otherTexture) {
		delete(texture);
	}
	this->otherTexture.clear();

	for (Texture* texture : this->otherUnderlinedTexture) {
		delete(texture);
	}
	this->otherUnderlinedTexture.clear();

	for (Texture* texture : this->exitTexture) {
		delete(texture);
	}
	this->exitTexture.clear();

	for (Texture* texture : this->fullscreenTexture) {
		delete(texture);
	}
	this->fullscreenTexture.clear();

	for (Texture* texture : this->screenWidthTexture) {
		delete(texture);
	}
	this->screenWidthTexture.clear();

	for (Texture* texture : this->screenHeightTexture) {
		delete(texture);
	}
	this->screenHeightTexture.clear();

	for (Texture* texture : this->minWidthTexture) {
		delete(texture);
	}
	this->minWidthTexture.clear();

	for (Texture* texture : this->minHeightTexture) {
		delete(texture);
	}
	this->minHeightTexture.clear();

	for (Texture* texture : this->musicTexture) {
		delete(texture);
	}
	this->musicTexture.clear();

	for (Texture* texture : this->soundsTexture) {
		delete(texture);
	}
	this->soundsTexture.clear();

	for (Texture* texture : this->languageTexture) {
		delete(texture);
	}
	this->languageTexture.clear();

	for (Texture* texture : this->defaultTexture) {
		delete(texture);
	}
	this->defaultTexture.clear();

	for (Texture* texture : this->confirmChangesTexture) {
		delete(texture);
	}
	this->confirmChangesTexture.clear();

	for (Texture* texture : this->yesTexture) {
		delete(texture);
	}
	this->yesTexture.clear();

	for (Texture* texture : this->noTexture) {
		delete(texture);
	}
	this->noTexture.clear();

	for (Texture* texture : this->restartTexture) {
		delete(texture);
	}
	this->restartTexture.clear();
}

//Function to manage the input
void OptionsController::manageInput() {
	int maxRow = 0;
	switch (this->currentState) {
	case OptionControllerState::NoOption:
		maxRow = 3;
		break;
	case OptionControllerState::GraphicsOptions:
		maxRow = 2;
		break;
	case OptionControllerState::SoundOptions:
		maxRow = 1;
		break;
	case OptionControllerState::OtherOptions:
		maxRow = 1;
		break;
	case OptionControllerState::ConfirmChanges:
		maxRow = 1;
		break;
	}

	if (this->textBeingInput) {
		std::string valueBeingModified;
		switch (this->selectedRow) {
		case 1:
			valueBeingModified = this->resolutionWidthValue;
			break;
		case 2:
			valueBeingModified = this->resolutionHeightValue;
			break;
		}

		//We define the color (Blue)
		SDL_Color textColor;
		textColor.r = 0;
		textColor.b = 255;
		textColor.g = 0;
		textColor.a = 255;

		SDL_Event e;
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_BACKSPACE) {
					if (valueBeingModified.length() > 0) {
						//lop off character
						valueBeingModified.pop_back();
						switch (this->selectedRow) {
						case 1:
							//We free the textures
							for (Texture* texture : this->resolutionWidthValueTexture) {
								delete(texture);
							}
							this->resolutionWidthValueTexture.clear();

							this->resolutionWidthValue = valueBeingModified;

							this->resolutionWidthValueTexture.push_back(Loader::getText("ComputerFont", this->resolutionWidthValue, textColor, FontSize::VeryBig));
							this->resolutionWidthValueTexture.push_back(Loader::getText("ComputerFont", this->resolutionWidthValue, textColor, FontSize::Big));
							this->resolutionWidthValueTexture.push_back(Loader::getText("ComputerFont", this->resolutionWidthValue, textColor, FontSize::Medium));
							break;
						case 2:
							//We free the textures
							for (Texture* texture : this->resolutionHeightValueTexture) {
								delete(texture);
							}
							this->resolutionHeightValueTexture.clear();

							this->resolutionHeightValue = valueBeingModified;

							this->resolutionHeightValueTexture.push_back(Loader::getText("ComputerFont", this->resolutionHeightValue, textColor, FontSize::VeryBig));
							this->resolutionHeightValueTexture.push_back(Loader::getText("ComputerFont", this->resolutionHeightValue, textColor, FontSize::Big));
							this->resolutionHeightValueTexture.push_back(Loader::getText("ComputerFont", this->resolutionHeightValue, textColor, FontSize::Medium));
							break;
						}
					}
				}
				else if (e.key.keysym.sym == SDLK_RETURN) {
					Utils::playSound(this->selectionSound);
					Input::setInputAsPressed(InputType::Selection);
					int inputValue = std::atoi(valueBeingModified.c_str());
					int minValue = 0;

					switch (this->selectedRow) {
					case 1:
						minValue = 1000;
						break;
					case 2:
						minValue = 800;
						break;
					}

					if (inputValue < minValue) {
						inputValue = minValue;
						valueBeingModified = std::to_string(inputValue);
					}

					switch (this->selectedRow) {
					case 1:
						//We free the textures
						for (Texture* texture : this->resolutionWidthValueTexture) {
							delete(texture);
						}
						this->resolutionWidthValueTexture.clear();

						this->resolutionWidthValue = valueBeingModified;

						this->resolutionWidthValueTexture.push_back(Loader::getText("ComputerFont", this->resolutionWidthValue, textColor, FontSize::VeryBig));
						this->resolutionWidthValueTexture.push_back(Loader::getText("ComputerFont", this->resolutionWidthValue, textColor, FontSize::Big));
						this->resolutionWidthValueTexture.push_back(Loader::getText("ComputerFont", this->resolutionWidthValue, textColor, FontSize::Medium));
						break;
					case 2:
						//We free the textures
						for (Texture* texture : this->resolutionHeightValueTexture) {
							delete(texture);
						}
						this->resolutionHeightValueTexture.clear();

						this->resolutionHeightValue = valueBeingModified;

						this->resolutionHeightValueTexture.push_back(Loader::getText("ComputerFont", this->resolutionHeightValue, textColor, FontSize::VeryBig));
						this->resolutionHeightValueTexture.push_back(Loader::getText("ComputerFont", this->resolutionHeightValue, textColor, FontSize::Big));
						this->resolutionHeightValueTexture.push_back(Loader::getText("ComputerFont", this->resolutionHeightValue, textColor, FontSize::Medium));
						break;
					}

					this->textBeingInput = false;
					Input::setHandleMouse(true);
				}
			}
			else if (e.type == SDL_TEXTINPUT) {
				if (isdigit(*(e.text.text)) != 0 && valueBeingModified.length() < 7) {
					valueBeingModified += e.text.text;
					switch (this->selectedRow) {
					case 1:
						//We free the textures
						for (Texture* texture : this->resolutionWidthValueTexture) {
							delete(texture);
						}
						this->resolutionWidthValueTexture.clear();

						this->resolutionWidthValue = valueBeingModified;

						this->resolutionWidthValueTexture.push_back(Loader::getText("ComputerFont", this->resolutionWidthValue, textColor, FontSize::VeryBig));
						this->resolutionWidthValueTexture.push_back(Loader::getText("ComputerFont", this->resolutionWidthValue, textColor, FontSize::Big));
						this->resolutionWidthValueTexture.push_back(Loader::getText("ComputerFont", this->resolutionWidthValue, textColor, FontSize::Medium));
						break;
					case 2:
						//We free the textures
						for (Texture* texture : this->resolutionHeightValueTexture) {
							delete(texture);
						}
						this->resolutionHeightValueTexture.clear();

						this->resolutionHeightValue = valueBeingModified;

						this->resolutionHeightValueTexture.push_back(Loader::getText("ComputerFont", this->resolutionHeightValue, textColor, FontSize::VeryBig));
						this->resolutionHeightValueTexture.push_back(Loader::getText("ComputerFont", this->resolutionHeightValue, textColor, FontSize::Big));
						this->resolutionHeightValueTexture.push_back(Loader::getText("ComputerFont", this->resolutionHeightValue, textColor, FontSize::Medium));
						break;
					}
				}
			}
		}
	}
	else if (this->languageBeeingChanged) {
		//Right
		if (Input::inputPressed(InputType::Right)) {
			this->languageVectorPosition++;
			if (this->languageVectorPosition >= languagesTextures.size()) {
				this->languageVectorPosition = 0;
			}
			this->changeLanguage(this->languageCodes.at(this->languageVectorPosition));
			Utils::playSound(this->changeSelectionSound);
		}

		//Left
		if (Input::inputPressed(InputType::Left)) {
			this->languageVectorPosition--;
			if (this->languageVectorPosition < 0) {
				this->languageVectorPosition = languagesTextures.size() - 1;
			}
			this->changeLanguage(this->languageCodes.at(this->languageVectorPosition));
			Utils::playSound(this->changeSelectionSound);
		}

		//Selection
		if (Input::inputPressed(InputType::Selection) || Input::mouseLeftInputPressed()) {
			this->languageBeeingChanged = false;
			Utils::playSound(this->selectionSound);
		}
	}
	else if (this->volumeBeeingChanged) {
		//Right
		if (Input::inputPressed(InputType::Right)) {
			Utils::playSound(this->changeSelectionSound);
			switch (this->selectedRow) {
			case 0:
				if (this->musicVolume > 100) {
					this->musicVolume = 100;
				}
				else {
					this->musicVolume -= 25;
					if (this->musicVolume < 0) {
						this->musicVolume = 0;
					}
				}
				Mix_VolumeMusic(this->musicVolume);
				break;
			case 1:
				if (this->soundVolume > 100) {
					this->soundVolume = 100;
				}
				else {
					this->soundVolume -= 25;
					if (this->soundVolume < 0) {
						this->soundVolume = 0;
					}
				}
				Mix_Volume(-1, this->soundVolume);
				break;
			}
		}

		//Left
		if (Input::inputPressed(InputType::Left)) {
			Utils::playSound(this->changeSelectionSound);
			switch (this->selectedRow) {
			case 0:
				if (this->musicVolume == 100) {
					this->musicVolume = 128;
				}
				else {
					this->musicVolume += 25;
					if (this->musicVolume > 128) {
						this->musicVolume = 128;
					}
				}
				Mix_VolumeMusic(this->musicVolume);
				break;
			case 1:
				if (this->soundVolume == 100) {
					this->soundVolume = 128;
				}
				else {
					this->soundVolume += 25;
					if (this->soundVolume > 128) {
						this->soundVolume = 128;
					}
				}
				Mix_Volume(-1, this->soundVolume);
				break;
			}
		}

		//Selection
		if (Input::inputPressed(InputType::Selection) || Input::mouseLeftInputPressed()) {
			Utils::playSound(this->selectionSound);
			this->volumeBeeingChanged = false;
		}
	}
	else {
		//Down
		if (this->currentState != OptionControllerState::ConfirmChanges && Input::inputPressed(InputType::Down)) {
			Utils::playSound(this->changeSelectionSound);
			this->selectedRow++;
			if (this->selectedRow > maxRow) {
				this->selectedRow = 0;
			}
		}

		//Up
		if (this->currentState != OptionControllerState::ConfirmChanges && Input::inputPressed(InputType::Up)) {
			Utils::playSound(this->changeSelectionSound);
			this->selectedRow--;
			//We check if it has to go to the last option
			if (this->selectedRow < 0) {
				this->selectedRow = maxRow;
			}
		}

		//Right
		if (this->currentState == OptionControllerState::ConfirmChanges && Input::inputPressed(InputType::Right)) {
			Utils::playSound(this->changeSelectionSound);
			this->selectedRow++;
			if (this->selectedRow > maxRow) {
				this->selectedRow = 0;
			}
		}

		//Left
		if (this->currentState == OptionControllerState::ConfirmChanges && Input::inputPressed(InputType::Left)) {
			Utils::playSound(this->changeSelectionSound);
			this->selectedRow--;
			//We check if it has to go to the last option
			if (this->selectedRow < 0) {
				this->selectedRow = maxRow;
			}
		}

		//Selection
		if (Input::inputPressed(InputType::Selection) || Input::mouseLeftInputPressed()) {

			SDL_Event e;
			switch (this->currentState) {
			case OptionControllerState::NoOption:
				Utils::playSound(this->selectionSound);
				switch (this->selectedRow) {
				case 0: //Graphics
					this->currentState = OptionControllerState::GraphicsOptions;
					this->selectedRow = 0;
					break;
				case 1: //Sound
					this->currentState = OptionControllerState::SoundOptions;
					this->selectedRow = 0;
					break;
				case 2: //Other
					this->currentState = OptionControllerState::OtherOptions;
					this->selectedRow = 0;
					break;
				case 3: //Exit
					this->currentState = OptionControllerState::ConfirmChanges;
					this->selectedRow = 1;
					break;
				}
				break;
			case OptionControllerState::GraphicsOptions:
				Utils::playSound(this->selectionSound);
				switch (this->selectedRow) {
				case 0://Fullscreen
					this->fullscreenValue = !this->fullscreenValue;
					break;
				case 1://Screen Width
				case 2://Screen Height
					this->textBeingInput = true;
					Input::setHandleMouse(false);
					while (SDL_PollEvent(&e) != 0) {
					}
					break;
				}
				break;
			case OptionControllerState::SoundOptions:
				Utils::playSound(this->selectionSound);
				this->volumeBeeingChanged = true;
				break;
			case OptionControllerState::OtherOptions:
				Utils::playSound(this->selectionSound);
				switch (this->selectedRow) {
				case 0:
					this->languageBeeingChanged = true;
					break;
				case 1://Default Reset
					Utils::playSound(this->selectionSound);
					this->defaultConfiguration();
					break;
				}
				break;
			case OptionControllerState::ConfirmChanges:
				Utils::playSound(this->selectionSound);
				switch (this->selectedRow) {
				case 0: //Yes
					this->saveConfiguration();
					Input::changeConfiguration();
					this->mainController->openMainMenu();
					this->mainController->freeController(this);
					break;
				case 1: //No
					//We have to reset the volume of the music, the rest will simply be ignored
					Mix_VolumeMusic(std::atoi(Config::getConfig("MusicVolume").c_str()));
					Mix_Volume(-1, std::atoi(Config::getConfig("SoundVolume").c_str()));

					//We reload the language
					this->mainController->changeMainMenuLanguage(Config::getConfig("Language"));

					//We reopen the main menu
					this->mainController->openMainMenu();
					this->mainController->freeController(this);
					break;
				}
				break;
			}
		}

		//Back
		if (Input::inputPressed(InputType::Back) || Input::mouseRightInputPressed()) {
			//This variable is used in OptionControllerState::ControllsOptions case to check if all inputs have been assigned
			bool allAsigned = true;
			switch (this->currentState) {
			case OptionControllerState::NoOption:
				Utils::playSound(this->selectionSound);
				this->currentState = OptionControllerState::ConfirmChanges;
				this->selectedRow = 1;
				break;
			case OptionControllerState::GraphicsOptions:
				Utils::playSound(this->selectionSound);
				this->selectedRow = 0;
				this->currentState = OptionControllerState::NoOption;
				break;
			case OptionControllerState::SoundOptions:
				Utils::playSound(this->selectionSound);
				this->selectedRow = 1;
				this->currentState = OptionControllerState::NoOption;
				break;
			case OptionControllerState::OtherOptions:
				Utils::playSound(this->selectionSound);
				this->selectedRow = 2;
				this->currentState = OptionControllerState::NoOption;
				break;
			case OptionControllerState::ConfirmChanges:
				this->selectedRow = 1;
				break;
			}
		}

		//Mouse
		if (Input::mouseMoved()) {
			//Mouse Controlls
			Position scrollPosition = Utils::getCenteredPosition(Position(0, 0), Utils::getScreenWidth(), Utils::getScreenHeight(), this->backgroundTexture->width, this->backgroundTexture->height);
			Position mousePosition = Input::getMousePosition();

			//We get the position of the mouse inside the scroll
			Position mouseScrollPosition = Position(mousePosition.x - scrollPosition.x, mousePosition.y - scrollPosition.y);

			switch (this->currentState) {
			case OptionControllerState::NoOption:
				//We check if it's in the column of options
				if (mouseScrollPosition.x > 300 && mouseScrollPosition.x < 700) {
					//We check if it's on any of the options
					if (mouseScrollPosition.y >= 136 && mouseScrollPosition.y < 236) {
						if (this->selectedRow != 0) {
							Utils::playSound(this->changeSelectionSound);
						}
						this->selectedRow = 0;
					}
					else if (mouseScrollPosition.y >= 246 && mouseScrollPosition.y < 346) {
						if (this->selectedRow != 1) {
							Utils::playSound(this->changeSelectionSound);
						}
						this->selectedRow = 1;
					}
					else if (mouseScrollPosition.y >= 356 && mouseScrollPosition.y < 456) {
						if (this->selectedRow != 2) {
							Utils::playSound(this->changeSelectionSound);
						}
						this->selectedRow = 2;
					}
					else if (mouseScrollPosition.y >= 466 && mouseScrollPosition.y < 566) {
						if (this->selectedRow != 3) {
							Utils::playSound(this->changeSelectionSound);
						}
						this->selectedRow = 3;
					}

					if (this->selectedRow > maxRow) {
						this->selectedRow = maxRow;
					}
				}
				break;
			case OptionControllerState::GraphicsOptions:
				//We check if it's in the column of options
				if (mouseScrollPosition.x > 150 && mouseScrollPosition.x < 475) {
					//We check if it's on any of the options
					if (mouseScrollPosition.y >= 136 && mouseScrollPosition.y < 236) {
						if (this->selectedRow != 0) {
							Utils::playSound(this->changeSelectionSound);
						}
						this->selectedRow = 0;
					}
					else if (mouseScrollPosition.y >= 246 && mouseScrollPosition.y < 346) {
						if (this->selectedRow != 1) {
							Utils::playSound(this->changeSelectionSound);
						}
						this->selectedRow = 1;
					}
					else if (mouseScrollPosition.y >= 356 && mouseScrollPosition.y < 456) {
						if (this->selectedRow != 2) {
							Utils::playSound(this->changeSelectionSound);
						}
						this->selectedRow = 2;
					}

					if (this->selectedRow > maxRow) {
						this->selectedRow = maxRow;
					}
				}
				break;
			case OptionControllerState::SoundOptions:
				//We check if it's in the column of options
				if (mouseScrollPosition.x > 150 && mouseScrollPosition.x < 475) {
					//We check if it's on any of the options
					if (mouseScrollPosition.y >= 136 && mouseScrollPosition.y < 236) {
						if (this->selectedRow != 0) {
							Utils::playSound(this->changeSelectionSound);
						}
						this->selectedRow = 0;
					}
					else if (mouseScrollPosition.y >= 246 && mouseScrollPosition.y < 346) {
						if (this->selectedRow != 1) {
							Utils::playSound(this->changeSelectionSound);
						}
						this->selectedRow = 1;
					}

					if (this->selectedRow > maxRow) {
						this->selectedRow = maxRow;
					}
				}
				break;
			case OptionControllerState::OtherOptions:
				if (mouseScrollPosition.x > 150 && mouseScrollPosition.x < 475 && mouseScrollPosition.y >= 136 && mouseScrollPosition.y < 236) {
					if (this->selectedRow != 0) {
						Utils::playSound(this->changeSelectionSound);
					}
					this->selectedRow = 0;
				}
				else if (mouseScrollPosition.x > 150 && mouseScrollPosition.x < 850 && mouseScrollPosition.y >= 246 && mouseScrollPosition.y < 346) {
					if (this->selectedRow != 1) {
						Utils::playSound(this->changeSelectionSound);
					}
					this->selectedRow = 1;
				}
				break;
			case OptionControllerState::ConfirmChanges:
				if (mouseScrollPosition.x > 250 && mouseScrollPosition.x < 406 && mouseScrollPosition.y > 450 && mouseScrollPosition.y < 544) {
					if (this->selectedRow != 0) {
						Utils::playSound(this->changeSelectionSound);
					}
					this->selectedRow = 0;
				}
				else if (mouseScrollPosition.x > 594 && mouseScrollPosition.x < 750 && mouseScrollPosition.y > 450 && mouseScrollPosition.y < 544) {
					if (this->selectedRow != 1) {
						Utils::playSound(this->changeSelectionSound);
					}
					this->selectedRow = 1;
				}
				break;
			}
		}
	}
}

//Function to draw a frame
void OptionsController::drawframe() {
	//We draw the background centered. If it's too big, it will fit right so the center of the texture alignes with the center of the screen. If it's too small there will be black borders
	Utils::drawCenteredTextureAt(Position(0, 0), Utils::getScreenWidth(), Utils::getScreenHeight(), this->backgroundTexture);

	//We get the scroll position (Which is in the center of the screen) and draw the scroll
	Position scrollPosition = Utils::getCenteredPosition(Position(0, 0), Utils::getScreenWidth(), Utils::getScreenHeight(), this->backgroundTexture->width, this->backgroundTexture->height);
	this->backgroundTexture->draw(scrollPosition);

	//We now have to draw the text of each scroll. To do that we first need to know which state we currently are in
	switch (this->currentState) {
	case OptionControllerState::NoOption:
		this->drawNoOptions(scrollPosition);
		break;
	case OptionControllerState::GraphicsOptions:
		this->drawGraphicsOptions(scrollPosition);
		break;
	case OptionControllerState::SoundOptions:
		this->drawSoundOptions(scrollPosition);
		break;
	case OptionControllerState::OtherOptions:
		this->drawOtherOptions(scrollPosition);
		break;
	case OptionControllerState::ConfirmChanges:
		this->drawConfirmOptions(scrollPosition);
		break;
	}
}