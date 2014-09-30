/** CS515 Lab 3
	File: debug1.cpp, debug2.cpp, debug_result1, debug_result2, toUpper.cpp, countFreq.cpp
	Name: Jonathan Hart
	Section: 2
	Date: 9/11/13
	Collaboration Declaration: Jake Woodward
*/

#include <iostream>
#include <cstring>   // for strlen()
#include <fstream>
using namespace std;

int main(int argc, char *argv[])
{

char c;

if(argc < 3)
{
	cout << "Too Few Arguments";	
	return -1;
}

ifstream infile(argv[1]);

if(!infile)
{
	cout << "File Does Not Exist";
	return -1;
}

ofstream outfile(argv[2]);

while(infile.get(c))
{
	outfile.put(toupper(c));
}














}

