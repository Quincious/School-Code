#ifndef CUCKOO_HASH_H
#define CUCKOO_HASH_H

// Hash table implementation for a string SET adt.
// Use Cuckoo Hashing

#define numOfTables 3  // number of tables

#include <string>
using namespace std;

class HashTable{
  public:
    HashTable();
    ~HashTable();
    bool insert(const string & x);
    bool remove(const string & x);
    bool find(const string & x) const;
    int size();

  private:
    struct HashEntry{
        string element;  // stores only the key string
        bool isActive;
        HashEntry( string info = "", bool a = false )
          : element( info ), isActive( a ) { }
    };
    
    HashEntry ** array;  // pointers to table arrays
    int tablesize;  // size of each table
    int entrysize;  // total number of elements in the hash table
    int findPos(const string & x, int & n) const; // find the position of an element
    void rehash();  // increase the size of each table and rehash all element
};

unsigned int hash( const string & key, int which );
bool isPrime( int n );
int nextPrime( int n );

#endif
