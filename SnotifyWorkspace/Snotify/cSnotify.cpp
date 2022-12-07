#include "cPersonGenerator.h"
#include "cMusicGenerator.h"
#include "cSnotify.h"


// This returns a COPY of the users library, in the form of a regular dynamic array.
bool cSnotify::GetUsersSongLibrary(unsigned int snotifyUserID, cSong*& pLibraryArray, unsigned int& sizeOfLibary)
{
	// The caller would do something like this (assume the user ID = 28472382)
	//
	//	cSong* pTheSongs = 0;
	//	unsigned int arraySize = 0;
	//	GetUsersSongLibrary( 28472382, pTheSongs, arraySize );
	// 
	// Inside this method, you'd do something like this:

	// TODO: Find that user... 

	// Alloate a heap based array to hold all the songs...

//	sizeOfLibary = WhateverYouHaveToDoToGetThisValue();
//	pCopyOfLibrary = new cSong[sizeOfLibary];

	// The array and the size of the array are "returned" by reference to the caller. 

	// TODO: Copy all the songs over

	return true;
}

cSnotify::cSnotify()
{
}

cSnotify::~cSnotify()
{
}

bool cSnotify::AddUser(cPerson* pPerson, std::string& errorString)
{
	// check if user already exist.
	for (int i = 0; i < users.Size(); i++) {
		if (users.Get(i).getSnotifyUniqueUserID() == pPerson->getSnotifyUniqueUserID()) {
			errorString = "Add user failed because uniqueId already exist. id: " + std::to_string(pPerson->getSnotifyUniqueUserID());
			return false;
		}
		// Add user to list.
	}
	users.Add(*pPerson);
	
	return true;
}

bool cSnotify::UpdateUser(cPerson* pPerson, std::string& errorString)
{
	// Find the user with unique snotifyId
	for (int i = 0; i < users.Size(); i++) {
		if (users.Get(i).getSnotifyUniqueUserID() == pPerson->getSnotifyUniqueUserID()) {
			users.Add(*pPerson, i);
			return true;
		}
	}
	errorString = "Update user failed because uniqueId does not exist. id: " + std::to_string(pPerson->getSnotifyUniqueUserID());

	return false;
}

bool cSnotify::DeleteUser(unsigned int SnotifyUserID, std::string& errorString)
{
	for (int i = 0; i < users.Size(); i++) {
		if (users.Get(i).getSnotifyUniqueUserID() == SnotifyUserID) {
			users.Delete(i);
			return true;
		}
	}
	errorString = "Failed to delete user with uniqueId: " + std::to_string(SnotifyUserID);

	return false;
}

bool cSnotify::AddSong(cSong* pSong, std::string& errorString)
{
	// check if song already exist.
	for (int i = 0; i < songs.Size(); i++) {
		if (songs.Get(i).getUniqueID() == pSong->getUniqueID()) {
			errorString = "Add song failed because uniqueId already exist. id: " + std::to_string(pSong->getUniqueID());
			return false;
		}
		// Add song to list.
	}
	songs.Add(*pSong);

	return true;
}

bool cSnotify::UpdateSong(cSong* pSong, std::string& errorString)
{
	// Find the song with unique snotifyId
	for (int i = 0; i < songs.Size(); i++) {
		if (songs.Get(i).getUniqueID() == pSong->getUniqueID()) {
			songs.Add(*pSong, i);
			return true;
		}
	}
	errorString = "Update song failed because uniqueId does not exist. id: " + std::to_string(pSong->getUniqueID());

	return false;
}

bool cSnotify::DeleteSong(unsigned int UniqueSongID, std::string& errorString)
{
	for (int i = 0; i < songs.Size(); i++) {
		if (songs.Get(i).getUniqueID() == UniqueSongID) {
			songs.Delete(i);
			return true;
		}
	}
	errorString = "Failed to delete song with uniqueId: " + std::to_string(UniqueSongID);

	return false;
}

bool cSnotify::AddSongToUserLibrary(unsigned int snotifyUserID, cSong* pNewSong, std::string& errorString)
{
	Node* node = libraries.GetHead();
	while (node != nullptr) {
		if (node->data.snotifyUserID == snotifyUserID) {
			//bool songExist = false;
			for (int i = 0; i < node->data.songs.Size(); i++) {
				if (node->data.songs.Get(i).getUniqueID() == pNewSong->getUniqueID()) {
					errorString = "Failed to add song because it already exist. UniqueId: " + std::to_string(pNewSong->getUniqueID());
					return false;
				}
			}
			// If we get here, it means the song does not exist in user's library.
			node->data.songs.Add(*pNewSong);
			return true;
		}
		node = node->next;
	}
	// If we get here, means the user does not have a library so add one.
	Library* data = new Library();
	data->snotifyUserID = snotifyUserID;
	data->songs.Add(*pNewSong);
	libraries.AddNode(data);
	return true;
}

