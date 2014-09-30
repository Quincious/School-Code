/**   CS515 Lab4
File: debug.cpp
Name: Ian D'Elia
Section: 2
Date: 09/18/13
Collaboration Declaration: Jonathan Hart
*/
#include <iostream>
#include <cstdlib>
using namespace std;

int* initArray(int);
void fillArray(int *, int);
int* doubleArray(int *, int);
void displayArray(int *, int);

/* The program will create an array of given size
 * populate the array with random number from (0-99)
 * and display the array; then the program will double
 * the size of the array, repopulate the array and 
 * display it again.
 */


int main(int argc, char ** argv){
    if (argc != 2){
        cout << "wrong number of arguments" << endl;
        exit(1);
    }
    
    int n = atoi(argv[1]); // get size
    srand(time(0));
    
    // create initial array and display it
    int* ptr = initArray(n);
    fillArray(ptr, n);
    displayArray(ptr, n);
    
    // create the double sized array and display it
    ptr = doubleArray(ptr, n);
    fillArray(ptr, 2*n);
    displayArray(ptr, 2*n);
    delete [] ptr;
}

// Create an array of size n and return its address
int* initArray(int n){
    int* arr = new int[n];
    
    return arr;
}

// Fill array ptr with n random numbers
void fillArray(int *ptr, int n){
    for(int i=0; i<n; i++){
        ptr[i] = rand() % 100;
    }
}

// Double the size of the array, make sure no memory leak
int* doubleArray(int *ptr, int n){
    delete [] ptr;
    int size = 2*n;
    int * tmp = new int[size];
    ptr = tmp;
    
    return ptr;
}

// Display n array elements
void displayArray(int *ptr, int n){
    for(int i=0; i<n; i++){
        cout << ptr[i] << " ";
    }
    cout << endl;
}
