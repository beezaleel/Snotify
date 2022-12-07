#ifndef _cMusicGenerator_HG_
#define _cMusicGenerator_HG_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "cSong.h"
#include "cList.h"

class cMusicGenerator
{
public:
	cMusicGenerator();
	~cMusicGenerator();

	bool LoadMusicInformation(std::string musicFileName, std::string& errorString);

	cSong* getRandomSong(void);
	
	// Returns 0, NULL, or nullptr if no song is found
	// This must be an EXACT MATCH for what's in the billboard100 file. 
	// So case sensitive, etc. 
	cSong* findSong(std::string songName, std::string artist);
private:
	cList<std::string> mMusics;
	int GenerateRandomNumber(int max);
};

#endif
