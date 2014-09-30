/** CS515 Lab 3
	File: debug1.cpp, debug2.cpp, debug_result1, debug_result2, toUpper.cpp, countFreq.cpp
	Name: Jonathan Hart
	Section: 2
	Date: 9/11/13
	Collaboration Declaration: Jake Woodward
*/

#include <iostream>
#include <cstring>   // for strlen()
#include <cstdlib>   // for rand()
using namespace std;

/******************************************************************
 *   maxIndex returns the index of the first max element in the array
 *   displayArr prints out all array index and array elements. 
 *   The two functions are tested with two arrays created in the main() function. 
 ******************************************************************/

int maxIndex(int arr[], int size){
    int maxIndex = 0, max = 0;
    int i;
    for(i=0; i<size; i++){
       if (arr[i] > max){
          max = arr[i];
          maxIndex = i;
       }
    }
    return maxIndex;
}

void displayArr(int arr[], int size){
    int i;
    for(i=0; i<size; i++) 
    	cout << i << ": " << arr[i] << endl;
}

int main(){
    int s1[8] = {0};  // initialize array
    int s2[100] = {0};
    srand (time(NULL));    
    for(int i=0; i<8; i++)
    	s1[i] = rand() % 100;
    for(int i=0; i<100; i++)
    	s2[i] = rand() % 100;
    	
    int max_index; 	
    displayArr(s1, 8);  // display array s1
    max_index = maxIndex(s1, 8);
    cout << "Max value is " << s1[max_index] << " at index " << max_index << endl;
    
    displayArr(s2, 100);  // display array s2
    max_index = maxIndex(s2, 100);
    cout << "Max value is " << s2[max_index] << " at index " << max_index << endl;
}



