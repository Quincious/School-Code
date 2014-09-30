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
#include <sstream>
using namespace std;

string GetFileContents(string);
int GetMaxLet(string);
string DoBreak(string, int);

int main(int argc, char **argv)
{

	if(argc != 3)
	{
		cout << "Incorrect Number of Arguments!" << endl;
		return -1;
	}

	string input = GetFileContents(argv[2]);	
	
	if(input == "")
		return -1;

	int keyLength;
	stringstream s(argv[1]);

	if(s >> keyLength)
	{
		string key = DoBreak(input, keyLength);	
		cout << key << endl;
	}
	else
	{
		cout << "Invalid Key Length Argument!" << endl;
		return -1;
	}

	return 0;
}

string GetFileContents(string filename)
{
	  ifstream in(filename);

	  if (in)
	  {
			string contents;
			in.seekg(0, in.end);
			contents.resize(in.tellg());
			in.seekg(0, in.beg);
			in.read(&contents[0], contents.size());
			in.close();
			
			return contents;
	  }
	  else
	  {
		  cout << "Error opening input file!" << endl;
		  return "";
	  }
}



int GetMaxLet(string input)
{
    int lettersInAlphabet = 26;
    char alphabet[] = {'a', 'b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    int letterCount[26];
    int maxLetterCount = 0;
    int indexOfHighestCount = 0;
       
    for(int i = 0;i<lettersInAlphabet;i++)
	{
        letterCount[i] = 0;
    }
    for(int i = 0; i<input.length();i++)
	{
        for(int j = 0; j<lettersInAlphabet;j++)
		{
            if(input.at(i)==alphabet[j])
			{
                letterCount[j]=letterCount[j]+1;
                break;
            }
        }
    }
    for(int i = 0; i<lettersInAlphabet;i++)
	{
        if(letterCount[i]>maxLetterCount)
		{
            indexOfHighestCount = i;
            maxLetterCount=letterCount[i];
        }
    }
    return indexOfHighestCount;
} 

string DoBreak(string ciphertext, int keyLength)
{
    char alphabet[] = {'a', 'b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    string key = "";
    int ciphertextLength = ciphertext.length();
       
    for(int i = 0; i<keyLength;i++)
	{
        string lettersAtMultiplesOfI = "";
        int startIndex = i;
        int currentIndex = startIndex;
        while(currentIndex<ciphertextLength)
		{
            lettersAtMultiplesOfI = lettersAtMultiplesOfI+ciphertext.at(currentIndex);
            currentIndex = currentIndex+keyLength;
        }
        int maxLetterIndex = GetMaxLet(lettersAtMultiplesOfI);
        int keyCharIndex = ((maxLetterIndex-4+26)%26);
        key = key+alphabet[keyCharIndex];
    }
    return key;
} 