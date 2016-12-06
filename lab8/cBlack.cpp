/*
=================
cBlack.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cBlack.h"

/*
=================================================================
Defualt Constructor
=================================================================
*/
cBlack::cBlack() : cSprite()
{
	this->blackVelocity = { 0.0f, 0.0f };
}
/*
=================================================================
Update the sprite position
=================================================================
*/

void cBlack::update(double deltaTime)
{

	FPoint direction = { 0.0f, 0.0f };
	direction.X = (sin(this->getSpriteRotAngle()*PI / 180));
	direction.Y = -(cos(this->getSpriteRotAngle()*PI / 180));

	direction.X *= this->getSpriteTranslation().x;
	direction.Y *= this->getSpriteTranslation().y;

	this->blackVelocity.x = this->blackVelocity.x + direction.X;
	this->blackVelocity.y = this->blackVelocity.y + direction.Y;

	SDL_Rect currentSpritePos = this->getSpritePos();
	currentSpritePos.x += this->blackVelocity.x * deltaTime;
	currentSpritePos.y += this->blackVelocity.y * deltaTime;

	this->blackVelocity.x *= 0.95;
	this->blackVelocity.y *= 0.95;

	this->setSpritePos({ currentSpritePos.x, currentSpritePos.y });
	this->setBoundingRect(this->getSpritePos());
}
/*
=================================================================
Sets the velocity for the black
=================================================================
*/
void cBlack::setBlackVelocity(SDL_Point rocketVel)
{
	blackVelocity = rocketVel;
}
/*
=================================================================
Gets the black velocity
=================================================================
*/
SDL_Point cBlack::getBlackVelocity()
{
	return blackVelocity;
}

