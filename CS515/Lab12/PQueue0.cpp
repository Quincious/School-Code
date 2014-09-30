	/**   CS515 Lab12
	File: PQueue0.cpp, PQueue.cpp, PQueue.h
	Name: Jonathan Hart
	Section: 2
	Date: 11/14/13
	Collaboration Declaration: Ian D'Elia
	*/


#include "PQueue0.h"

PQueue::PQueue() // default constructor
{
	_size = 0;
}

void PQueue::insert(T input) // insert an item; duplicates are allowed.
{
	_size++;
	_array[_size] = input;
	
	
	moveUp();
}

T PQueue::findMin() // return the smallest item from the queue
{
	return _array[1];	
}

void PQueue::deleteMin() // remove the smallest item from the queue
{	
	if(_size > 0)
	{
		_array[1] = _array[_size];
		_size--;	
		
		moveDown(1);
	}
}

bool PQueue::isEmpty() // test if the priority queue is logically empty
{
	return _size == 0; 
}

int PQueue::size() // return queue size
{
	return _size;
} 

void PQueue::moveDown(int index)// move down element at given index
{
	int child;
	T temp = _array[index];
	
	for(;index*2<= _size; index = child)
	{
		child = index * 2;
		
		if(child <= _size && _array[child+1] < _array[child])
			child++;
		
		if(_array[child] < temp)
			_array[index] = _array[child];
		else
			break;			
	}
	_array[index] = temp;
	
}
 
void PQueue::moveUp() // move up the last element in the heap
{
	int index = _size;
	
	while(_array[index] < _array[(index)/2] && index > 1)
	{
		T temp = _array[index];
		_array[index] = _array[(index)/2];
		_array[(index)/2] = temp;
		index = (index)/2;		
	}
}
