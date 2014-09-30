	/**   CS515 Lab11
	File: cuckoo.cpp
	Name: Jonathan Hart
	Section: 2
	Date: 11/6/13
	Collaboration Declaration: Ian D'Elia
	*/


#include "cuckoo.h"
#include <cstdlib>
#include <iostream>
using namespace std;


// Construct the hash table.
HashTable::HashTable(){
    srand(time(0));
    tablesize = nextPrime(101); // initial table size
    entrysize = 0;
    array = new HashEntry*[numOfTables];
    for ( int i =0; i<numOfTables; i++){
        array[i] = new HashEntry[tablesize];
    }
}

HashTable::~HashTable(){
    for (int i=0; i<numOfTables; i++){
        delete [] array[i];
    }
    delete [] array;
}


// Insert item newkey into the hash table.
// return false if item is already in the table
// otherwise, insert element and return true
// rehash if eviction loop is detected
// YOU DON'T NEED TO IMPLEMENT REHASH FOR LAB SUBMISSION
bool HashTable::insert( const string & newkey ){
	
	int count = 0;
	string wordToInsert = newkey;
	
	if(find(newkey))
		return false;
	
	while(true)
	{
		unsigned int key = hash(wordToInsert, count) % tablesize;
		
		if(!array[count][key].isActive )//empty location!!!!
		{
			array[count][key].element = wordToInsert;
			array[count][key].isActive = true;
			entrysize++;
			return true;
		}
		else//word already in spot
		{
			string temp = wordToInsert;
			wordToInsert = array[count][key].element;
			array[count][key].element = temp;
						
			count++;
			if(count == numOfTables)
				count = 0;
		}				
	}
	
   // fill in here
}

// increase the size of each table and rehash all elements
void HashTable::rehash( ){
    // not implemented
}

// find position of an element in a table
// if found, set n to the table index and return x's position in this table
// if not found (in any table), set n to -1 and return -1;
int HashTable::findPos( const string & x, int & n) const{
    // fill in here
    
    for(int i = 0; i < numOfTables; i++)
	{
		unsigned int key = hash(x,i) % tablesize;
		if(array[i][key].element == x && array[i][key].isActive)
		{
			n = i;
			return key;		
		}
	}
   
    n = -1;
    return -1;
}

// Remove item x from the hash table. Return true if successufl, else false
bool HashTable::remove( const string & x ){
    // fill in here
    
    //bool removed = false;
    
    for(int i = 0; i < numOfTables; i++)
	{
		unsigned int key = hash(x,i) % tablesize;
		if(array[i][key].element == x && array[i][key].isActive)
		{
			array[i][key].isActive = false;
			entrysize--;
			return true;		
		}
	}
   
    return false;
}

// Find item x in the hash table. Return true if found, else false
bool HashTable::find( const string & x ) const{
   // fill in here
      
	for(int i = 0; i < numOfTables; i++)
	{		
		unsigned int key = hash(x,i) % tablesize;
		if(array[i][key].element == x && array[i][key].isActive)
			return true;		
		
	}
   
   return false;
	   
}

// return the total number of element in the hashtable.
int HashTable::size(){
    return entrysize;
}

// hash a string based on one of the three simple hash functions
// each hash function differ by three prime constant
unsigned int hash( const string & key, int which){
    unsigned int hashVal = 0;
    static int multiplier[] = {233, 113, 307}; // randomly selected 3 prime numbers
    for( int i = 0; i < key.length(); i++ )
        hashVal =  multiplier[which] * hashVal + key[i];
    return hashVal;
}

// Internal method to test if a positive number is prime (not efficient)
bool isPrime( int n ){
    if( n == 2 || n == 3 )
        return true;
    if( n == 1 || n % 2 == 0 )
        return false;
    for( int i = 3; i * i <= n; i += 2 )
        if( n % i == 0 )
            return false;
    return true;
}

// Internal method to return a prime number at least as large as n.
// Assumes n > 0.
int nextPrime( int n ){
    if( n % 2 == 0 )
        n++;
    for( ; !isPrime( n ); n += 2 )
        ;
    return n;
}


