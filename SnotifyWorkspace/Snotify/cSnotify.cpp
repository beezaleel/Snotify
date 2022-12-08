#include "cPersonGenerator.h"
#include "cMusicGenerator.h"
#include "cSnotify.h"

cSnotify::cSnotify()
{
}

cSnotify::~cSnotify()
{
}

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

	Node* node = libraries.GetHead();
	while (node != nullptr) {
		if (node->data.snotifyUserID == snotifyUserID) {
			sizeOfLibary = node->data.songs.Size();
			pLibraryArray = new cSong[sizeOfLibary];
			for (int i = 0; i < sizeOfLibary; i++) {
				pLibraryArray[i] = node->data.songs.Get(i);
			}
			return true;
		}
		node = node->next;
	}

	return false;
}

bool cSnotify::GetUsersSongLibraryAscendingByTitle(unsigned int snotifyUserID, cSong*& pLibraryArray, unsigned int& sizeOfLibary)
{
	Node* node = libraries.GetHead();
	while (node != nullptr) {
		if (node->data.snotifyUserID == snotifyUserID) {
			sizeOfLibary = node->data.songs.Size();
			pLibraryArray = new cSong[sizeOfLibary];
			for (int i = 0; i < sizeOfLibary; i++) {
				pLibraryArray[i] = node->data.songs.Get(i);
			}

			for (int i = 0; i < sizeOfLibary; i++) {
				for (int j = i + 1; j < sizeOfLibary; j++) {
					if (pLibraryArray[j].name < pLibraryArray[i].name) {
						cSong temp = pLibraryArray[i];
						pLibraryArray[i] = pLibraryArray[j];
						pLibraryArray[j] = temp;
					}
				}
			}
			return true;
		}
		node = node->next;
	}

	return false;
}

bool cSnotify::GetUsersSongLibraryAscendingByArtist(unsigned int snotifyUserID, cSong*& pLibraryArray, unsigned int& sizeOfLibary)
{
	Node* node = libraries.GetHead();
	while (node != nullptr) {
		if (node->data.snotifyUserID == snotifyUserID) {
			sizeOfLibary = node->data.songs.Size();
			pLibraryArray = new cSong[sizeOfLibary];
			for (int i = 0; i < sizeOfLibary; i++) {
				pLibraryArray[i] = node->data.songs.Get(i);
			}

			for (int i = 0; i < sizeOfLibary; i++) {
				for (int j = i + 1; j < sizeOfLibary; j++) {
					if (pLibraryArray[j].artist < pLibraryArray[i].artist) {
						cSong temp = pLibraryArray[i];
						pLibraryArray[i] = pLibraryArray[j];
						pLibraryArray[j] = temp;
					}
				}
			}
			return true;
		}
		node = node->next;
	}

	return false;
}

bool cSnotify::GetUsers(cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray)
{
	sizeOfUserArray = users.Size();
	pAllTheUsers = new cPerson[sizeOfUserArray];
	if (users.Size() > 0) {
		for (int i = 0; i < sizeOfUserArray; i++) {
			pAllTheUsers[i] = users.Get(i);
		}
		
		return true;
	}
	
	return false;
}

bool cSnotify::GetUsersByID(cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray)
{
	sizeOfUserArray = users.Size();
	pAllTheUsers = new cPerson[sizeOfUserArray];
	if (users.Size() > 0) {
		for (int i = 0; i < sizeOfUserArray; i++) {
			pAllTheUsers[i] = users.Get(i);
		}

		for (int i = 0; i < sizeOfUserArray; i++) {
			for (int j = i + 1; j < sizeOfUserArray; j++) {
				if (pAllTheUsers[j].getSnotifyUniqueUserID() < pAllTheUsers[i].getSnotifyUniqueUserID()) {
					cPerson temp = pAllTheUsers[i];
					pAllTheUsers[i] = pAllTheUsers[j];
					pAllTheUsers[j] = temp;
				}
			}
		}

		return true;
	}

	return false;
}

