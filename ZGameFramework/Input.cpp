#include <fstream>
#include <string>
#include <vector>

#include <SDL.h>

#include "Config.h"
#include "Input.h"
#include "Utils.h"

int Input::upPressedFrames;
int Input::downPressedFrames;
int Input::rightPressedFrames;
int Input::leftPressedFrames;
int Input::selectionPressedFrames;
int Input::backPressedFrames;
int Input::escapePressedFrames;

SDL_Scancode Input::upKeyboardCode;
SDL_Scancode Input::downKeyboardCode;
SDL_Scancode Input::rightKeyboardCode;
SDL_Scancode Input::leftKeyboardCode;
SDL_Scancode Input::selectionKeyboardCode;
SDL_Scancode Input::backKeyboardCode;
SDL_Scancode Input::escapeKeyboardCode;

bool Input::handleMouse;
bool Input::mouseHasMoved;

int Input::mouseX;
int Input::mouseY;
int Input::previousMouseX;
int Input::previousMouseY;
int Input::mouseLeftInputFramesPressed;
int Input::mouseRightInputFramesPressed;

//Constructor
void Input::initInput() {
	//We get the beyboard assignments
	Input::upKeyboardCode = static_cast<SDL_Scancode>(std::atoi(Config::getConfig("UpKeyboardCode").c_str()));
	Input::downKeyboardCode = static_cast<SDL_Scancode>(std::atoi(Config::getConfig("DownKeyboardCode").c_str()));
	Input::rightKeyboardCode = static_cast<SDL_Scancode>(std::atoi(Config::getConfig("RightKeyboardCode").c_str()));
	Input::leftKeyboardCode = static_cast<SDL_Scancode>(std::atoi(Config::getConfig("LeftKeyboardCode").c_str()));
	Input::selectionKeyboardCode = static_cast<SDL_Scancode>(std::atoi(Config::getConfig("SelectionKeyboardCode").c_str()));
	Input::backKeyboardCode = static_cast<SDL_Scancode>(std::atoi(Config::getConfig("BackKeyboardCode").c_str()));
	Input::escapeKeyboardCode = static_cast<SDL_Scancode>(std::atoi(Config::getConfig("EscapeKeyboardCode").c_str()));

	//We set all to not pressed
	Input::upPressedFrames = -1;
	Input::downPressedFrames = -1;
	Input::rightPressedFrames = -1;
	Input::leftPressedFrames = -1;
	Input::selectionPressedFrames = -1;
	Input::backPressedFrames = -1;
	Input::escapePressedFrames = -1;
	Input::mouseLeftInputFramesPressed = -1;
	Input::mouseRightInputFramesPressed = -1;

	//We set them to imposible values to indicate first values
	Input::mouseX = -1;
	Input::mouseY = -1;
	Input::previousMouseY = -1;
	Input::previousMouseX = -1;

	Input::handleMouse = true;
}

//Indicates if a given input has been pressed this frame
//If an input was pressed this frame, it will have 0 as the number of frames beeing pressed
bool Input::inputPressed(InputType input) {
	//We check the input and if it's 0 it means it has beend pressed
	switch (input) {
		case InputType::Up:
			return Input::upPressedFrames == 0;
			break;
		case InputType::Down:
			return Input::downPressedFrames == 0;
			break;
		case InputType::Right:
			return Input::rightPressedFrames == 0;
			break;
		case InputType::Left:
			return Input::leftPressedFrames == 0;
			break;
		case InputType::Selection:
			return Input::selectionPressedFrames == 0;
			break;
		case InputType::Back:
			return Input::backPressedFrames == 0;
			break;
		case InputType::Escape:
			return Input::escapePressedFrames == 0;
			break;
	}
	return false;
}

//Setter
void Input::setHandleMouse(bool handleMouse) {
	Input::handleMouse = handleMouse;
}

//Indicates if a given input is beeing hold
//It is beeing hold if it's beeing pressed more than one frame.
//If so, the counter of frames for a given input is higher than 0.
//(0 once it is pressed, positive once it is hold)
bool Input::inputHold(InputType input) {
	switch (input) {
		case InputType::Up:
			return Input::upPressedFrames > 0;
			break;
		case InputType::Down:
			return Input::downPressedFrames > 0;
			break;
		case InputType::Right:
			return Input::rightPressedFrames > 0;
			break;
		case InputType::Left:
			return Input::leftPressedFrames > 0;
			break;
		case InputType::Selection:
			return Input::selectionPressedFrames > 0;
			break;
		case InputType::Back:
			return Input::backPressedFrames > 0;
			break;
		case InputType::Escape:
			return Input::escapePressedFrames > 0;
			break;
	}
	return false;
}

//Indicates how many frames a input has been hold
int Input::framesHolded(InputType input) {
	switch (input) {
		case InputType::Up:
			return Input::upPressedFrames;
			break;
		case InputType::Down:
			return Input::downPressedFrames;
			break;
		case InputType::Right:
			return Input::rightPressedFrames;
			break;
		case InputType::Left:
			return Input::leftPressedFrames;
			break;
		case InputType::Selection:
			return Input::selectionPressedFrames;
			break;
		case InputType::Back:
			return Input::backPressedFrames;
			break;
		case InputType::Escape:
			return Input::escapePressedFrames;
			break;
	}
	return 0;

}

