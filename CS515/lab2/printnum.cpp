/** CS515 Lab 2
	File: debug1.cpp, debug2.cpp, results, myatoi.cpp, printnum.cpp
	Name: Jonathan Hart
	Section: 2
	Date: 9/4/13
	Collaboration Declaration: Bradley Snay
*/

#include <iostream>
#include <string>
using namespace std;

void PrintLargestofNDigits(int n) {
	char arr[101];
   for(int i = 0; i < n ; i++){
	   arr[i] = '9';
   }
   arr[n] = '\0';
   cout<< arr;
}

// main as test driver
// the basic test cases are included in file "input1"
int main(){
    int x;
    while ( cin >> x  ){
        PrintLargestofNDigits(x);
        cout << endl;
    }
}

