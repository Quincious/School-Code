	/**   CS515 Lab7
	File: skiplist.cpp, map.cpp
	Name: Jonathan Hart
	Section: 2
	Date: 10/11/13
	Collaboration Declaration: Ian D'Elia
	*/

#include "map.h"


// operator [] will search for the key first.
// If the key exist in the map, return the data associated with the key.
// if the key doesn't exist in the map, then insert a new entry
// with the key and return the data (an empty set)

T&  Map::operator[](KEY key){
   // fill in here
			
	if(find(key) == end())
	{
		Set *a = new Set();
		
		Elem *el = new Elem;
		el->key = key;
		el->data = *a;
		
		Elem *cur = _head->next;
		while(cur != _tail)
		{
			if(cur->key > key)
				break;
			cur = cur->next;
		}
		
		el->next = cur;
		el->prev = cur->prev;
		cur->prev->next = el;
		cur->prev = el;
		_size++;
		
		delete a;
		
		return find(key)->data;
	}
	else
	{
		return find(key)->data;
	}
   
}
