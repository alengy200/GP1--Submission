/*
==================================================================================
cGame.cpp
==================================================================================
*/
#include "cGame.h"

cGame* cGame::pInstance = NULL;
static cTextureMgr* theTextureMgr = cTextureMgr::getInstance();
static cFontMgr* theFontMgr = cFontMgr::getInstance();
static cSoundMgr* theSoundMgr = cSoundMgr::getInstance();
static cButtonMgr* theButtonMgr = cButtonMgr::getInstance(); 

//gives an empty value for the seconds
SDL_Surface *seconds = NULL;


/*
=================================================================================
Constructor
=================================================================================
*/
cGame::cGame()
{

}
/*
=================================================================================
Singleton Design Pattern
=================================================================================
*/
cGame* cGame::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new cGame();
	}
	return cGame::pInstance;
}

//initialise function
void cGame::initialise(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	// Get width and height of render context
	SDL_GetRendererOutputSize(theRenderer, &renderWidth, &renderHeight);
	this->m_lastTime = high_resolution_clock::now();
	// Clear the buffer with a black background
	SDL_SetRenderDrawColor(theRenderer, 0, 0, 0, 255);
	SDL_RenderPresent(theRenderer);
	theScore = 0; //set the score to 0
	theTextureMgr->setRenderer(theRenderer);
	theFontMgr->initFontLib();  //get the fonts from the Font library
	theSoundMgr->initMixer();	//get the sounds from the Sounds library

	//The timer starting time
	secsTimer = 10.0f;
	
	//Set the initial coordinates of mouse clicked
	theAreaClicked = { 0, 0 };

	// Store the textures
	textureName = { "theGhost","theBackground", "thePacman", "theBlack"};
	texturesToUse = { "Images\\ghost.png", "Images\\maze1024x688.png", "Images\\pacman.png", "Images\\black.png"};
	for (int tCount = 0; tCount < textureName.size(); tCount++)
	{	
		theTextureMgr->addTexture(textureName[tCount], texturesToUse[tCount]);
	}
	//Store the buttons
	btnNameList = { "exit_btn", "giveup_btn", "load_btn", "menu_btn", "play_btn", "save_btn", "settings_btn" };
	btnTexturesToUse = { "Images/Buttons/button_exit.png", "Images/Buttons/button_giveup.png", "Images/Buttons/button_load.png", "Images/Buttons/button_menu.png", "Images/Buttons/button_play1.png", "Images/Buttons/button_save.png", "Images/Buttons/button_settings.png" };
	btnPos = { { 400, 375 }, { 400, 300 }, { 400, 300 }, { 500, 500 }, { 400, 300 }, { 740, 500 }, { 400, 300 } };
	for (int bCount = 0; bCount < btnNameList.size(); bCount++)
	{
		theTextureMgr->addTexture(btnNameList[bCount], btnTexturesToUse[bCount]);
	}
	for (int bCount = 0; bCount < btnNameList.size(); bCount++)
	{
		//Create a Button
		cButton * newBtn = new cButton();
		newBtn->setTexture(theTextureMgr->getTexture(btnNameList[bCount]));
		newBtn->setSpritePos(btnPos[bCount]);
		newBtn->setSpriteDimensions(theTextureMgr->getTexture(btnNameList[bCount])->getTWidth(), theTextureMgr->getTexture(btnNameList[bCount])->getTHeight());
		theButtonMgr->add(btnNameList[bCount], newBtn);
	}

	// Create textures for Game Dialogue (text), get the fonts from the Font library
	fontList = { "arcade" };
	fontsToUse = { "Fonts/arcade.ttf" };
	for (int fonts = 0; fonts < fontList.size(); fonts++)
	{
		theFontMgr->addFont(fontList[fonts], fontsToUse[fonts], 42); // 42 = font size
	}
	//texts
	gameTextList = { "Good Bye Pacman", "Score ", "Get all the dead Pacmen bodies", "you have 10 second to see the map push space for it!", " Congratulation your", "Time Left " };
	//Add textures to the texts
	theTextureMgr->addTexture("Title", theFontMgr->getFont("arcade")->createTextTexture(theRenderer, gameTextList[0], SOLID, { 255, 255, 0 }, { 0, 0, 0, 0 }));
	theTextureMgr->addTexture("Score", theFontMgr->getFont("arcade")->createTextTexture(theRenderer, gameTextList[1], SOLID, { 255, 255, 255, 255 }, { 0, 0, 0, 0 }));
	theTextureMgr->addTexture("Rules1", theFontMgr->getFont("arcade")->createTextTexture(theRenderer, gameTextList[2], SOLID, { 255, 255, 255, 255 }, { 0, 0, 0, 0 }));
	theTextureMgr->addTexture("Rules2", theFontMgr->getFont("arcade")->createTextTexture(theRenderer, gameTextList[3], SOLID, { 255, 255, 255, 255 }, { 0, 0, 0, 0 }));
	theTextureMgr->addTexture("Congrat", theFontMgr->getFont("arcade")->createTextTexture(theRenderer, gameTextList[4], SOLID, { 255, 255, 255, 255 }, { 0, 0, 0, 0 }));
	theTextureMgr->addTexture("Timer", theFontMgr->getFont("arcade")->createTextTexture(theRenderer, gameTextList[5], SOLID, { 255, 255, 255, 255 }, { 0, 0, 0, 0 }));

	// Load game sounds
	soundList = { "theme", "pickUp", "intro", "map", "button" };
	soundTypes = { MUSIC, SFX, SFX, SFX, SFX };
	soundsToUse = { "Audio/Original.mp3", "Audio/deadPacman.wav", "Audio/intromusic.mp3", "Audio/map.mp3", "Audio/button.wav" };
	for (int sounds = 0; sounds < soundList.size(); sounds++)
	{
		theSoundMgr->add(soundList[sounds], soundsToUse[sounds], soundTypes[sounds]);
	}

	//set the objects texutres, positions, dimensions and scale

	spriteBkgd.setSpritePos({ 0, 0 });
	spriteBkgd.setTexture(theTextureMgr->getTexture("theBackground"));
	spriteBkgd.setSpriteDimensions(theTextureMgr->getTexture("theBackground")->getTWidth(), theTextureMgr->getTexture("theBackground")->getTHeight());

	theGhost.setSpritePos({ 15, 385 });
	theGhost.setTexture(theTextureMgr->getTexture("theGhost"));
	theGhost.setSpriteDimensions(theTextureMgr->getTexture("theGhost")->getTWidth(), theTextureMgr->getTexture("theGhost")->getTHeight());
	theGhost.setGhostVelocity({ 0, 0 });

	thePacman.setSpritePos({ 470, 160 });
	thePacman.setTexture(theTextureMgr->getTexture("thePacman"));
	thePacman.setSpriteDimensions(theTextureMgr->getTexture("thePacman")->getTWidth(), theTextureMgr->getTexture("thePacman")->getTHeight());
	thePacman.setPacmanVelocity({ 0, 0 });

	theBlack.setSpritePos({ 0, 0 });
	theBlack.setTexture(theTextureMgr->getTexture("theBlack"));
	theBlack.setSpriteDimensions(theTextureMgr->getTexture("theBlack")->getTWidth(), theTextureMgr->getTexture("theBlack")->getTHeight());
	theBlack.setBlackVelocity({ 0, 0 });

	// Create vector array of textures and set the pacman object to random positions with their textures, dimensions and scales

	for (int pac = 0; pac < 5; pac++)
	{
		thePacmen.push_back(new cPacman);
		thePacmen[pac]->setSpritePos({ 92 * (rand() % 10), 60 * (rand() % 10 + 1) });
		thePacmen[pac]->setTexture(theTextureMgr->getTexture("thePacman"));
		thePacmen[pac]->setSpriteDimensions(theTextureMgr->getTexture("thePacman")->getTWidth(), theTextureMgr->getTexture("thePacman")->getTHeight());
		thePacmen[pac]->setPacmanVelocity({ 0, 0 });
		thePacmen[pac]->setActive(true);
	}
}


