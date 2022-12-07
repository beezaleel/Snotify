#pragma once

#include "cList.h"
#include "cSong.h"

struct Library {
	unsigned int snotifyUserID = 0;
	cList<cSong> songs;
};
