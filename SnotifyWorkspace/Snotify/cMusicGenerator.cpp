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

cSong* cMusicGenerator::findSong(std::string songName, std::string artist)
{
	for (int i = 0; i < mMusics.Size(); i++) {
		cList<std::string> songList;
		std::stringstream line(mMusics.Get(i));
		while (line.good()) {
			std::string substr;
			getline(line, substr, ',');
			songList.Add(substr.c_str());
		}
		if (songList.Get(3) == songName && songList.Get(4) == artist) {
			cSong* song = new cSong();
			song->name = songList.Get(3).c_str();
			song->artist = songList.Get(4).c_str();
			song->numberOfTimesPlayed = i;
			return song;
		}
	}
	return nullptr;
}

int cMusicGenerator::GenerateRandomNumber(int max)
{
	if (!seeded) {
		srand(time(0));
		seeded = true;
	}
	return rand() % (max - 0);
}
