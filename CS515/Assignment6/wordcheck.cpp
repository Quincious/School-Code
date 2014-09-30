#include "map.h"
#include "set.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
using namespace std;

bool onlyLetters(string s)
{
	for(int i = 0; i < s.size(); i++)
	{
		char c = s.at(i);
		
		 if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')))
			return false;
	}
	return true;
}

int main()
{
	Map<string, Set<string> > m0;
	Map<string, Set<string> > m1;
	Map<string, Set<string> > m2;
	Map<string, Set<string> > m3;
		
	ifstream dict("/usr/share/dict/words");
	
	if(!dict)
	{
		cout << "Error opening dictionary" << endl;
		return -1;
	}
	
	while(true)
	{
		string word;
		dict >> word;
		if(dict.eof())
			break;
			
		if(word.size() == 4)
		{
			if(onlyLetters(word))
			{	
				for(int i = 0; i < word.size();i++)
				{					
					if(word[i] <='Z' && word[i] >='A')
						word[i] = tolower(word[i]);
				}
				
				string removeFirst;
				string removeSecond;
				string removeThird;
				string removeFourth;
				
				removeFirst += word.at(1);
				removeFirst += word.at(2);
				removeFirst += word.at(3);
				
				removeSecond += word.at(0);
				removeSecond += word.at(2);
				removeSecond += word.at(3);
				
				removeThird += word.at(0);
				removeThird += word.at(1);
				removeThird += word.at(3);
				
				removeFourth += word.at(0);
				removeFourth += word.at(1);
				removeFourth += word.at(2);
								
				m0[removeFirst].insert(word);
				m1[removeSecond].insert(word);
				m2[removeThird].insert(word);
				m3[removeFourth].insert(word);				
			}
		}
	}
	
	string input;
	
	cout << "Please input a 4 letter word: ";	
	while(cin >> input)
	{
		if(input.size() == 4)
		{
			if(onlyLetters(input))
			{			
				for(int i = 0; i < input.size();i++)
				{					
					if(input[i] <='Z' && input[i] >='A')
						input[i] = tolower(input[i]);
				}
				
				string removeFirst;
				string removeSecond;
				string removeThird;
				string removeFourth;
				
				removeFirst += input.at(1);
				removeFirst += input.at(2);
				removeFirst += input.at(3);
				
				removeSecond += input.at(0);
				removeSecond += input.at(2);
				removeSecond += input.at(3);
				
				removeThird += input.at(0);
				removeThird += input.at(1);
				removeThird += input.at(3);
				
				removeFourth += input.at(0);
				removeFourth += input.at(1);
				removeFourth += input.at(2);
				
				Set<string> s0 = m0[removeFirst];
				Set<string> s1 = m1[removeSecond];
				Set<string> s2 = m2[removeThird];
				Set<string> s3 = m3[removeFourth];
				
				s0.erase(input);
				s1.erase(input);
				s2.erase(input);
				s3.erase(input);
				
				int totalWords = s0.size() + s1.size() + s2.size() + s3.size();
				
				cout << s0 << s1 << s2 << s3 << endl;
				cout << "Total " << totalWords << " words" << endl;
			}
			else
				cout << "Must only contain letters!" << endl;
		}
		else
			cout << "Wrong Length!" << endl;
		
		cout << "Please input a 4 letter word: ";		
	}
	
}