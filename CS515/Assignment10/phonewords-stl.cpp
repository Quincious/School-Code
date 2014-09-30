	/**   CS515 Assignment10
	File: phonewords-stl.cpp
	Name: Jonathan Hart
	Section: 2
	Date: 11/13/13 
	Collaboration Declaration: 
	*/

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <map>
#include <set>
using namespace std;

string GetNumberEquivalent(string word);
void GetWords(string input, int curIndex, string curWord);
bool CheckInput(string userInput);

map< string, set <string> > dictionary;

int main(int argc, char ** argv)
{
	if(argc != 2)
	{
		cout << "Must enter one and only one argument." << endl;
		return -1;
	}

	ifstream inputFile (argv[1]);

	if(!inputFile)
	{
		cout << "Invalid File." << endl;
		return -1;
	}
	
	
	if (inputFile.is_open())
	{
		string line;

		// Get every line
		while (getline (inputFile, line))
		{
			//isolate words
			stringstream wordBuffer (line);
			string word;

			while (wordBuffer >> word)
			{
				string wordNum = GetNumberEquivalent(word);
				//cout << word << " - " << wordNum << endl; 
				dictionary[wordNum].insert(word);
			}
		}

		inputFile.close();
	}
	
	//Insert 0 and 1 into dictionary.
	dictionary["0"].insert("0");
	dictionary["1"].insert("-");

	string userInput;
	cout << "Please enter a 10 digit number" << endl;

	while(getline(cin, userInput))
	{
		if(userInput.length() != 10 || !CheckInput(userInput))
			cout << "Invalid input. Please enter a 10 digit number!" << endl;
		else
			GetWords(userInput, 0, "");		

		cout << "Please enter a 10 digit number" << endl;
	}
	return 0;
}

string GetNumberEquivalent(string word)
{
	string wordNumber = "";

	for(int i = 0; i < word.length(); i++)
	{
		switch(word[i])
		{
		case 'a': case 'b': case 'c':
			wordNumber = wordNumber + '2';
			break;
		case 'd': case 'e': case 'f':
			wordNumber = wordNumber + '3';
			break;
		case 'g': case 'h': case 'i':
			wordNumber = wordNumber + '4';
			break;
		case 'j': case 'k': case 'l':
			wordNumber = wordNumber + '5';
			break;
		case 'm': case 'n': case 'o':
			wordNumber = wordNumber + '6';
			break;
		case 'p': case 'q': case 'r': case 's':
			wordNumber = wordNumber + '7';
			break;
		case 't': case 'u': case 'v':
			wordNumber = wordNumber + '8';
			break;
		case 'w': case 'x': case 'y': case 'z':
			wordNumber = wordNumber + '9';
			break;
		}
	}

	return wordNumber;
}

bool CheckInput(string userInput)
{
	for(int i = 0; i < userInput.length(); i++)
	{
		if(userInput[i] < '0' || userInput[i] > '9')
			return false;
	}

	return true;
}

void GetWords(string input, int curIndex, string curWord)
{
	for(int i = curIndex; i < input.length(); i++)
	{
		string word = "";
		for(int j = curIndex; j <= i; j++)
			word = word + input[j];		

		if(dictionary.find(word) != dictionary.end())
		{
			set<string>::iterator it = dictionary[word].begin(); 

			while(it != dictionary[word].end())
			{
				string tempWord = curWord + *it + " ";
				if(i == input.length() - 1)
					cout << tempWord << endl;
				else
					GetWords(input, i + 1, tempWord);

				it++;
			}
		}
	}
}