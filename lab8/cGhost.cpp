/*
=================
cGhost.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cGhost.h"

/*
=================================================================
Defualt Constructor
=================================================================
*/
cGhost::cGhost() : cSprite()
{
	this->ghostVelocity = { 0.0f, 0.0f };
}
/*
=================================================================
Update the sprite position
=================================================================
*/

void cGhost::update(double deltaTime)
{

	FPoint direction = { 0.0f, 0.0f };
	direction.X = (sin(this->getSpriteRotAngle()*PI / 180));
	direction.Y = -(cos(this->getSpriteRotAngle()*PI / 180));

	direction.X *= this->getSpriteTranslation().x;
	direction.Y *= this->getSpriteTranslation().y;

	this->ghostVelocity.x = this->ghostVelocity.x + direction.X;
	this->ghostVelocity.y = this->ghostVelocity.y + direction.Y;

	SDL_Rect currentSpritePos = this->getSpritePos();
	currentSpritePos.x += this->ghostVelocity.x * deltaTime * 20;
	currentSpritePos.y += this->ghostVelocity.y * deltaTime * 20;

	this->ghostVelocity.x *= 0.95;
	this->ghostVelocity.y *= 0.95;
	
	this->setSpritePos({ currentSpritePos.x , currentSpritePos.y  });
	this->setBoundingRect(this->getSpritePos());
}
/*
=================================================================
Sets the velocity for the ghost
=================================================================
*/
void cGhost::setGhostVelocity(SDL_Point rocketVel)
{
	ghostVelocity = rocketVel;
}
/*
=================================================================
Gets the ghost velocity
=================================================================
*/
SDL_Point cGhost::getGhostVelocity()
{
	return ghostVelocity;
}