//run function
void cGame::run(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	//the game starts running
	loop = true;

	while (loop)
	{
		//We get the time that passed since the last frame
		double elapsedTime = this->getElapsedSeconds();
		//update the game after every frame and render it
		loop = this->getInput(loop);
		this->update(elapsedTime);
		this->render(theSDLWND, theRenderer);
	}
}

//render function
void cGame::render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	SDL_RenderClear(theRenderer);
	switch (theGameState)
	{
		//on the menu scene this is happening
	case MENU: 
	{
		//play the intro sound once
		theSoundMgr->getSnd("intro")->play(0);
		
		// Render the Title
		cTexture* tempTextTexture = theTextureMgr->getTexture("Title");
		SDL_Rect pos = { 350, 80, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		FPoint scale = { 1, 1 };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);


		// Render the Rules1
		cTexture* tempTextTextureRules1 = theTextureMgr->getTexture("Rules1");
		SDL_Rect pos3 = { 180, 300, tempTextTextureRules1->getTextureRect().w, tempTextTextureRules1->getTextureRect().h };
		FPoint scale3 = { 1, 1 };
		tempTextTextureRules1->renderTexture(theRenderer, tempTextTextureRules1->getTexture(), &tempTextTextureRules1->getTextureRect(), &pos3, scale3);

		// Render the Rules2
		cTexture* tempTextTextureRules2 = theTextureMgr->getTexture("Rules2");
		SDL_Rect pos4 = { 30, 340, tempTextTextureRules2->getTextureRect().w, tempTextTextureRules2->getTextureRect().h };
		FPoint scale4 = { 1, 1 };
		tempTextTextureRules2->renderTexture(theRenderer, tempTextTextureRules2->getTexture(), &tempTextTextureRules2->getTextureRect(), &pos4, scale4);
		
		// Render play and exit button
		theButtonMgr->getBtn("play_btn")->setSpritePos({ 400, 500 });
		theButtonMgr->getBtn("play_btn")->render(theRenderer, &theButtonMgr->getBtn("play_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("play_btn")->getSpritePos(), theButtonMgr->getBtn("play_btn")->getSpriteScale());
		theButtonMgr->getBtn("exit_btn")->setSpritePos({ 400, 570 });
		theButtonMgr->getBtn("exit_btn")->render(theRenderer, &theButtonMgr->getBtn("exit_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("exit_btn")->getSpritePos(), theButtonMgr->getBtn("exit_btn")->getSpriteScale());
		
		//render a pacman
		thePacman.render(theRenderer, &thePacman.getSpriteDimensions(), &thePacman.getSpritePos(), thePacman.getSpriteRotAngle(), &thePacman.getSpriteCentre(), thePacman.getSpriteScale());

	}
	break;

	//this is happening on the playing scene
	case PLAYING:
	{
		//render black
		theBlack.render(theRenderer, &theBlack.getSpriteDimensions(), &theBlack.getSpritePos(), theBlack.getSpriteRotAngle(), &theBlack.getSpriteCentre(), theBlack.getSpriteScale());

	
	
	// Render Pacmen if the black is on
	
		if (black == true)
		{
			spriteBkgd.render(theRenderer, NULL, NULL, spriteBkgd.getSpriteScale());

				// Render each pacman in the vector array
				for (int draw = 0; draw < thePacmen.size(); draw++)
				{
					thePacmen[draw]->render(theRenderer, &thePacmen[draw]->getSpriteDimensions(), &thePacmen[draw]->getSpritePos(), thePacmen[draw]->getSpriteRotAngle(), &thePacmen[draw]->getSpriteCentre(), thePacmen[draw]->getSpriteScale());
				}
				
			// render the ghost
			theGhost.render(theRenderer, &theGhost.getSpriteDimensions(), &theGhost.getSpritePos(), theGhost.getSpriteRotAngle(), &theGhost.getSpriteCentre(), theGhost.getSpriteScale());
		}
	
	//Render the Score
	theTextureMgr->addTexture("Score", theFontMgr->getFont("arcade")->createTextTexture(theRenderer, theSScore.c_str(), SOLID, { 255, 0, 0 }, { 0, 0, 0, 0 }));

	cTexture* tempTextTextureScore = theTextureMgr->getTexture("Score");
	SDL_Rect pos2 = { 800, 10, tempTextTextureScore->getTextureRect().w, tempTextTextureScore->getTextureRect().h };
	FPoint scale2 = { 1, 1 };
	tempTextTextureScore->renderTexture(theRenderer, tempTextTextureScore->getTexture(), &tempTextTextureScore->getTextureRect(), &pos2, scale2);

	// Render the Timer
	theTextureMgr->addTexture("Timer", theFontMgr->getFont("arcade")->createTextTexture(theRenderer, theTimer.c_str(), SOLID, { 255, 0, 0 }, { 0, 0, 0, 0 }));

	cTexture* tempTextTextureTimer = theTextureMgr->getTexture("Timer");
	SDL_Rect pos7 = { 350, 10, tempTextTextureTimer->getTextureRect().w, tempTextTextureTimer->getTextureRect().h };
	FPoint scale7 = { 1, 1 };
	tempTextTextureTimer->renderTexture(theRenderer, tempTextTextureTimer->getTexture(), &tempTextTextureTimer->getTextureRect(), &pos7, scale7);

	//render give up button
	theButtonMgr->getBtn("giveup_btn")->setSpritePos({ 10, 0 });
	theButtonMgr->getBtn("giveup_btn")->render(theRenderer, &theButtonMgr->getBtn("giveup_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("giveup_btn")->getSpritePos(), theButtonMgr->getBtn("giveup_btn")->getSpriteScale());

	}
	break;
	//this is happening on the end scene
	case END:
	{

		//Render the Score
		cTexture* tempTextTextureScore = theTextureMgr->getTexture("Score");
		SDL_Rect pos6 = { 400, 275, tempTextTextureScore->getTextureRect().w, tempTextTextureScore->getTextureRect().h };
		FPoint scale6 = { 1, 1 };
		tempTextTextureScore->renderTexture(theRenderer, tempTextTextureScore->getTexture(), &tempTextTextureScore->getTextureRect(), &pos6, scale6);

		// Render the Congrats
		cTexture* tempTextTextureCong = theTextureMgr->getTexture("Congrat");
		SDL_Rect pos5 = { 275, 200, tempTextTextureCong->getTextureRect().w, tempTextTextureCong->getTextureRect().h };
		FPoint scale5 = { 1, 1 };
		tempTextTextureCong->renderTexture(theRenderer, tempTextTextureCong->getTexture(), &tempTextTextureCong->getTextureRect(), &pos5, scale5);


		//render menu and exit buttons
		theButtonMgr->getBtn("menu_btn")->setSpritePos({ 400, 550});
		theButtonMgr->getBtn("menu_btn")->render(theRenderer, &theButtonMgr->getBtn("menu_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("menu_btn")->getSpritePos(), theButtonMgr->getBtn("menu_btn")->getSpriteScale());
		theButtonMgr->getBtn("exit_btn")->setSpritePos({ 405, 625 });
		theButtonMgr->getBtn("exit_btn")->render(theRenderer, &theButtonMgr->getBtn("exit_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("exit_btn")->getSpritePos(), theButtonMgr->getBtn("exit_btn")->getSpriteScale());

	}
	break;
	//this is happening on the quit scene
	case QUIT:
	{
		//the window closes
		loop = false;
	}
	break;
	default:
		break;
	}
	//render everything
	SDL_RenderPresent(theRenderer);

}
//render function
void cGame::render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer, double rotAngle, SDL_Point* spriteCentre)
{

	SDL_RenderPresent(theRenderer);
}
//update function
void cGame::update()
{

}

//update function
void cGame::update(double deltaTime)
{

	
	// CHeck Button clicked and change state
	if (theGameState == MENU || theGameState == END)
	{
		theGameState = theButtonMgr->getBtn("exit_btn")->update(theGameState, QUIT, theAreaClicked);
		theGameState = theButtonMgr->getBtn("play_btn")->update(theGameState, PLAYING, theAreaClicked);
		theGameState = theButtonMgr->getBtn("menu_btn")->update(theGameState, MENU, theAreaClicked);
		theAreaClicked = { 0, 0 };
	}
	else
	{
		theGameState = theButtonMgr->getBtn("exit_btn")->update(theGameState, END, theAreaClicked);
		theGameState = theButtonMgr->getBtn("giveup_btn")->update(theGameState, END, theAreaClicked);
		theAreaClicked = { 0, 0 };
	}
	
	//if the current scene is playing
	if (theGameState == PLAYING)
	{
		//if the timer goes below 1, change the game state to end and stop the timer
		cout << "Timer: " << secsTimer;

		if ((int)secsTimer < 1.0f)
		{
			theGameState = END;
		}
		
		//if the game state goes to end
		if (theGameState == END)
		{
			//stop the timer
			running = false;
			//set back the timer
			secsTimer = 10;
			//set back the ghost's position
			theGhost.setSpritePos({ 15, 385 }); 
		}

		///If the timer is running
		if (running == true)
		{
			//The timer's time as a string
			string time;
			//time minus deltatime time
			secsTimer -= deltaTime;
			//Convert the timer's time to a string
			time = to_string((int)(secsTimer));

			//add the string next to the Timer text
			theTimer = gameTextList[5] + time;
			theTextureMgr->deleteTexture("Timer");
		}

		// Update the visibility and position of each pacmen
		vector<cPacman*>::iterator pacmanIterator = thePacmen.begin();
		while (pacmanIterator != thePacmen.end())
		{
			if ((*pacmanIterator)->isActive() == false)
			{
				pacmanIterator = thePacmen.erase(pacmanIterator);
			}
			else
			{
				(*pacmanIterator)->update(deltaTime);
				++pacmanIterator;
			}
		}
	
		/*
		==============================================================
		| Check for collisions
		==============================================================
		*/
		
		for (vector<cPacman*>::iterator pacmanIterartor = thePacmen.begin(); pacmanIterartor != thePacmen.end(); ++pacmanIterartor)
		{
			if ((*pacmanIterartor)->collidedWith(&(*pacmanIterartor)->getBoundingRect(), &theGhost.getBoundingRect()))
			{
				// if a collision set the ghost and pacman to false
				(*pacmanIterartor)->setActive(false);
				//play pickup sound effect once
				theSoundMgr->getSnd("pickUp")->play(0);
				//add one score
				theScore++;
				//update the score string
				theSScore = gameTextList[1] + to_string(theScore);
				theTextureMgr->deleteTexture("Score");
			}
		}

		// Update the ghost position
		theGhost.update(deltaTime);

		//if the numbers of the pacmen is 0
		if (thePacmen.size() == 0)
		{
			//goes to the end scene
			theGameState = END;
			//stop the timer
			running = false;
			//set back the timer
			secsTimer = 10;
			//set back the ghost's position
			theGhost.setSpritePos({ 15, 385 });

			// Create vector array of textures and set the pacman object to random positions with their textures, dimensions and scales
			//set back the pacmen
			for (int pac = 0; pac < 5; pac++)
			{
				thePacmen.push_back(new cPacman);
				thePacmen[pac]->setSpritePos({ 92 * (rand() % 10), 60 * (rand() % 10 + 1) });
				thePacmen[pac]->setTexture(theTextureMgr->getTexture("thePacman"));
				thePacmen[pac]->setSpriteDimensions(theTextureMgr->getTexture("thePacman")->getTWidth(), theTextureMgr->getTexture("thePacman")->getTHeight());
				thePacmen[pac]->setPacmanVelocity({ 0, 0 });
				thePacmen[pac]->setActive(true);
			}
			theAreaClicked = { 0, 0 };
		}

	}
}
//input function
bool cGame::getInput(bool theLoop)
{
	//joystick input
	SDL_JOYSTICK_XINPUT;

	//keyboard input
	const Uint8 *keys = SDL_GetKeyboardState(NULL);
	SDL_Event event;
	
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			theLoop = false;
		}

		switch (event.type)
		{
			//mouse button input
		case SDL_MOUSEBUTTONDOWN:
			switch (event.button.button)
			{
				case SDL_BUTTON_LEFT:
				{
					theAreaClicked = { event.motion.x, event.motion.y };
				}
			}
			break;

		case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
						//escape button input
					case SDLK_ESCAPE:
						theLoop = false;
						break;
						//down arrow input
					case SDLK_DOWN:
					{
						if (theGhost.getSpritePos().y < (renderWidth - theGhost.getSpritePos().w))
						{
							theGhost.setGhostVelocity({ 0, 5 });
						}
					}
					break;
					//up arrow input
					case SDLK_UP:
					{
						if (theGhost.getSpritePos().y < (renderWidth - theGhost.getSpritePos().w))
						{
							theGhost.setGhostVelocity({ 0, -5 });
						}
					}
					break;
					//right arrow input
					case SDLK_RIGHT:
					{
						if (theGhost.getSpritePos().x < (renderWidth - theGhost.getSpritePos().w))
						{
							theGhost.setGhostVelocity({ 5, 0 });
						}
					}
					break;
					//left arrow input
					case SDLK_LEFT:
					{
						if (theGhost.getSpritePos().x < (renderWidth - theGhost.getSpritePos().w))
						{
							theGhost.setGhostVelocity({ -5, 0 });
						}
					}
					break;
					//space bar input
					case SDLK_SPACE:
					{
						//black shows up
   						black = true;
						//map sound effect playes once						
						theSoundMgr->getSnd("map")->play(0);
						
					}
					break;
					default:
						break;
					}

		//when you stop holding down the space bar
		case SDL_KEYUP:
			switch (event.key.keysym.sym)
			{
			case SDLK_SPACE:
			{
				//black is off
   				black = false;
				//timer pause
				running = false;

				
			}
			break;
			default:
				break;

			}

					default:
					break;
				}

		//when the space is under press
		if (keys[SDL_SCANCODE_SPACE])
		{
			//black is on
			black = true;
			
			//If the timer is running
			if (running == true)
			{
				//Stop the timer
				running = false;
			}
			else
			{
				//Start the timer
				running = true;

			}
		}
		
	}
	return theLoop;
	
}
//elapsed seconds function
double cGame::getElapsedSeconds()
{
	//checking for time
	this->m_CurrentTime = high_resolution_clock::now();
	this->deltaTime = (this->m_CurrentTime - this->m_lastTime);
	this->m_lastTime = this->m_CurrentTime;
	return deltaTime.count();
}
//clean up function
void cGame::cleanUp(SDL_Window* theSDLWND)
{
	// Delete our OpengL context
	SDL_GL_DeleteContext(theSDLWND);

	// Destroy the window
	SDL_DestroyWindow(theSDLWND);

	// Quit IMG system
	IMG_Quit();

	// Shutdown SDL 2
	SDL_Quit();
}