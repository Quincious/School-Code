/** CS515 Assignment1
	File: pizza.cpp
	Name: Jonathan Hart
	Section: 2
	Date: 9/7/13
	Collaboration Declaration: none
	*/

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main()
{
	string userInput;
	string roomName = "";
	string sliceInput;

	bool isInvalid = false;//use to check if input is invalid
	
	int boxCount = 0;
	int sliceCount = 0;

	while(getline(cin, userInput))//get whole line until /n
	{
		stringstream ss(userInput);

		ss >> roomName;// first input is room name

		while(ss >> sliceInput)//remaining inputs are for slice amounts
		{
			boxCount++;
			//cout << sliceInput << endl;
			
			if(sliceInput == "0" || sliceInput == "zero");
			else if(sliceInput == "1" || sliceInput == "slice")
				sliceCount++;
			else if(sliceInput == "2" || sliceInput == "quarter")
				sliceCount += 2;
			else if(sliceInput == "3")
				sliceCount += 3;
			else if(sliceInput == "4" || sliceInput == "half")
				sliceCount += 4;
			else if(sliceInput == "5")
				sliceCount += 5;
			else if(sliceInput == "6")
				sliceCount += 6;
			else if(sliceInput == "7")
				sliceCount += 7;
			else if(sliceInput == "8" || sliceInput == "whole")
				sliceCount += 8;
			else//will only reach here with invalid input
			{
				isInvalid = true;
				break;
			}

		}//end slice while loop

		if(roomName != "")//to ignore empty lines
		{
			if(!isInvalid)
			{			
				int boxesNeeded = 0;
				if(sliceCount > 0)//only do math if there are left over slices
					boxesNeeded = (sliceCount / 8) + 1;

				cout << roomName << " needs : " << boxesNeeded << " of the " << boxCount << " boxes." << endl;
			}
			else//when invalid input is entered.
			{
				cout << "Strange slices found in " << roomName << "! Please inform the physics police." << endl;
			}
		}

		//set variables back to default
		boxCount = 0;
		sliceCount = 0;
		roomName = "";
		isInvalid = false;
	}//end input while loop

	return 0;
}