/*
=================
cGhost.h
- Header file for class definition - SPECIFICATION
- Header file for the Ghost class which is a child of cSprite class
=================
*/
#ifndef _CGHOST_H
#define _CGHOST_H
#include "cSprite.h"

class cGhost : public cSprite
{
private:
	SDL_Point ghostVelocity;

public:
	cGhost();										// Constructor
	void update(double deltaTime);					// Ghost update method
	void setGhostVelocity(SDL_Point rocketVel);		 // Sets the velocity for the Ghost
	SDL_Point getGhostVelocity();					// Gets the Ghost velocity
};
#endif