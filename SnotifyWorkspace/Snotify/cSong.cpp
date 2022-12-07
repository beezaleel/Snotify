#include "cSong.h"

cSong::cSong() {
	this->rating = 0;
	this->numberOfTimesPlayed = 0;
	this->uniqueID = cSong::m_NEXT_Snotify_UniqueSongID;
	const unsigned int MAX_ID_INCREMENT = 11;
	cSong::m_NEXT_Snotify_UniqueSongID += (rand() % MAX_ID_INCREMENT);
}

unsigned int cSong::getUniqueID(void)
{
	return this->uniqueID;
}

unsigned int cSong::m_NEXT_Snotify_UniqueSongID = 1;