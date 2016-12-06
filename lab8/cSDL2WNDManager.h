#ifndef _SDL2WNDMANAGER_H
#define _SDL2WNDMANAGER_H

/*
==================================================================================
cSDL2WNDManager.h

- Header file for the SDL2WNDManager class
==================================================================================
*/
#include <SDL.h>
#include <string>
#include <iostream>

using namespace std;

class cSDL2WNDManager
{
public:
	cSDL2WNDManager();											 // Constructor

	bool initWND(string strWNDTitle, int iWidth, int iHeight); //initialise a window with a title and the size of it
	void CheckSDLError(int line);			//checking for errors with their lines
	SDL_Window* getSDLWindow();				//get a window for SDL
	SDL_GLContext getSDL_GLContext();		//get the SDL context informations
	SDL_Renderer* getSDLRenderer();			//get the SDL renderer informations

	static cSDL2WNDManager* getInstance();

private:

	static cSDL2WNDManager* pInstance;
	SDL_Window *mainWindow;
	SDL_GLContext mainContext;
	SDL_Renderer* theRenderer;

};

#endif

