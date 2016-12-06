/*
==========================================================================
cFont.h
- Header file for class definition - SPECIFICATION
- Header file for the Font class
==========================================================================
*/

#ifndef _CFONT_H
#define _CFONT_H

// OpenGL Headers, using gameConstants header file
#include "GameConstants.h"

using namespace std;

class cFont
{
private:
	TTF_Font* theFont;

//set variables return a font and to create a text with a font type with texture
public:
	cFont();														// Constructor
	~cFont();														// Destructor.
	bool loadFont(LPCSTR fontFileName, int fontSize);
	TTF_Font* getFont();											//Initialise the SDL ttf library
	SDL_Texture* createTextTexture(SDL_Renderer* theRenderer, LPCSTR text, textType txtType, SDL_Color txtColour, SDL_Color txtBkgd);
};
#endif