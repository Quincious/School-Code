/**   CS515 Lab4
File: queue.cpp, stack.cpp
Name: Jonathan Hart
Section: 2
Date: 09/25/13
Collaboration Declaration: Ian D'Elia
*/
#include "queue.h"

queue::queue(){
    rear = 0;
    front = 0;
}

// precondition: queue is not full 
void queue::enqueue(int data){
    item[(rear) % MAX_CAP] = data;	
	rear++;
}

// precondition: queue is not empty
int queue::dequeue(){
	int retVal = item[front % MAX_CAP ];
	front++;
	
    return retVal;
}

void queue::display(ostream &os){
	int tempFront = front;
	
    for(int i=0; i<= size() - 1;i++)
	{
        os<<item[(tempFront) % MAX_CAP]<<endl;
		tempFront++;
	}
}

int queue::size(){
    return (rear - front );
}

bool queue::empty(){
    return (front == rear) ;
}

bool queue::full(){
    return (size() >= MAX_CAP);
    
}
