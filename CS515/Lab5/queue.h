// Do not modify this file
#include <iostream>
#include <cstdlib>
#include <cassert>

#define MAX_CAP 10
using namespace std;

class queue{
private:
    int item[MAX_CAP];  // array for queue items
    int rear;       // index to rear of queue
    int front;      // index to front of queue
public:
    queue();        // constructor with default value
    void enqueue(const int); 
    int dequeue();
    void display(ostream &os);  // print to ostream 
    int size();         // return queue size
    bool empty();      
    bool full(); 
};
