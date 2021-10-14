#pragma once

#include <iostream>
#include <SDL.h>

#include "Position.h"

//Class that contains a texture to draw on screen. Is created by Loader and used by all kinds of classes.
class Texture {

	public:

		//Renderer of the game
		SDL_Renderer* renderer;

		//Texture per sé
		SDL_Texture* texture;

		//Width and height of the texture
		int width;
		int height;

		//Constructor
		Texture(SDL_Renderer* renderer, SDL_Texture* texture) {
			this->renderer = renderer;
			this->texture = texture;
			SDL_QueryTexture(texture, NULL, NULL, &this->width, &this->height);
		}

		//Destroyer. Only really necessary for textures created by text
		~Texture() {
			//Destroys the texture
			SDL_DestroyTexture(this->texture);
		}

		//Function used to draw the texture on the given screen position.
		//(0,0) is the left-top corner. 
		//(X,0) is on the top but X pixels to the right.
		//(0,Y) is on the left but X pixels down from the top.
		void draw(Position screenPosition){
		
			//Creates the rectangle used to draw the texture
			SDL_Rect rect;

			//Asigns the correct attributes
			rect.h = this->height;
			rect.w = this->width;
			rect.x = screenPosition.x;
			rect.y = screenPosition.y;

			//Renders the texture
			SDL_RenderCopy(this->renderer, this->texture, NULL, &rect);
		}
};