#pragma once

#include <SDL.h>

#include "Position.h"

class Config;
class MainController;

//Enum to classify the possible inputs
enum class InputType {
	Up,
	Right,
	Down,
	Left,
	Selection,
	Back,
	Escape
};

//Class to controll keyboard and mouse input
class Input{
private:
	//How many frames a given input has been pressed. 
	//Special values:
	//	-1: Not beeing pressed
	//	0: Pressed during this frame
	static int upPressedFrames;
	static int downPressedFrames;
	static int rightPressedFrames;
	static int leftPressedFrames;
	static int selectionPressedFrames;
	static int backPressedFrames;
	static int escapePressedFrames;

	//Keyboard assignments
	static SDL_Scancode upKeyboardCode;
	static SDL_Scancode downKeyboardCode;
	static SDL_Scancode rightKeyboardCode;
	static SDL_Scancode leftKeyboardCode;
	static SDL_Scancode selectionKeyboardCode;
	static SDL_Scancode backKeyboardCode;
	static SDL_Scancode escapeKeyboardCode;

	//Current mouse positions
	static int mouseX;
	static int mouseY;

	//Mouse positions in the previous frame
	static int previousMouseX;
	static int previousMouseY;

	//How many frames a given mouse input has been pressed. 
	//Special values:
	//	-1: Not beeing pressed
	//	0: Pressed during this frame
	static int mouseLeftInputFramesPressed;
	static int mouseRightInputFramesPressed;

	//Indicates if the mouse has moved in this frame
	static bool mouseHasMoved;

	//Indicates if the mouse must been handled
	static bool handleMouse;
public:
	//Constructor
	static void initInput();

	//Setter
	static void setHandleMouse(bool handleMouse);

	//Indicates if a given input has been pressed this frame
	static bool inputPressed(InputType input);

	//Indicates if a given input is beeing hold
	static bool inputHold(InputType input);

	//Indicates how many frames a input has been hold
	static int framesHolded(InputType input);

	//Checkes the current input
	static void updateInput();

	//Activates changes produced in configuration
	static void changeConfiguration();

	//Gets name for that particular input
	static std::string getNameKeyForInput(InputType input);

	//Gets mouse position
	static Position getMousePosition();

	//Indicates if the mouse has moved
	static bool mouseMoved();
	
	//Equivalent presses for inputs but for mouse
	static bool mouseLeftInputPressed();
	static bool mouseLeftInputHold();
	static int mouseLeftInputFramesHolded();

	static bool mouseRightInputPressed();
	static bool mouseRightInputHold();
	static int mouseRightInputFramesHolded();

	//Sets an input as pressed
	static void setInputAsPressed(InputType input);
};