bool cSnotify::RemoveSongFromUserLibrary(unsigned int snotifyUserID, unsigned int SnotifySongID, std::string& errorString)
{
	Node* node = libraries.GetHead();
	while (node != nullptr) {
		if (node->data.snotifyUserID == snotifyUserID) {
			bool songExist = false;
			for (int i = 0; i < node->data.songs.Size(); i++) {

				if (node->data.songs.Get(i).getUniqueID() == SnotifySongID) {
					node->data.songs.Delete(i);
					songExist = true;
					return true;
				}
			}
			if (!songExist) {
				errorString = "Song does not exist in user's library. SnotifySongID: " + std::to_string(SnotifySongID);
				return false;
			}
		}
		node = node->next;
	}
	return false;
}

bool cSnotify::UpdateRatingOnSong(unsigned int SnotifyUserID, unsigned int songUniqueID, unsigned int newRating)
{
	Node* node = libraries.GetHead();
	while (node != nullptr) {
		if (node->data.snotifyUserID == SnotifyUserID) {
			for (int i = 0; i < node->data.songs.Size(); i++) {
				if (node->data.songs.Get(i).getUniqueID() == songUniqueID) {
					cSong pSong = node->data.songs.Get(i);
					pSong.rating = newRating;
					node->data.songs.Add(pSong, i);
					return true;
				}
			}
			return false;
		}
		node = node->next;
	}
	return false;
}

cSong* cSnotify::GetSong(unsigned int SnotifyUserID, unsigned int songUniqueID, std::string& errorString)
{
	cSong* pSong = new cSong();
	Node* node = libraries.GetHead();
	while (node != nullptr) {
		if (node->data.snotifyUserID == SnotifyUserID) {
			for (int i = 0; i < node->data.songs.Size(); i++) {
				if (node->data.songs.Get(i).getUniqueID() == songUniqueID) {
					*pSong = node->data.songs.Get(i);
					return pSong;
				}
			}
			errorString = "Unable to find song with songUniqueID " + std::to_string(songUniqueID);
		}
		node = node->next;
	}
	return nullptr;
}

bool cSnotify::GetCurrentSongRating(unsigned int snotifyUserID, unsigned int songUniqueID, unsigned int& songRating)
{
	Node* node = libraries.GetHead();
	while (node != nullptr) {
		if (node->data.snotifyUserID == snotifyUserID) {
			for (int i = 0; i < node->data.songs.Size(); i++) {
				if (node->data.songs.Get(i).getUniqueID() == songUniqueID) {
					songRating = node->data.songs.Get(i).rating;
					return true;
				}
			}
			return false;
		}
		node = node->next;
	}
	return false;
}

bool cSnotify::GetCurrentSongNumberOfPlays(unsigned int snotifyUserID, unsigned int songUniqueID, unsigned int& numberOfPlays)
{
	Node* node = libraries.GetHead();
	while (node != nullptr) {
		if (node->data.snotifyUserID == snotifyUserID) {
			for (int i = 0; i < node->data.songs.Size(); i++) {
				if (node->data.songs.Get(i).getUniqueID() == songUniqueID) {
					numberOfPlays = node->data.songs.Get(i).numberOfTimesPlayed;
					return true;
				}
			}
			return false;
		}
		node = node->next;
	}
	return false;
}

cPerson* cSnotify::FindUserBySIN(unsigned int SIN)
{
	cPerson* person = new cPerson();
	for (int i = 0; i < users.Size(); i++) {
		if (users.Get(i).SIN == SIN) {
			*person = users.Get(i);
			return person;
		}
	}

	return nullptr;
}

cPerson* cSnotify::FindUserBySnotifyID(unsigned int SnotifyID)
{
	cPerson* person = new cPerson();
	for (int i = 0; i < users.Size(); i++) {
		if (users.Get(i).getSnotifyUniqueUserID() == SnotifyID) {
			*person = users.Get(i);
			return person;
		}
	}
	return nullptr;
}

cSong* cSnotify::FindSong(std::string title, std::string artist)
{
	cSong* song = new cSong();
	for (int i = 0; i < songs.Size(); i++) {
		if (songs.Get(i).name == title && songs.Get(i).artist == artist) {
			*song = songs.Get(i);
			return song;
		}
	}
	return nullptr;
}

cSong* cSnotify::FindSong(unsigned int uniqueID)
{
	cSong* song = new cSong();
	for (int i = 0; i < songs.Size(); i++) {
		if (songs.Get(i).getUniqueID() == uniqueID) {
			*song = songs.Get(i);
			return song;
		}
	}
	return nullptr;
}

