/*
==========================================================================
cSoundMgr.h
- Header file for class definition - SPECIFICATION
- Header file for the SoundMgr class
==========================================================================
*/

#ifndef _SOUNDMGR_H
#define _SOUNDMGR_H

// OpenGL Headers
#include "GameConstants.h"
#include "cSound.h"


using namespace std;

class cSoundMgr
{
private:
	static cSoundMgr* pInstance;

protected:
	cSoundMgr(); // Constructor
	~cSoundMgr(); // Destructor.
	map <LPCSTR, cSound*> gameSnds;

public:
	void add(LPCSTR sndName, LPCSTR fileName, soundType sndType);	//add a sound with its name and type
	cSound* getSnd(LPCSTR sndName);				//get a sound from Audio folder
	void deleteSnd();							//delete the sound
	bool initMixer();							// Initialize SDL_Mixer library
	static cSoundMgr* getInstance();			//get instance from the a sound
};
#endif