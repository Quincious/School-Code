/** CS515 Lab 2
	File: debug1.cpp, debug2.cpp, results, myatoi.cpp, printnum.cpp
	Name: Jonathan Hart
	Section: 2
	Date: 9/4/13
	Collaboration Declaration: Bradley Snay
*/

#include <iostream>
using namespace std;

// myatoi takes a string and converted it to an integer value. 
// if the string is empty or contains non-numeric characters
// 0 will be returned.
// numbers with a sign charactor (+ or -) are allowed.

int myatoi(const char * ptr){
	int retVal = 0;
	bool negative = false;
	
		if(ptr[0] == '+'){
			ptr++;
		}
		else if(ptr[0] == '-'){
			negative = true;
			ptr++;
		}
	
		while( *ptr != '\0' ){
			retVal *= 10;
			switch(*ptr){
				case '0':retVal += 0;
				break;
				
				case '1':retVal +=1;
				break;
				
				case '2':retVal += 2;
				break;
				
				case '3':retVal +=3;
				break;
				
				case '4':retVal += 4;
				break;
				
				case '5':retVal += 5;
				break;
				
				case '6':retVal += 6;
				break;
				
				case '7':retVal += 7;
				break;
				
				case '8':retVal += 8;
				break;
				
				case '9':retVal += 9;
				break;
					
				
				default: return 0;
			}
			ptr++;
		}
		if(negative == true){
			retVal = retVal - (retVal *2);
		}
		return retVal;
		
}

// main as test driver
// the basic test cases are included in file "input2"
int main(){
    string s;
    while ( cin >> s  )
        cout << myatoi(s.c_str()) << endl;
}
