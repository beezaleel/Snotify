#include "cPersonGenerator.h"

// Warning C26812 : Prefer 'enum class' over 'enum' (Enum.3)
#pragma warning( disable : 26812 )

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

static bool seeded = false;

cPersonGenerator::cPersonGenerator()
{
}

cPersonGenerator::~cPersonGenerator()
{
}

bool cPersonGenerator::LoadCensusFiles(
	std::string babyNameFile,
	std::string surnameFile,
	std::string streetNameFile,
	std::string& errorString)
{
	// Load names
	std::ifstream infile(babyNameFile);

	if (infile.bad() || infile.fail()) {
		errorString = "Unable to open file: " + babyNameFile;
		return false;
	}

	while (infile.is_open()) {
		std::string line;

		if (!getline(infile, line))
			break;
		mNames.Add(line.c_str());
	}
	infile.close();

	// Load surnames
	int surnameIndex = 0;
	std::ifstream infileSurname(surnameFile);

	if (infileSurname.bad() || infileSurname.fail()) {
		errorString = "Unable to open file: " + surnameFile;
		return false;
	}

	while (infileSurname.is_open()) {
		std::string line;

		if (!getline(infileSurname, line))
			break;

		if (surnameIndex == 0) {
			surnameIndex++;
			continue;
		}
			
		mSurnames.Add(line.c_str());
		surnameIndex++;
	}

	// Load street
	int streetIndex = 0;
	std::ifstream infileStreet(streetNameFile);

	if (infileStreet.bad() || infileStreet.fail()) {
		errorString = "Unable to open file: " + streetNameFile;
		return false;
	}

	while (infileStreet.is_open()) {
		std::string line;

		if (!getline(infileStreet, line))
			break;

		if (streetIndex == 0) {
			streetIndex++;
			continue;
		}

		mStreets.Add(line.c_str());
		streetIndex++;
	}

	return true;
}

unsigned int cPersonGenerator::getNumberOfNamesLoaded(void)
{
	return mNames.Size();
}

unsigned int cPersonGenerator::getNumberOfSurnamesLoaded(void)
{
	return mSurnames.Size();
}

unsigned int cPersonGenerator::getNumberOfStreetsLoaded(void)
{
	return mStreets.Size();
}

cPerson* cPersonGenerator::generateRandomPerson(void)
{
	cList<std::string> addressList;
	cList<std::string> firstnameList;
	cList<std::string> lastnameList;

	int index = GenerateRandomNumber(mStreets.Size());

	std::stringstream addressStream(mStreets.Get(index));
	while (addressStream.good())
	{
		std::string substr;
		getline(addressStream, substr, ',');
		addressList.Add(substr.c_str());
	}

	std::stringstream firstnameStream(mNames.Get(index));
	while (firstnameStream.good())
	{
		std::string substr;
		getline(firstnameStream, substr, ',');
		firstnameList.Add(substr.c_str());
	}

	std::stringstream lastnameStream(mSurnames.Get(index));
	while (lastnameStream.good())
	{
		std::string substr;
		getline(lastnameStream, substr, ',');
		lastnameList.Add(substr.c_str());
	}

	cPerson* person = new cPerson();
	person->age = atoi(lastnameList.Get(1).c_str()); // Using lastname rank as age since there is no age field in csv
	person->city = ""; // No city provided
	person->first = firstnameList.Get(0).c_str();
	if (firstnameList.Get(1) == "M")
		person->gender = cPerson::MALE;
	else if (firstnameList.Get(1) == "F")
		person->gender = cPerson::FEMALE;
	else
		person->gender = cPerson::NON_BINARY;
	person->last = lastnameList.Get(0).c_str();
	person->middle = "";
	strcpy(person->postalCode, GenerateRandomChars().c_str());
	person->province = "";
	person->SIN = index; // using generated index as SIN
	person->streetDirection = addressList.Get(3).c_str();
	person->streetName = addressList.Get(1).c_str();
	person->streetNumber = index; // using generated index as street number.
	person->streetType = addressList.Get(2).c_str();

	return person;
}

int cPersonGenerator::GenerateRandomNumber(int max)
{
	if (!seeded) {
		srand(time(0));
		seeded = true;
	}
	return rand() % (max - 0);
}

std::string cPersonGenerator::GenerateRandomChars()
{
	char exclude[7] = { ':', ';', '<', '=', '>', '?', '@' };
	if (!seeded) {
		srand(time(0));
		seeded = true;
	}

	std::string generatedString = "";
	unsigned char value;
	unsigned int min, max, range;
	min = 48;
	max = 84;
	range = max - min + 1;

	for (int i = 0; i < 6; i++) {
		value = rand() % range + min;
		for (int j = 0; j < 7; j++) {
			if (value == exclude[j])
				value = 'N';
		}
		generatedString += value;
	}

	return generatedString;
}


// Here's a simple way to load the comma delimited files:
bool readCSVFile(void)
{
	// Open the file
	std::ifstream namesFile("Names_2010Census.csv");
	if (!namesFile.is_open())
	{
		std::cout << "Didn't open file" << std::endl;
		return false;
	}

	// name,rank,count,prop100k,cum_prop100k,pctwhite,pctblack,pctapi,pctaian,pct2prace,pcthispanic
	// SMITH,1,2442977,828.19,828.19,70.9,23.11,0.5,0.89,2.19,2.4
	//
	// - rank is how popular the last name is, like 1st, 2nd, etc.
	// - count is how many people have that last name, so 2,442,977 people have last name "Smith"
	// - prop100k is the ratio per 100,000 people. Smith is 828.19, 
	//            meaning that there's a 828.19 out of 100,000 chance (0.82819% chance)
	//            that someone is named "Smith"

	std::string theLine;

	unsigned int lineCount = 0;
	while (std::getline(namesFile, theLine))
	{
		lineCount++;
		std::stringstream ssLine(theLine);

		std::string token;
		unsigned int tokenCount = 0;
		while (std::getline(ssLine, token, ','))
		{
			if (tokenCount == 0)
			{
				std::cout << token << std::endl;
			}
			// Ignore the other parts of the line
			tokenCount++;
		}
	}

	std::cout << "Lines read = " << lineCount << std::endl;

	return true;
}