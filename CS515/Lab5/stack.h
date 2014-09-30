// Do not modify this file
#include <iostream>
#include <cassert>
using namespace std;

#define INITCAP 8

class stack{
public:
    stack(int=INITCAP);               // constructor with default value
    stack(const stack&);              // copy constructor
    stack& operator=(const stack&);  // assignment operator
    ~stack();                        // destructor
    void push(const int x);   // push an element
    void pop();         // remove and element,
    int& top();         // access next element without popping
    bool empty();       // test whether stack is empty
    int  size();        // return the number of elements on stack
    int  capacity();    // return the current capacity of the stack
    void print(std::ostream& os); // print stack content to ostream       
private:
    int * _arr;     // pointer to dynamic array
    int _tos;       // index to top of stack
    int _capacity;  // current capacity 
};
 
