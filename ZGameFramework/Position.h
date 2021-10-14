#pragma once

#include <math.h>
#include <stdlib.h>

//Used to indicate a position. This can be a position on the map, a position on the screen, a position in a menu, etc.
//Basically represents a classical (X,Y) position. To make it all the same, (0,0) will be always up in the corner, X increases by going right and Y by going down
class Position {

	public:
		//Values of the position
		int x;
		int y;

		//Constructors
		Position() { this->x = 0; this->y = 0; }
		Position(int x, int y) { this->x = x; this->y = y; }

		//Calculates the Manhattan distance to another position. 
		int manhattanDistanceTo(Position position) {
			return abs(this->x - position.x) + abs(this->y - position.y);
		}

		//Calculates the Euclidean distance to another position
		int euclideanDistanceTo(Position position) {
			return sqrt(pow((this->x - position.x),2) + pow((this->y - position.y), 2));
		}

		//Checks if it's the same position
		bool equalTo(Position position) {
			return this->x == position.x && this->y == position.y;
		}
};