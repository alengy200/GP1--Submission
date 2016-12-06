/*
=================
cButton.h
- Header file for class definition - SPECIFICATION
- Header file for the Button class which is a child of cSprite class
=================
*/
#ifndef _CBUTTON_H
#define _CBUTTON_H
#include "cSprite.h"

class cButton : public cSprite
{

private:

	SDL_Point buttonClickedRC;
	bool clicked = false;

public:
	cButton(); // Constructor

	//set an update, where can specify what should it do after we clicked on the button
	gameState update(gameState theCurrentGameState, gameState newGameState, SDL_Point theAreaClicked);

	//variables for clicking on the buttons
	bool getClicked();
	void setClicked(bool state);

};
#endif