/*
=================
cRocket.h
- Header file for class definition - SPECIFICATION
- Header file for the Pacman class which is a child of cSprite class
=================
*/
#ifndef _CPACMAN_H
#define _CPACMAN_H
#include "cSprite.h"

class cPacman : public cSprite
{
private:
	SDL_Point pacmanVelocity;

public:
	cPacman();										// Constructor
	void update(double deltaTime);					// Rocket update method
	void setPacmanVelocity(SDL_Point blackVel);   // Sets the velocity for the rocket
	SDL_Point getPacmanVelocity();				 // Gets the rocket velocity
};
#endif