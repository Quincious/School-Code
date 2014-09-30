// The program will print out the content in arrays by calling printIntArray


#include <iostream>
using namespace std;

// print an array of integers, all on one line.
void printIntArray(int *a, int n){
    for (int i=0; i<n; i++)  
        cout << a[i] << " ";
    cout << endl; 
}

int main(){
    // test 1
    int arr1[] = {90,11,20};
    printIntArray(arr1, 3);
    
    // test 2
    int arr2[] = {19,21,90,11,20,19,45,3,44,52};
    printIntArray(arr2, 10);
}

/*
In line 10 the for loop was comparing n to 1 everytime which gets you 
nowhere.
*/