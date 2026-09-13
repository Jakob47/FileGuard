
#include <iostream>
#include <string>
#include <fstream>
#include "sha256.h"
#include <vector>
#include <cstdio>


void space() {
	std::cout << "\n";
	std::cout << "\n";
	
}


int addingPath(std::string filePathp ,std::string hashValuep ,std::string inputOfFilep, char byte)
{
	std::cout << "which file do you want to scan please put the path? " << std::endl;

	// Get the file path from the user
	std::getline(std::cin >> std::ws, filePathp);

	std::cout << "Generating a hash for the selected file...\n";
	std::ifstream readfile(filePathp, std::ios::binary);

	if (!readfile)
	{
		std::cout << "File could not be opened" << std::endl;
		std::cout << "File does not exist or is not accessible" << std::endl;
		space();
		std::cin.get();
		return 1;
	}

	else
	{
		while (readfile.get(byte))
		{
			// Read the file byte by byte and store it in the inputOfFile string
			inputOfFilep += byte;
		}

		// Generate the hash value for the file content
		hashValuep = sha256(inputOfFilep);
		std::cout << "suceesfully generated hash for the selected file\n";
	}


	//store the file path in the meta.txt file
	std::ofstream newpath("meta.txt", std::ios::app);
	newpath << "Path =" << filePathp << "|";
	newpath << "Hash =" << hashValuep<< "|" << std::endl;
	std::cout << "Successfully stored file path and hash value in meta file\n";
	space();

}


int main() {

	//Variables
	std::string hashValue;
	std::string filePath;
	std::string inputOfFile;
	std::string line;
	std::vector<std::string> paths;
	std::vector<std::string> hashes;

	char userInput;
	int i = 0;


	char byte = 0;


	std::cout << R"(
  _____ _ _       ____                     _
 |  ___(_) | ___ / ___|_   _  __ _ _ __ __| |
 | |_  | | |/ _ \ |  _| | | |/ _` | '__/ _` |
 |  _| | | |  __/ |_| | |_| | (_| | | | (_| |
 |_|   |_|_|\___|\____|\__,_|\__,_|_|  \__,_|
)" << std::endl;

	std::ifstream existingmetafile("meta.txt");


	if (!existingmetafile)
	{
		std::cout << "could not find meta.txt file\n";
		std::cout << "creating meta.txt file\n";

		std::ofstream metafile("meta.txt");
		addingPath(filePath, hashValue, inputOfFile, byte);
		
	}


	std::ifstream proofMetaFileEmpty("meta.txt", std::ios::binary | std::ios::ate);
	if (!proofMetaFileEmpty)
	{
		std::cout << "could not open meta.txt file\n";
	}

	else if (proofMetaFileEmpty.tellg() == 0)
	{
		std::cout << "meta file is empty\n";
		std::ofstream newFile("meta.txt");
		addingPath(filePath, hashValue, inputOfFile, byte);

	}
	while (true)
	{
		std::cout << "Do u wanna put a another file path? (y/n): " << std::endl;
		std::cin >> userInput;
		
		if (userInput == 'y' || userInput == 'Y')
		{

			addingPath(filePath, hashValue, inputOfFile, byte);
		}
		else if (userInput == 'n' || userInput == 'N')
		{
			break;
		}
		else
		{
			std::cout << "Invalid input. Please enter 'y' or 'n'." << std::endl;
		}
	}
	
	std::ifstream readingPathFromMetaFile("meta.txt");
	std::cout << "reading meta file\n";
	while (getline(readingPathFromMetaFile, line))
	{
		std::size_t positionPath = line.find("Path =");
		std::size_t positionHash = line.find("Hash =");

		if (positionPath != std::string::npos)
		{
			i++;

			std::size_t startpath = positionPath + std::string("Path =").length();
			std::size_t endpath = line.find('|', startpath);

			std::size_t startHash = positionHash + std::string("Hash =").length();
			std::size_t endHash = line.find('|', startHash);

			std::string finalLine = line.substr(startpath, endpath - startpath);
			std::string finalHash = line.substr(startHash, endHash - startHash);

			paths.push_back(finalLine);
			hashes.push_back(finalHash);

			std::cout << i << ". Path found:" << finalLine << "\n";
			//std::cout << i << ". Hash value:" << finalHash << "\n";

		}
	}

	std::cout << "select one of the Paths" << std::endl;
	int selectedIndex;
	std::cin >> selectedIndex;
	space();

	if (selectedIndex >= 1 && selectedIndex <= paths.size() && selectedIndex <= hashes.size())
	{
		filePath = paths[selectedIndex - 1];
		hashValue = hashes[selectedIndex - 1];
		std::cout << "selceted path: " << filePath << std::endl;
	}

	else {
		std::cout << "Invalid input make sure the index is within the valid range" << std::endl;
		std::cin.get();
		return 1;
	}

	// Open the file from the path in binary mode
	std::ifstream file(filePath, std::ios::binary);

	if (file)
	{
		std::cout << "File opened successfully " << std::endl;
		space();

		// Read the file byte by byte
		while (file.get(byte)) {

			// Read the file byte by byte and store it in the inputOfFile string
			inputOfFile += byte;
		}

		std::string TemphashValue = sha256(inputOfFile);
		//std::cout << "TempHash value: " << TemphashValue << std::endl;
		//std::cout << "Hash value: " << hashValue << std::endl;

		if (TemphashValue == hashValue)
		{
			std::cout << "File File has not been modified" << std::endl;
		}
		else
		{
			std::cout << "File has been modified" << std::endl;
		}
	}

	else
	{
		std::cout << "File could not be opened" << std::endl;
		std::cout << "File does not exist or is not accessible" << std::endl;

		space();
		std::cin.get();
		return 1;

	}
	

		std::cin.get();
		std::cin.get();

		return 0;
	}
