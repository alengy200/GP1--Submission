/*
==================================================================================
cSoundMgr.cpp
==================================================================================
*/

#include "cSoundMgr.h"

cSoundMgr* cSoundMgr::pInstance = NULL;

/*
=================================================================================
Constructor
=================================================================================
*/
cSoundMgr::cSoundMgr()
{

}

/*
=================================================================================
Singleton Design Pattern
=================================================================================
*/
cSoundMgr* cSoundMgr::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new cSoundMgr();
	}
	return cSoundMgr::pInstance;
}


// add sound to the Sound collection
void cSoundMgr::add(LPCSTR sndName, LPCSTR fileName, soundType sndType)
{
	if (!getSnd(sndName))
	{
		cSound * newSnd = new cSound(sndType);
		newSnd->load(fileName);
		gameSnds.insert(make_pair(sndName, newSnd));
	}
}


// return the sound for use
cSound* cSoundMgr::getSnd(LPCSTR sndName)
{
	map<LPCSTR, cSound*>::iterator snd = gameSnds.find(sndName);
	if (snd != gameSnds.end())
	{
		return snd->second;
	}
	else
	{
		return NULL;
	}
}


//delete the sound
void cSoundMgr::deleteSnd()
{
	for (map<LPCSTR, cSound*>::iterator snd = gameSnds.begin(); snd != gameSnds.end(); ++snd)
	{
		delete snd->second;
	}
}

// Initialize SDL_Mixer library
bool cSoundMgr::initMixer()
{
	if (SDL_Init(SDL_INIT_AUDIO) != 0)
	{
		cout << "SDL_Init_AUDIO Failed: " << SDL_GetError() << endl;
		return false;
	}
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) != 0)
	{
		cout << "Mix_OpenAudio Failed: " << SDL_GetError() << endl;
		return false;
	}

	return true;
}


// Destructor
cSoundMgr::~cSoundMgr()
{
	deleteSnd();
	Mix_CloseAudio();
	Mix_Quit();
}
