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
double freq[123]= {0};
double count = 0;

if(argc < 2)
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

while(infile.get(c))
{
	if((c>='a' && c<='z')||(c>='A' && c<='Z'))
	{
		freq[tolower(c)]++;
		count++;
	}
}

for(int i = 0; i<123; i++)
{
	if(freq[i])
	{
		cout << (char)i << " ";
		cout << freq[i]/count << endl;
	}	
		
}	













}
