#ifndef _GAME_H
#define _GAME_H

/*
==================================================================================
cGame.h
- Header file for class definition - SPECIFICATION
- Header file for the Game class
==================================================================================
*/

#include <SDL.h>

// Game specific includes
#include "PacmenGame.h"


using namespace std;

class cGame
{
public:
	cGame(); // Constructor

	//main functions in the game
	void initialise(SDL_Window* theSDLWND, SDL_Renderer* theRenderer);
	void run(SDL_Window* theSDLWND, SDL_Renderer* theRenderer);
	void cleanUp(SDL_Window* theSDLWND);
	void render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer);
	void render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer, double rotAngle, SDL_Point* spriteCentre);
	void update();
	void update(double deltaTime);
	bool getInput(bool theLoop);
	double getElapsedSeconds();

	static cGame* getInstance();

private:

	static cGame* pInstance;
	// for framerates
	time_point< high_resolution_clock > m_lastTime;
	time_point< high_resolution_clock > m_CurrentTime;
	duration< double > deltaTime;

	// Sprites for displaying background, Ghost, Pacman and Black textures
	cSprite spriteBkgd;
	cGhost theGhost;
	cPacman thePacman;
	cBlack theBlack;

	// game related variables/vectors
	vector<LPCSTR> textureName;
	vector<LPCSTR> textName;
	vector<LPCSTR> texturesToUse;
	vector<cPacman*> thePacmen;
	// Fonts to use
	vector<LPCSTR> fontList;
	vector<LPCSTR> fontsToUse;
	// Text for Game
	vector<LPCSTR> gameTextList;
	vector<LPCSTR> gameTextNames;
	// Game Sounds
	vector<LPCSTR> soundList;
	vector<soundType> soundTypes;
	vector<LPCSTR> soundsToUse;
	// Create vector array of button textures
	vector<LPCSTR> btnNameList;
	vector<LPCSTR> btnTexturesToUse;
	vector<SDL_Point> btnPos;
	vector <cButton> theButtons;
	// Game objects
	// Define the elements and there position in/on the array/map
	int renderWidth, renderHeight;
	gameState theGameState;
	btnTypes theBtnType;
	SDL_Rect pos;
	FPoint scale;
	SDL_Rect aRect;
	SDL_Color aColour;
	cTexture* tempTextTexture;
	SDL_Point theAreaClicked;
	bool loop;
	bool theLoop;

	//black related variables
	bool black;
	//score related variables
	int theScore;
	string theSScore;
	//timer related variables
	SDL_Surface *seconds = NULL;
	bool running;
	string theTimer;
	double secsTimer;
};

#endif
