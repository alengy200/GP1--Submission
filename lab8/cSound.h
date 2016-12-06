/*
==========================================================================
cSound.h
- Header file for class definition - SPECIFICATION
- Header file for the Sound class
==========================================================================
*/

#ifndef _SOUND_H
#define _SOUND_H

// OpenGL Headers
#include "GameConstants.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class cSound
{
private:

	Mix_Chunk * SoundFX = NULL;
	Mix_Music * sMusic = NULL;
	soundType theSoundType;

public:
	cSound(); // Constructor
	cSound(soundType sndType); // Constructor
	~cSound(); // Destructor.

	bool load(LPCSTR filename);  //load the sound from the Audio folder
	void setSoundTYpe(soundType sndType); //set sound type
	soundType getSoundType(); //get the soundtype
	void play(int loop);  //play the sound and set a loop for it (how many times is it playing)
};
#endif