/** CS515 Assignment1
	File: crypto.cpp, mybreak.cpp
	Name: Jonathan Hart
	Section: 2
	Date: 9/15/13
	Collaboration Declaration: none
	*/

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

bool CheckKey(string);
void Encrypt(string, string, string);
void Decrypt(string, string, string);

int main(int argc, char ** argv)
{
	if(argc != 5)
	{
		cout << "Incorrect number of arguments!" << endl;
		return -1;
	}

	string mode = argv[1];

	if(mode != "e" && mode != "d")
	{
		cout << "Must enter e for encryption or d for decryption!" << endl;
		return -1;
	}

	string key = argv[2];

	if(!CheckKey(key))
		return -1;

	string inputFileName = argv[3];
	string outputFileName = argv[4];
		
	if(mode == "e")
		Encrypt(inputFileName, outputFileName, key);
	else if(mode == "d")
		Decrypt(inputFileName, outputFileName, key);
 
}

bool CheckKey(string key)
{
	if(key.size() > 10)
	{
		cout << "Key must be 10 characters or less!" << endl;
		return false;
	}

	for(int i = 0; i < key.size(); i++)
    {
		if(key[i] < 'a' || key[i] > 'z')
		{
			cout << "Invalid Key. Must contain only lower case letters!" << endl;
			return false;
		}
    }

	return true;
}

void Encrypt(string inputFileName, string outputFileName, string key)
{
	ifstream inputFile(inputFileName);

	if(!inputFile)
	{
		cout << "Input File Does Not Exist!";
		return;
	}

	ofstream outputFile(outputFileName);

	char c;

    for(int i = 0, j = 0; inputFile.get(c); i++)
    { 
		if(c >= 'A' && c <= 'Z')//put uppercase letters to lower case
			c = tolower(c);
		else if((c < 'A' || c > 'Z') && !(c >= 'a' && c <= 'z'))//for non letter characters
		{
			outputFile.put(c);//add to out then go to next character
			continue;
		}
 
		outputFile.put((c + key[j] - 2*'a') % 26 + 'a'); 
		j = (j + 1) % key.length();
    }
 
}

void Decrypt(string inputFileName, string outputFileName, string key)
{
	ifstream inputFile(inputFileName);

	if(!inputFile)
	{
		cout << "Input File Does Not Exist!";
		return;
	}

	ofstream outputFile(outputFileName);

	char c;
 
    for(int i = 0, j = 0; inputFile.get(c); i++)
    {
 
		if(c >= 'A' && c <= 'Z')//put uppercase letters to lower case
			c = tolower(c);
		else if((c < 'A' || c > 'Z') && !(c >= 'a' && c <= 'z'))//for non letter characters
		{
			outputFile.put(c);//add to out then go to next character
			continue;
		}
 
		outputFile.put((c - key[j] + 26) % 26 + 'a'); 
		j = (j + 1) % key.length();
    }
}