/**   CS515 Lab13
File: connectChecker.cpp
Name: Jonathan Hart
Section: 2
Date: 11/20/13
Collaboration Declaration: Ian D'Elia
*/

#include <iostream>
#include <map>
#include <list>
#include <string>
#include <set>
using namespace std;

bool found;

void findPath(char key, char endPoint, map<char, list <char> > connections, set<char> visited)
{	
	if(visited.find(key) != visited.end())
	{
		return;
	
    }
	else if(connections.find(key) != connections.end())
	{
		list<char>::iterator it = connections[key].begin();
		
		while(it != connections[key].end() && !found)
		{
			if(*it == endPoint)
			{
				found = true;
				return;
			}
			visited.insert(key);
			findPath(*it, endPoint, connections,visited);
			it++;
		}	
	}
}

int main()
{
	map<char, list <char> > connections;
	
	string input;
	
	while(getline(cin, input))
	{
		found = false;
		char key = input[0];
		
		if(key != '?')
		{
			string charToInsert = "";
			
			for(size_t i = 1; i < input.length(); i++)
			{
				if(!isspace(input[i]))
					charToInsert += input[i];			
			}
			
			for(size_t i = 0; i < charToInsert.length(); i++)
			{
				connections[key].push_back(charToInsert[i]);
			}
			
			//cout << key << ": ";
			
			//list<char>::iterator it = connections[key].begin();
			
			//while(it != connections[key].end())
			//{
				//cout << *it << " ";
				//it++;
			//}
			
			//cout << endl;
		}
		else
		{
			char start = input[2];
			char endPoint = input[4];
			
			
			if(connections.find(start) != connections.end())
			{
				list<char>::iterator it = connections[start].begin();
				
				while(it != connections[start].end() && !found)
				{
					if(*it == endPoint)
					{
						found = true;
						break;
					}
					
					set<char> visited;	
					visited.insert(start);
					findPath(*it, endPoint, connections, visited);
					it++;
				}
			}	
			
			cout << "from " << start << " to " << endPoint << " : ";
			
			if(found)
				cout << "path found." << endl;
			else
				cout << "path not found" << endl;
			
		}
	}
}

