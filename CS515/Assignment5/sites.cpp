/** CS515 Assignment5
	File: sites.cpp, set.cpp
	Name: Jonathan Hart
	Section: 2
	Date: 12/13/13
	Collaboration Declaration: none
	*/

#include "set.h"
#include <cassert>
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char** argv)
{
	Set totalVisitors, visitedAll;
	Set inputSets[argc-1];
	Set uniqueInputSets[argc-1];
	int numberOfSets = argc-1;
	
	for(int i = 1; i < argc; i++)
	{
		ifstream inputFile(argv[i]);
		if(!inputFile)
			return -1;
		
		string ip;
		
		while(getline(inputFile, ip))
		{
			if(ip.size() > 0)
				inputSets[i-1].insert(ip);
		}
		
		inputFile.close();
	}
	
	
	for(int i = 0; i < numberOfSets; i++)
	{
		totalVisitors = totalVisitors | inputSets[i];
	}
	
	cout << "visitors of ANY " << numberOfSets << " sites: " << totalVisitors.size() << endl;
	
	visitedAll = inputSets[0];
	
	for(int i = 1; i < numberOfSets; i++)
	{
		visitedAll = visitedAll & inputSets[i];
	}	
	
	cout << "visitors of ALL " << numberOfSets << " sites: " << visitedAll.size() << endl;
	
	for(int i = 0; i < numberOfSets; i++)
	{
		uniqueInputSets[i] = inputSets[i];
		
		for(int j = 0; j < numberOfSets; j++)
		{
			if(i != j)
				uniqueInputSets[i] = uniqueInputSets[i] - inputSets[j];
		}		
	}
	
	for(int i = 0; i < numberOfSets; i++)
	{
		cout << "visitors of " << argv[i+1] << " but not of any of the other sites: " << uniqueInputSets[i].size() << endl;
	}
	
	return 0;
}