//Checkes the current input
void Input::updateInput(){

	//We update the input state
	SDL_PumpEvents();

	//If we have to handle the mouse, we have to get the last mouse position
	if (Input::handleMouse) {
		int x;
		int y;
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_MOUSEMOTION:
				{
					Input::mouseX = event.motion.x;
					Input::mouseY = event.motion.y;
					break;
				}
			}
		}
	}

	//We get the keyboard state
	const Uint8* keyboardState = SDL_GetKeyboardState(NULL);

	//Is up beeing pressed?
	if (keyboardState[Input::upKeyboardCode]) {
		Input::upPressedFrames++;
	}
	else {
		Input::upPressedFrames = -1;
	}

	//Is down beeing pressed?
	if (keyboardState[Input::downKeyboardCode]) {
		Input::downPressedFrames++;
	}
	else {
		Input::downPressedFrames = -1;
	}

	//Is right beeing pressed?
	if (keyboardState[Input::rightKeyboardCode]) {
		Input::rightPressedFrames++;
	}
	else {
		Input::rightPressedFrames = -1;
	}

	//Is left beeing pressed?
	if (keyboardState[Input::leftKeyboardCode]) {
		Input::leftPressedFrames++;
	}
	else {
		Input::leftPressedFrames = -1;
	}

	//Is left beeing pressed?
	if (keyboardState[Input::selectionKeyboardCode]) {
		Input::selectionPressedFrames++;
	}
	else {
		Input::selectionPressedFrames = -1;
	}

	//Is left beeing pressed?
	if (keyboardState[Input::backKeyboardCode]) {
		Input::backPressedFrames++;
	}
	else {
		Input::backPressedFrames = -1;
	}

	//Is left beeing pressed?
	if (keyboardState[Input::escapeKeyboardCode]) {
		Input::escapePressedFrames++;
	}
	else {
		Input::escapePressedFrames = -1;
	}

	//We get the mouse state 
	int garbaxeX;
	int garbaxeY;
	Uint32 mouseState = SDL_GetMouseState(&garbaxeX, &garbaxeY);

	//We check if the mouse has moved
	if (Input::mouseX == Input::previousMouseX && Input::mouseY == Input::previousMouseY) {
		Input::mouseHasMoved = false;
	}
	else {
		Input::mouseHasMoved = true;
		Input::previousMouseX = Input::mouseX;
		Input::previousMouseY = Input::mouseY;
	}

	//We check if the mouse buttons are pressed
	if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) {
		Input::mouseLeftInputFramesPressed++;
	}
	else {
		Input::mouseLeftInputFramesPressed = -1;
	}

	if (mouseState & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
		Input::mouseRightInputFramesPressed++;
	}
	else {
		Input::mouseRightInputFramesPressed = -1;
	}
}

//Activates changes produced in configuration
void Input::changeConfiguration() {
	//We get the beyboard assignments
	Input::upKeyboardCode = static_cast<SDL_Scancode>(std::atoi(Config::getConfig("UpKeyboardCode").c_str()));
	Input::downKeyboardCode = static_cast<SDL_Scancode>(std::atoi(Config::getConfig("DownKeyboardCode").c_str()));
	Input::rightKeyboardCode = static_cast<SDL_Scancode>(std::atoi(Config::getConfig("RightKeyboardCode").c_str()));
	Input::leftKeyboardCode = static_cast<SDL_Scancode>(std::atoi(Config::getConfig("LeftKeyboardCode").c_str()));
	Input::selectionKeyboardCode = static_cast<SDL_Scancode>(std::atoi(Config::getConfig("SelectionKeyboardCode").c_str()));
	Input::backKeyboardCode = static_cast<SDL_Scancode>(std::atoi(Config::getConfig("BackKeyboardCode").c_str()));
	Input::escapeKeyboardCode = static_cast<SDL_Scancode>(std::atoi(Config::getConfig("EscapeKeyboardCode").c_str()));
}

//Gets name for that particular input
std::string Input::getNameKeyForInput(InputType input) {
	SDL_Scancode key = SDL_Scancode::SDL_NUM_SCANCODES;
	switch (input) {
		case InputType::Up:
			key = Input::upKeyboardCode;
			break;
		case InputType::Down:
			key = Input::downKeyboardCode;
			break;
		case InputType::Right:
			key = Input::rightKeyboardCode;
			break;
		case InputType::Left:
			key = Input::leftKeyboardCode;
			break;
		case InputType::Selection:
			key = Input::selectionKeyboardCode;
			break;
		case InputType::Back:
			key = Input::backKeyboardCode;
			break;
		case InputType::Escape:
			key = Input::escapeKeyboardCode;
			break;
		}
	return SDL_GetScancodeName(key);
}

//Gets mouse position
Position Input::getMousePosition(){
	return Position(Input::mouseX, Input::mouseY);
}

//Equivalent presses for inputs but for mouse
bool Input::mouseLeftInputPressed() {
	return Input::mouseLeftInputFramesPressed == 0;
}

bool Input::mouseLeftInputHold() {
	return Input::mouseLeftInputFramesPressed > 0;
}

int Input::mouseLeftInputFramesHolded() {
	return Input::mouseLeftInputFramesPressed;
}

bool Input::mouseRightInputPressed() {
	return Input::mouseRightInputFramesPressed == 0;
}

bool Input::mouseRightInputHold() {
	return Input::mouseRightInputFramesPressed > 0;
}

int Input::mouseRightInputFramesHolded() {
	return Input::mouseRightInputFramesPressed;
}

bool Input::mouseMoved() {
	return Input::mouseHasMoved;
}

//Sets an input as pressed
void Input::setInputAsPressed(InputType input) {
	switch (input) {
		case InputType::Up:
			Input::upPressedFrames = 0;
			break;
		case InputType::Down:
			Input::downPressedFrames=0;
			break;
		case InputType::Right:
			Input::rightPressedFrames=0;
			break;
		case InputType::Left:
			Input::leftPressedFrames=0;
			break;
		case InputType::Selection:
			Input::selectionPressedFrames = 0;
			break;
		case InputType::Back:
			Input::backPressedFrames = 0;
			break;
		case InputType::Escape:
			Input::backPressedFrames = 0;
			break;
	}
}