bool cSnotify::FindUsersFirstName(std::string firstName, cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray)
{
	unsigned int size = 0;
	cPerson* tempUsers = nullptr;
	size = users.Size();
	tempUsers = new cPerson[size];
	if (users.Size() > 0) {
		for (int i = 0; i < size; i++) {
			if (firstName == users.Get(i).first) {
				sizeOfUserArray++;
			}
			tempUsers[i] = users.Get(i);
		}

		if (sizeOfUserArray == 0) // No user with this Firstname.
			return false;

		pAllTheUsers = new cPerson[sizeOfUserArray];
		int count = 0;
		for (int i = 0; i < size; i++) {
			if (firstName == tempUsers[i].first) {
				pAllTheUsers[count] = tempUsers[i];
				count++;
			}
		}

		for (int i = 0; i < sizeOfUserArray; i++) {
			for (int j = i + 1; j < sizeOfUserArray; j++) {
				if (pAllTheUsers[j].first < pAllTheUsers[i].first) {
					cPerson temp = pAllTheUsers[i];
					pAllTheUsers[i] = pAllTheUsers[j];
					pAllTheUsers[j] = temp;
				}
			}
		}

		return true;
	}
	return false;
}

bool cSnotify::FindUsersLastName(std::string lastName, cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray)
{
	unsigned int size = 0;
	cPerson* tempUsers = nullptr;
	size = users.Size();
	tempUsers = new cPerson[size];
	if (users.Size() > 0) {
		for (int i = 0; i < size; i++) {
			if (lastName == users.Get(i).last) {
				sizeOfUserArray++;
			}
			tempUsers[i] = users.Get(i);
		}

		if (sizeOfUserArray == 0) // No user with this Lastname.
			return false;

		pAllTheUsers = new cPerson[sizeOfUserArray];
		int count = 0;
		for (int i = 0; i < size; i++) {
			if (lastName == tempUsers[i].last) {
				pAllTheUsers[count] = tempUsers[i];
				count++;
			}
		}

		for (int i = 0; i < sizeOfUserArray; i++) {
			for (int j = i + 1; j < sizeOfUserArray; j++) {
				if (pAllTheUsers[j].last < pAllTheUsers[i].last) {
					cPerson temp = pAllTheUsers[i];
					pAllTheUsers[i] = pAllTheUsers[j];
					pAllTheUsers[j] = temp;
				}
			}
		}

		return true;
	}
	return false;
}

