/** CS515 Lab 2
	File: debug1.cpp, debug2.cpp, results, myatoi.cpp, printnum.cpp
	Name: Jonathan Hart
	Section: 2
	Date: 9/4/13
	Collaboration Declaration: Bradley Snay
*/

// The program will print out the factorial of a given number
#include <iostream>
using namespace std;

int main(){
    int num;
    int result = 1; 
    cout << "Enter the number: ";
    cin >> num;

    for (int i=1; i<= num; i++)
        result = result*i;    	

    cout << "The factorial of " << num << " is " << result << endl;
}

/*
Debugging info:

Result wasn't set to a number so it defaulted to zero therefore multiplying 
everything by zero.

The parameter for the for loop was excluding the last number in the factorial
because it wasn't set to <=.
*/
