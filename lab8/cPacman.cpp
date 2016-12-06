/*
=================
cPacman.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cPacman.h"

/*
=================================================================
Defualt Constructor
=================================================================
*/
cPacman::cPacman() : cSprite()
{
	this->pacmanVelocity = { 0.0f, 0.0f };
}
/*
=================================================================
Update the sprite position
=================================================================
*/

void cPacman::update(double deltaTime)
{

	FPoint direction = { 0.0f, 0.0f };
	direction.X = (sin(this->getSpriteRotAngle()*PI / 180));
	direction.Y = -(cos(this->getSpriteRotAngle()*PI / 180));

	direction.X *= this->getSpriteTranslation().x;
	direction.Y *= this->getSpriteTranslation().y;

	this->pacmanVelocity.x = this->pacmanVelocity.x + direction.X;
	this->pacmanVelocity.y = this->pacmanVelocity.y + direction.Y;

	SDL_Rect currentSpritePos = this->getSpritePos();
	currentSpritePos.x += this->pacmanVelocity.x * deltaTime;
	currentSpritePos.y += this->pacmanVelocity.y * deltaTime;

	this->pacmanVelocity.x *= 0.95;
	this->pacmanVelocity.y *= 0.95;

	this->setSpritePos({ currentSpritePos.x, currentSpritePos.y });
	this->setBoundingRect(this->getSpritePos());
}
/*
=================================================================
Sets the velocity for the pacman
=================================================================
*/
void cPacman::setPacmanVelocity(SDL_Point rocketVel)
{
	pacmanVelocity = rocketVel;
}
/*
=================================================================
Gets the pacman velocity
=================================================================
*/
SDL_Point cPacman::getPacmanVelocity()
{
	return pacmanVelocity;
}