bool cSnotify::FindUsersFirstLastNames(std::string firstName, std::string lastName, cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray)
{
	unsigned int size = 0;
	cPerson* tempUsers = nullptr;
	size = users.Size();
	tempUsers = new cPerson[size];
	if (users.Size() > 0) {
		for (int i = 0; i < size; i++) {
			if (firstName == users.Get(i).first) {
				sizeOfUserArray++;
			}
			tempUsers[i] = users.Get(i);
		}

		if (sizeOfUserArray == 0) // No user with this Firstname.
			return false;

		pAllTheUsers = new cPerson[sizeOfUserArray];
		int count = 0;
		for (int i = 0; i < size; i++) {
			if (firstName == tempUsers[i].first) {
				pAllTheUsers[count] = tempUsers[i];
				count++;
			}
		}

		for (int i = 0; i < sizeOfUserArray; i++) {
			for (int j = i + 1; j < sizeOfUserArray; j++) {
				if (pAllTheUsers[j].last < pAllTheUsers[i].last) {
					cPerson temp = pAllTheUsers[i];
					pAllTheUsers[i] = pAllTheUsers[j];
					pAllTheUsers[j] = temp;
				}
			}
		}

		for (int i = 0; i < sizeOfUserArray; i++) {
			for (int j = i + 1; j < sizeOfUserArray; j++) {
				if (pAllTheUsers[j].first < pAllTheUsers[i].first) {
					cPerson temp = pAllTheUsers[i];
					pAllTheUsers[i] = pAllTheUsers[j];
					pAllTheUsers[j] = temp;
				}
			}
		}

		return true;
	}
	return false;
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

void TestAll() {
	std::string error;
	bool result;

	printf("****************************Test personGenerator Start****************************************\n");
	// Load Census files
	cPersonGenerator personGenerator = cPersonGenerator();
	result = personGenerator.LoadCensusFiles("yob1980.txt", "Names_2010Census.csv", "Street_Names.csv", error);
	if (!result) {
		printf("%s\n", error.c_str());
	}
	// Print length of each file
	printf("yob1980.txt count: %d\n", personGenerator.getNumberOfNamesLoaded());
	printf("Names_2010Census.csv count: %d\n", personGenerator.getNumberOfSurnamesLoaded());
	printf("Street_Names.csv count: %d\n", personGenerator.getNumberOfStreetsLoaded());

	for (int i = 0; i < 3; i++) {
		cPerson* person;
		person = personGenerator.generateRandomPerson();
		printf("UniqueUserID: %d, Gender: %s, Name: %s %s, SIN: %d, Street: %s\n", 
			person->getSnotifyUniqueUserID(), 
			person->getGenderAsString().c_str(), 
			person->first.c_str(), 
			person->last.c_str(), 
			person->SIN, 
			person->streetName.c_str());
	}
	printf("***************************Test personGenerator End*******************************************\n");
	printf("\n");

	printf("****************************Test cMusicGenerator Start****************************************\n");
	// Load songs
	cMusicGenerator musicGenerator = cMusicGenerator();
	result = musicGenerator.LoadMusicInformation("hot_stuff_2.csv", error);
	if (!result) {
		printf("%s\n", error.c_str());
	}
	// Find song.
	cSong* song;
	song = musicGenerator.findSong("Naughty Girls (Need Love Too)", "Samantha Fox");
	if (song) {
		printf("musicGenerator.findSong() ::: getUniqueID: %d, Name: %s, Artist: %s\n",
			song->getUniqueID(),
			song->name.c_str(),
			song->artist.c_str());
	}
	

	for (int i = 0; i < 3; i++) {
		song = musicGenerator.getRandomSong();
		printf("musicGenerator.getRandomSong() ::: getUniqueID: %d, Name: %s, Artist: %s\n",
			song->getUniqueID(),
			song->name.c_str(),
			song->artist.c_str());
	}
	printf("***************************Test cMusicGenerator End*******************************************\n");

	printf("\n");

	printf("****************************Test cSnotify#AddUser() Start****************************************\n");
	cSnotify snotify = cSnotify();
	cPerson* person;
	person = personGenerator.generateRandomPerson();
	result = snotify.AddUser(person, error);
	if (!result) {
		printf("%s\n", error.c_str());
	}
	else {
		printf("snotify.AddUser() ::: User added successfully.\n");
	}
	// Try to add the same user again!
	result = snotify.AddUser(person, error);
	if (!result) {
		printf("snotify.AddUser() :::  %s\n", error.c_str());
	}
	printf("****************************Test cSnotify#AddUser() End****************************************\n");

	printf("\n");

	printf("****************************Test cSnotify#UpdateUser() Start****************************************\n");

	person->first = "Ademola";
	result = snotify.UpdateUser(person, error);
	if (!result) {
		printf("%s\n", error.c_str());
	}
	else {
		printf("snotify.UpdateUser() ::: User updated successfully.\n");
	}
	// Try to update user with fake uniqueId!
	cPerson* fakePerson = new cPerson();
	result = snotify.UpdateUser(fakePerson, error);
	if (!result) {
		printf("snotify.UpdateUser() :::  %s\n", error.c_str());
	}
	printf("****************************Test cSnotify#UpdateUser() End****************************************\n");

	printf("\n");

	printf("****************************Test cSnotify#DeleteUser() Start****************************************\n");

	cPerson* person2;
	person2 = personGenerator.generateRandomPerson();
	snotify.AddUser(person2, error);
	result = snotify.DeleteUser(person2->getSnotifyUniqueUserID(), error);
	if (!result) {
		printf("%s\n", error.c_str());
	}
	else {
		printf("snotify.DeleteUser() ::: User deleted successfully.\n");
	}
	// Try to delete already deleted user!
	result = snotify.DeleteUser(person2->getSnotifyUniqueUserID(), error);
	if (!result) {
		printf("snotify.DeleteUser() :::  %s\n", error.c_str());
	}
	printf("****************************Test cSnotify#DeleteUser() End****************************************\n");

	printf("\n");

	printf("****************************Test cSnotify#AddSong() Start****************************************\n");

	song = musicGenerator.getRandomSong();
	result = snotify.AddSong(song, error);

	if (!result) {
		printf("%s\n", error.c_str());
	}
	else {
		printf("snotify.AddSong() ::: Song Added successfully.\n");
	}
	// Try to added same song again!
	result = snotify.AddSong(song, error);
	if (!result) {
		printf("snotify.AddSong() :::  %s\n", error.c_str());
	}
	printf("****************************Test cSnotify#AddSong() End****************************************\n");

	printf("\n");

	printf("****************************Test cSnotify#UpdateSong() Start****************************************\n");

	song->rating = 5;
	result = snotify.UpdateSong(song, error);

	if (!result) {
		printf("%s\n", error.c_str());
	}
	else {
		printf("snotify.UpdateSong() ::: Song Updated successfully.\n");
	}
	// Try to update fake song!
	cSong* fakeSong = new cSong();
	result = snotify.UpdateSong(fakeSong, error);
	if (!result) {
		printf("snotify.UpdateSong() :::  %s\n", error.c_str());
	}
	printf("****************************Test cSnotify#UpdateSong() End****************************************\n");

	printf("\n");

	printf("****************************Test cSnotify#DeleteSong() Start****************************************\n");

	result = snotify.DeleteSong(song->getUniqueID(), error);
	if (!result) {
		printf("%s\n", error.c_str());
	}
	else {
		printf("snotify.DeleteSong() ::: User deleted successfully.\n");
	}
	// Try to delete already deleted song!
	result = snotify.DeleteSong(song->getUniqueID(), error);
	if (!result) {
		printf("snotify.DeleteSong() :::  %s\n", error.c_str());
	}
	printf("****************************Test cSnotify#DeleteSong() End****************************************\n");

	printf("\n");

	printf("****************************Test cSnotify#AddSongToUserLibrary() Start****************************************\n");

	for (int i = 0; i < 7; i++) {
		song = musicGenerator.getRandomSong();
		result = snotify.AddSongToUserLibrary(person->getSnotifyUniqueUserID(), song, error);
		if (!result) {
			printf("%s\n", error.c_str());
		}
		else {
			printf("snotify.AddSongToUserLibrary() ::: Song added to user's library successfully.\n");
		}
	}
	
	// Try to adding same song to user's library!
	result = snotify.AddSongToUserLibrary(person->getSnotifyUniqueUserID(), song, error);
	if (!result) {
		printf("snotify.AddSongToUserLibrary() :::  %s\n", error.c_str());
	}
	printf("****************************Test cSnotify#AddSongToUserLibrary() End****************************************\n");

	printf("\n");

	printf("****************************Test cSnotify#RemoveSongFromUserLibrary() Start****************************************\n");

	result = snotify.RemoveSongFromUserLibrary(person->getSnotifyUniqueUserID(), song->getUniqueID(), error);
	if (!result) {
		printf("%s\n", error.c_str());
	}
	else {
		printf("snotify.RemoveSongFromUserLibrary() ::: Song removed from user's library successfully.\n");
	}

	// Try to remove same song to user's library!
	result = snotify.RemoveSongFromUserLibrary(person->getSnotifyUniqueUserID(), song->getUniqueID(), error);
	if (!result) {
		printf("snotify.RemoveSongFromUserLibrary() :::  %s\n", error.c_str());
	}
	printf("****************************Test cSnotify#RemoveSongFromUserLibrary() End****************************************\n");

	printf("\n");

	printf("****************************Test cSnotify#UpdateRatingOnSong() Start****************************************\n");

	cSong* song1;
	song1 = musicGenerator.getRandomSong();
	snotify.AddSong(song1, error);
	snotify.AddSongToUserLibrary(person->getSnotifyUniqueUserID(), song1, error);
	result = snotify.UpdateRatingOnSong(person->getSnotifyUniqueUserID(), song1->getUniqueID(), 3);
	if (!result) {
		printf("%s\n", error.c_str());
	}
	else {
		printf("snotify.UpdateRatingOnSong() ::: Song rate updated successfully.\n");
	}

	// Try to update fake song in user's library!
	fakeSong = new cSong();
	result = snotify.UpdateRatingOnSong(person->getSnotifyUniqueUserID(), fakeSong->getUniqueID(), 4);
	if (!result) {
		printf("snotify.UpdateRatingOnSong() :::  %s\n", error.c_str());
	}
	printf("****************************Test cSnotify#UpdateRatingOnSong() End****************************************\n");

	printf("\n");

	printf("****************************Test cSnotify#GetSong() Start****************************************\n");

	song = musicGenerator.getRandomSong();
	song->rating = 5;
	snotify.AddSongToUserLibrary(person->getSnotifyUniqueUserID(), song, error);

	cSong* newSong;
	newSong = snotify.GetSong(person->getSnotifyUniqueUserID(), song->getUniqueID(), error);
	if (!newSong) {
		printf("%s\n", error.c_str());
	}
	else {
		printf("snotify.GetSong() ::: Song retrieved successfully.\n");
		printf("snotify.GetSong() ::: getUniqueID: %d, Name: %s, Artist: %s\n",
			newSong->getUniqueID(),
			newSong->name.c_str(),
			newSong->artist.c_str());
	}

	// Try to update fake song in user's library!
	cSong* newSong1;
	newSong1 = snotify.GetSong(person->getSnotifyUniqueUserID(), 400, error);
	if (!newSong1) {
		printf("snotify.GetSong() :::  %s\n", error.c_str());
	}
	printf("****************************Test cSnotify#GetSong() End****************************************\n");

	printf("\n");

	printf("****************************Test cSnotify#GetCurrentSongRating() Start****************************************\n");

	unsigned int songRating = 0;
	result = snotify.GetCurrentSongRating(person->getSnotifyUniqueUserID(), newSong->getUniqueID(), songRating);
	if (!result) {
		printf("%s\n", error.c_str());
	}
	else {
		printf("snotify.GetCurrentSongRating() ::: Song rating retrieved successfully.\n");
		printf("snotify.GetCurrentSongRating() ::: Rating: %d\n", songRating);
	}
	printf("****************************Test cSnotify#GetCurrentSongRating() End****************************************\n");

	printf("\n");

	printf("****************************Test cSnotify#GetCurrentSongNumberOfPlays() Start****************************************\n");

	unsigned int numberOfPlays = 0;
	result = snotify.GetCurrentSongNumberOfPlays(person->getSnotifyUniqueUserID(), newSong->getUniqueID(), numberOfPlays);
	if (!result) {
		printf("%s\n", error.c_str());
	}
	else {
		printf("snotify.GetCurrentSongNumberOfPlays() ::: Number of plays retrieved successfully.\n");
		printf("snotify.GetCurrentSongNumberOfPlays() ::: Number of plays: %d\n", numberOfPlays);
	}
	printf("****************************Test cSnotify#GetCurrentSongNumberOfPlays() End****************************************\n");

	printf("\n");

	printf("****************************Test cSnotify#FindUserBySIN() Start****************************************\n");

	cPerson* newPerson;
	newPerson = snotify.FindUserBySIN(person->SIN);
	if (!newPerson) {
		printf("%s\n", error.c_str());
	}
	else {
		printf("snotify.FindUserBySIN() ::: User found by SIN.\n");
		printf("UniqueUserID: %d, Gender: %s, Name: %s %s, SIN: %d, Street: %s\n",
			newPerson->getSnotifyUniqueUserID(),
			newPerson->getGenderAsString().c_str(),
			newPerson->first.c_str(),
			newPerson->last.c_str(),
			newPerson->SIN,
			newPerson->streetName.c_str());
	}
	printf("****************************Test cSnotify#FindUserBySIN() End****************************************\n");

	printf("\n");

	printf("****************************Test cSnotify#FindUserBySnotifyID() Start****************************************\n");

	newPerson = snotify.FindUserBySnotifyID(person->getSnotifyUniqueUserID());
	if (!newPerson) {
		printf("%s\n", error.c_str());
	}
	else {
		printf("snotify.FindUserBySnotifyID() ::: User found by SnotifyUniqueUserID.\n");
		printf("UniqueUserID: %d, Gender: %s, Name: %s %s, SIN: %d, Street: %s\n",
			newPerson->getSnotifyUniqueUserID(),
			newPerson->getGenderAsString().c_str(),
			newPerson->first.c_str(),
			newPerson->last.c_str(),
			newPerson->SIN,
			newPerson->streetName.c_str());
	}
	printf("****************************Test cSnotify#FindUserBySnotifyID() End****************************************\n");

	printf("\n");

	printf("****************************Test cSnotify#FindSong() Start****************************************\n");

	cSong* newSong4;
	newSong4 = snotify.FindSong(song1->name, song1->artist);
	if (!newSong4) {
		printf("%s\n", error.c_str());
	}
	else {
		printf("snotify.FindSong() ::: Song found by by title and name.\n");
		printf("snotify.GetSong() ::: getUniqueID: %d, Name: %s, Artist: %s\n",
			newSong4->getUniqueID(),
			newSong4->name.c_str(),
			newSong4->artist.c_str());
	}

	cSong* newSong5;
	newSong5 = snotify.FindSong(song1->getUniqueID());
	if (!newSong5) {
		printf("%s\n", error.c_str());
	}
	else {
		printf("snotify.FindSong() ::: Song found by by uniqueID.\n");
		printf("snotify.GetSong() ::: getUniqueID: %d, Name: %s, Artist: %s\n",
			newSong5->getUniqueID(),
			newSong5->name.c_str(),
			newSong5->artist.c_str());
	}
	printf("****************************Test cSnotify#FindSong() End****************************************\n");

	printf("\n");

	printf("****************************Test cSnotify#GetUsersSongLibrary() Start****************************************\n");

	for (int i = 0; i < 5; i++) {
		result = snotify.AddSongToUserLibrary(person->getSnotifyUniqueUserID(), musicGenerator.getRandomSong(), error);
	}

	unsigned int sizeOfLibrary = 0;
	cSong* librayArray;
	result = snotify.GetUsersSongLibrary(person->getSnotifyUniqueUserID(), librayArray, sizeOfLibrary);
	if (!result) {
		printf("%s\n", error.c_str());
	}
	else {
		printf("snotify.GetUsersSongLibrary() ::: Successfully retrieved users library.\n");
		for (int i = 0; i < sizeOfLibrary; i++) {
			printf("snotify.GetUsersSongLibrary() ::: getUniqueID: %d, Name: %s, Artist: %s\n",
				librayArray->getUniqueID(),
				librayArray->name.c_str(),
				librayArray->artist.c_str());
			librayArray++;
		}
	}

	printf("****************************Test cSnotify#GetUsersSongLibrary() End****************************************\n");

	printf("\n");

	printf("****************************Test cSnotify#GetUsersSongLibraryAscendingByTitle() Start****************************************\n");

	unsigned int sizeOfLibrary1 = 0;
	cSong* librayArray1;
	result = snotify.GetUsersSongLibraryAscendingByTitle(person->getSnotifyUniqueUserID(), librayArray1, sizeOfLibrary1);
	if (!result) {
		printf("%s\n", error.c_str());
	}
	else {
		printf("snotify.GetUsersSongLibraryAscendingByTitle() ::: Successfully retrieved users library.\n");
		for (int i = 0; i < sizeOfLibrary1; i++) {
			printf("snotify.GetUsersSongLibraryAscendingByTitle() ::: getUniqueID: %d, Name: %s, Artist: %s\n",
				librayArray1->getUniqueID(),
				librayArray1->name.c_str(),
				librayArray1->artist.c_str());
			librayArray1++;
		}
	}

	printf("****************************Test cSnotify#GetUsersSongLibraryAscendingByTitle() End****************************************\n");

	printf("\n");

	printf("****************************Test cSnotify#GetUsersSongLibraryAscendingByArtist() Start****************************************\n");

	unsigned int sizeOfLibrary2 = 0;
	cSong* librayArray2;
	result = snotify.GetUsersSongLibraryAscendingByArtist(person->getSnotifyUniqueUserID(), librayArray2, sizeOfLibrary2);
	if (!result) {
		printf("%s\n", error.c_str());
	}
	else {
		printf("snotify.GetUsersSongLibraryAscendingByArtist() ::: Successfully retrieved users library.\n");
		for (int i = 0; i < sizeOfLibrary2; i++) {
			printf("snotify.GetUsersSongLibraryAscendingByArtist() ::: getUniqueID: %d, Name: %s, Artist: %s\n",
				librayArray2->getUniqueID(),
				librayArray2->name.c_str(),
				librayArray2->artist.c_str());
			librayArray2++;
		}
	}

	printf("****************************Test cSnotify#GetUsersSongLibraryAscendingByArtist() End****************************************\n");

	printf("\n");

	printf("****************************Test cSnotify#GetUsers() Start****************************************\n");

	for (int i = 0; i < 5; i++) {
		result = snotify.AddUser(personGenerator.generateRandomPerson(), error);
	}

	unsigned int sizeOfUser = 0;
	cPerson* allUsers = 0;
	result = snotify.GetUsers(allUsers, sizeOfUser);
	if (!result) {
		printf("%s\n", error.c_str());
	}
	else {
		printf("snotify.GetUsers() ::: Successfully retrieved all users.\n");
		for (int i = 0; i < sizeOfUser; i++) {
			printf("UniqueUserID: %d, Gender: %s, Name: %s %s, SIN: %d, Street: %s\n",
				allUsers->getSnotifyUniqueUserID(),
				allUsers->getGenderAsString().c_str(),
				allUsers->first.c_str(),
				allUsers->last.c_str(),
				allUsers->SIN,
				allUsers->streetName.c_str());
			allUsers++;
		}
	}

	printf("****************************Test cSnotify#GetUsers() End****************************************\n");

	printf("\n");

	printf("****************************Test cSnotify#GetUsersByID() Start****************************************\n");

	unsigned int sizeOfUser1 = 0;
	cPerson* allUsers1 = 0;
	result = snotify.GetUsersByID(allUsers1, sizeOfUser1);
	if (!result) {
		printf("%s\n", error.c_str());
	}
	else {
		printf("snotify.GetUsersByID() ::: Successfully retrieved all users.\n");
		for (int i = 0; i < sizeOfUser1; i++) {
			printf("UniqueUserID: %d, Gender: %s, Name: %s %s, SIN: %d, Street: %s\n",
				allUsers1->getSnotifyUniqueUserID(),
				allUsers1->getGenderAsString().c_str(),
				allUsers1->first.c_str(),
				allUsers1->last.c_str(),
				allUsers1->SIN,
				allUsers1->streetName.c_str());
			allUsers1++;
		}
	}

	printf("****************************Test cSnotify#GetUsersByID() End****************************************\n");

	printf("\n");

	printf("****************************Test cSnotify#FindUsersFirstName() Start****************************************\n");
	for (int i = 0; i < 100; i++) {
		result = snotify.AddUser(personGenerator.generateRandomPerson(), error);
	}

	unsigned int sizeOfUser2 = 0;
	cPerson* allUsers2 = 0;
	result = snotify.FindUsersFirstName(person->first, allUsers2, sizeOfUser2);
	if (!result) {
		printf("Unable to find user with firstname\n");
	}
	else {
		printf("snotify.FindUsersFirstName() ::: Successfully retrieved all users.\n");
		for (int i = 0; i < sizeOfUser2; i++) {
			printf("UniqueUserID: %d, Gender: %s, Name: %s %s, SIN: %d, Street: %s\n",
				allUsers2->getSnotifyUniqueUserID(),
				allUsers2->getGenderAsString().c_str(),
				allUsers2->first.c_str(),
				allUsers2->last.c_str(),
				allUsers2->SIN,
				allUsers2->streetName.c_str());
			allUsers2++;
		}
	}

	printf("****************************Test cSnotify#FindUsersFirstName() End****************************************\n");

	printf("\n");

	printf("****************************Test cSnotify#FindUsersLastName() Start****************************************\n");

	unsigned int sizeOfUser3 = 0;
	cPerson* allUsers3 = 0;
	result = snotify.FindUsersLastName(person->last, allUsers3, sizeOfUser3);
	if (!result) {
		printf("Unable to find user with lastname\n");
	}
	else {
		printf("snotify.FindUsersLastName() ::: Successfully retrieved all users.\n");
		for (int i = 0; i < sizeOfUser3; i++) {
			printf("UniqueUserID: %d, Gender: %s, Name: %s %s, SIN: %d, Street: %s\n",
				allUsers3->getSnotifyUniqueUserID(),
				allUsers3->getGenderAsString().c_str(),
				allUsers3->first.c_str(),
				allUsers3->last.c_str(),
				allUsers3->SIN,
				allUsers3->streetName.c_str());
			allUsers3++;
		}
	}

	printf("****************************Test cSnotify#FindUsersLastName() End****************************************\n");

	printf("\n");

	printf("****************************Test cSnotify#FindUsersFirstLastNames() Start****************************************\n");

	unsigned int sizeOfUser4 = 0;
	cPerson* allUsers4 = 0;
	result = snotify.FindUsersFirstLastNames(person->first, person->last, allUsers4, sizeOfUser4);
	if (!result) {
		printf("Unable to find user with lastname\n");
	}
	else {
		printf("snotify.FindUsersFirstLastNames() ::: Successfully retrieved all users.\n");
		for (int i = 0; i < sizeOfUser4; i++) {
			printf("UniqueUserID: %d, Gender: %s, Name: %s %s, SIN: %d, Street: %s\n",
				allUsers4->getSnotifyUniqueUserID(),
				allUsers4->getGenderAsString().c_str(),
				allUsers4->first.c_str(),
				allUsers4->last.c_str(),
				allUsers4->SIN,
				allUsers4->streetName.c_str());
			allUsers4++;
		}
	}

	printf("****************************Test cSnotify#FindUsersFirstLastNames() End****************************************\n");
}

int main(int argc, char** argv) {
	TestAll();
	return 0;
}
