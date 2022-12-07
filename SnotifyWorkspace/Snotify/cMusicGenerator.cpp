#include "cMusicGenerator.h"

static bool seeded = false;

cMusicGenerator::cMusicGenerator() {
}

cMusicGenerator::~cMusicGenerator() {
}

bool cMusicGenerator::LoadMusicInformation(std::string musicFileName, std::string& errorString)
{
	// Load song
	int index = 0;
	std::ifstream infile(musicFileName);

	if (infile.bad() || infile.fail()) {
		errorString = "Unable to open file: " + musicFileName;
		return false;
	}

	while (infile.is_open()) {
		std::string line;

		if (!getline(infile, line))
			break;

		if (index == 0) {
			index++;
			continue;
		}

		mMusics.Add(line.c_str());
		index++;
	}

	return true;
}

cSong* cMusicGenerator::getRandomSong(void)
{
	cList<std::string> musicList;
	int index = GenerateRandomNumber(mMusics.Size());

	std::stringstream musicStream(mMusics.Get(index));
	while (musicStream.good())
	{
		std::string substr;
		getline(musicStream, substr, ',');
		musicList.Add(substr.c_str());
	}
	cSong* song = new cSong();
	song->name = musicList.Get(3).c_str();
	song->artist = musicList.Get(4).c_str();
	song->numberOfTimesPlayed = index; // Setting play times to index value so that it's not just zero.

	return song;
}

int cMusicGenerator::GenerateRandomNumber(int max)
{
	if (!seeded) {
		srand(time(0));
		seeded = true;
	}
	return rand() % (max - 0);
}
