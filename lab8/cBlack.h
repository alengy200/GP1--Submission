/*
=================
cBlack.h
- Header file for class definition - SPECIFICATION
- Header file for the Black class which is a child of cSprite class
=================
*/
#ifndef _CBLACK_H
#define _CBLACK_H
#include "cSprite.h"

class cBlack : public cSprite
{
private:
	SDL_Point blackVelocity;

public:
	cBlack(); // Constructor
	void update(double deltaTime);		// Black update method
	void setBlackVelocity(SDL_Point blackVel);   // Sets the velocity for the Black
	SDL_Point getBlackVelocity();				 // Gets the Black velocity
};
#endif