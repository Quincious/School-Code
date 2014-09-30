/** CS515 Lab 3
	File: debug1.cpp, debug2.cpp, debug_result1, debug_result2, toUpper.cpp, countFreq.cpp
	Name: Jonathan Hart
	Section: 2
	Date: 9/11/13
	Collaboration Declaration: Jake Woodward
*/

#include <iostream>
#include <cstring>   // for strlen
using namespace std;

/******************************************************************
 *   appendStr returns the result of appending the characters in s2 to s1.
 *   Assumption: enough space has been allocated for s1 to store 
 *   the extra characters.
 *   The function is test with keyboard input values. 
 ******************************************************************/

char* appendStr(char s1[], char s2[]){
    int s1len = strlen(s1);
    int s2len = strlen(s2);
    for(int k = 0; k < s2len; k++){
        s1[k+s1len] = s2[k];
    }
    return s1;
}

int main(){
    char s1[256] = {'\0'};
    char s2[256] = {'\0'};
    while(1){
      cout << "s1? ";
      cin >> s1;
      cout << "s2? ";
      cin >> s2;
      cout << "s1 is: " << s1 << "\ns2 is: " << s2 << endl;
      cout << "Append result is: " << appendStr(s1, s2) << endl;
    }
    return 0;
}