int main(int argc, char** argv) {
	std::string error;
	bool result;

	cPersonGenerator personGenerator = cPersonGenerator();
	result = personGenerator.LoadCensusFiles("yob1980.txt", "Names_2010Census.csv", "Street_Names.csv", error);
	if (!result) {
		printf("%s\n", error.c_str());
	}

	cPerson* person;
	person = personGenerator.generateRandomPerson();

	cMusicGenerator musicGenerator = cMusicGenerator();
	result = musicGenerator.LoadMusicInformation("hot_stuff_2.csv", error);
	if (!result) {
		printf("%s\n", error.c_str());
	}

	cSong* song;
	song = musicGenerator.getRandomSong();

	cSong* song2;
	song2 = musicGenerator.getRandomSong();


	cSnotify snotify = cSnotify();
	result = snotify.AddUser(person, error);
	if (!result) {
		printf("%s\n", error.c_str());
	}

	snotify.AddSong(song, error);
	snotify.AddSong(song2, error);

	result = snotify.AddUser(person, error);
	if (!result) {
		printf("%s\n", error.c_str());
	}

	person->first = "Ademola";
	result = snotify.UpdateUser(person, error);
	if (!result) {
		printf("%s\n", error.c_str());
	}

	person->first = "Ademola";
	result = snotify.UpdateUser(person, error);
	if (!result) {
		printf("%s\n", error.c_str());
	}

	cPerson* person1;
	person1 = personGenerator.generateRandomPerson();
	snotify.AddUser(person1, error);

	cPerson* person2;
	person2 = personGenerator.generateRandomPerson();
	snotify.AddUser(person2, error);

	result = snotify.DeleteUser(person2->getSnotifyUniqueUserID(), error);
	if (!result) {
		printf("%s\n", error.c_str());
	}

	result = snotify.DeleteUser(person2->getSnotifyUniqueUserID(), error);
	if (!result) {
		printf("%s\n", error.c_str());
	}

	result = snotify.AddSongToUserLibrary(person2->getSnotifyUniqueUserID(), song, error);
	if (!result) {
		printf("%s\n", error.c_str());
	}

	result = snotify.AddSongToUserLibrary(person2->getSnotifyUniqueUserID(), song, error);
	if (!result) {
		printf("%s\n", error.c_str());
	}

	result = snotify.AddSongToUserLibrary(person1->getSnotifyUniqueUserID(), song2, error);
	if (!result) {
		printf("%s\n", error.c_str());
	}

	result = snotify.RemoveSongFromUserLibrary(person1->getSnotifyUniqueUserID(), song2->getUniqueID(), error);
	if (!result) {
		printf("%s\n", error.c_str());
	}

	result = snotify.RemoveSongFromUserLibrary(person1->getSnotifyUniqueUserID(), 500, error);
	if (!result) {
		printf("%s\n", error.c_str());
	}

	cSong* song3;
	song3 = musicGenerator.getRandomSong();
	result = snotify.AddSongToUserLibrary(person1->getSnotifyUniqueUserID(), song3, error);
	if (!result) {
		printf("%s\n", error.c_str());
	}

	cSong* song4;
	song4 = musicGenerator.getRandomSong();
	result = snotify.AddSongToUserLibrary(person1->getSnotifyUniqueUserID(), song4, error);
	if (!result) {
		printf("%s\n", error.c_str());
	}

	snotify.UpdateRatingOnSong(person1->getSnotifyUniqueUserID(), song3->getUniqueID(), 3);
	snotify.UpdateRatingOnSong(person1->getSnotifyUniqueUserID(), song4->getUniqueID(), 4);

	cSong* newSong;
	newSong = snotify.GetSong(person1->getSnotifyUniqueUserID(), song3->getUniqueID(), error);
	if (!result) {
		printf("%s\n", error.c_str());
	}

	cSong* newSong2;
	newSong2 = snotify.GetSong(person1->getSnotifyUniqueUserID(), 200, error);
	if (!newSong2) {
		printf("%s\n", error.c_str());
	}

	unsigned int songRating = 0;
	result = snotify.GetCurrentSongRating(person1->getSnotifyUniqueUserID(), song4->getUniqueID(), songRating);
	if (!result) {
		printf("%s\n", error.c_str());
	}

	unsigned int numberOfPlays = 0;
	result = snotify.GetCurrentSongNumberOfPlays(person1->getSnotifyUniqueUserID(), song4->getUniqueID(), numberOfPlays);
	if (!result) {
		printf("%s\n", error.c_str());
	}

	cPerson* newPerson;
	newPerson = snotify.FindUserBySIN(person1->SIN);
	if (!newPerson) {
		printf("%s\n", error.c_str());
	}

	cPerson* newPerson1;
	newPerson1 = snotify.FindUserBySnotifyID(person1->getSnotifyUniqueUserID());
	if (!newPerson1) {
		printf("%s\n", error.c_str());
	}

	cSong* newSong4;
	newSong4 = snotify.FindSong(song2->name, song2->artist);
	if (!newSong4) {
		printf("%s\n", error.c_str());
	}

	return 0;
}
