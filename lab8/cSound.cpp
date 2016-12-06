/*
==========================================================================
cSound.cpp
==========================================================================
*/
//#pragma warning ( disable : 4996 )
#include "cSound.h"
using namespace std;

/*
==========================================================================
Default Constructor
==========================================================================
*/

cSound::cSound()
{
	this->theSoundType = SFX;
}
cSound::cSound(soundType sndType)
{
	this->theSoundType = sndType;
}

/*
==========================================================================
Destructor
==========================================================================
*/
cSound::~cSound()
{
}

/*
==========================================================================
Load the desiered sound
==========================================================================
*/
bool cSound::load(LPCSTR filename)
{
	switch (this->theSoundType)
	{
		case SFX:
		{
			this->SoundFX = Mix_LoadWAV(filename);
			if (this->SoundFX != 0)
			{
				cout << "Sound FX '" << filename << "' could not be loaded. " << SDL_GetError() << endl;
				return false;
			}
			return true;
		}
		break;
		case MUSIC:
		{
			this->sMusic = Mix_LoadMUS(filename);
			if (this->sMusic != 0)
			{
				cout << "Music '" << filename << "' could not be loaded. " << SDL_GetError() << endl;
				return false;
			}
			return true;
		}
		break;
		default:
			return false;
	}
}

//play the sound according to its type
void cSound::play(int loop)
{
	switch (this->theSoundType)
	{
		case SFX:
		{
			Mix_PlayChannel(-1, this->SoundFX, loop);
		}
		break;
		case MUSIC:
		{
			Mix_PlayMusic(this->sMusic, loop);
		}
		break;
		default:
			break;
	}
}
