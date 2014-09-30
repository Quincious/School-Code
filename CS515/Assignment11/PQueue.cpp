/*
CS515 Assignment 11
File: HuffTree.cpp, PQueue.cpp, HuffTree.h, PQueue.h
Name: Jonathan Hart
Section: 2
Date: 11/19/2013
Collaboration Declaration: Red Bull
*/ 

template<class T, int MAX_SIZE>
PQueue<T,MAX_SIZE>::PQueue() // default constructor
{
	_size = 0;
}

template<class T, int MAX_SIZE>
void PQueue<T,MAX_SIZE>::insert(T input) // insert an item; duplicates are allowed.
{
	_size++;
	_array[_size] = input;	
	
	if(_size > 1)
		moveUp();
}

template<class T, int MAX_SIZE>
T PQueue<T,MAX_SIZE>::findMin() // return the smallest item from the queue
{
	return _array[1];	
}

template<class T, int MAX_SIZE>
void PQueue<T,MAX_SIZE>::deleteMin() // remove the smallest item from the queue
{	
	if(_size > 0)
	{
		_array[1] = _array[_size];
		_size--;	
		
		moveDown(1);
	}
}

template<class T, int MAX_SIZE>
bool PQueue<T,MAX_SIZE>::isEmpty() // test if the priority queue is logically empty
{
	return _size == 0; 
}

template<class T, int MAX_SIZE>
int PQueue<T,MAX_SIZE>::size() // return queue size
{
	return _size;
} 

template<class T, int MAX_SIZE>
void PQueue<T,MAX_SIZE>::moveDown(int index)// move down element at given index
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

template<class T, int MAX_SIZE> 
void PQueue<T,MAX_SIZE>::moveUp() // move up the last element in the heap
{
	int index = _size;
	int parentIndex = index/2;
	T temp;
	
	while(_array[index] < _array[parentIndex])
	{
		temp = _array[parentIndex];
		_array[parentIndex] = _array[index];
		_array[index] = temp;
		index = parentIndex;
		parentIndex = index/2;
		if(index <= 1)
			break;
	}
}
