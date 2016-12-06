
/*
==========================================================================
cSoundMgr.h
- Header file for class definition - SPECIFICATION
- Header file for the ButtonMgr class
==========================================================================
*/

#ifndef _BUTTONMGR_H
#define _BUTTONMGR_H

// OpenGL Headers, using these two header files
#include "GameConstants.h"
#include "cButton.h"


using namespace std;

class cButtonMgr
{
private:
	static cButtonMgr* pInstance;

protected:
	cButtonMgr(); // Constructor
	~cButtonMgr(); // Destructor.
	map <LPCSTR, cButton*> gameBtns;

	//set variables for make a button, get a button, delete a button and get an instance
public:
	void add(LPCSTR btnName, cButton* theBtn);
	cButton* getBtn(LPCSTR btnName);
	void deleteBtn();
	static cButtonMgr* getInstance();
};
#endif
