// set implemented with doubly and head sentinal linked list

#ifndef SET_H
#define SET_H
#include <iostream>
using namespace std;
typedef int ELEMENT_TYPE;


class Set{
public:
    // constructs empty set
    Set();
  
    // copy constructor
    Set(const Set &rhs);
   
    // destructor
    ~Set();
    
    // assignment operator
    Set& operator=(const Set &rhs);
    
    // insert an int into the set; 
    void insert(ELEMENT_TYPE);
    
    // remove an int from the set; 
    void erase(ELEMENT_TYPE);
    
    // remove all elements from set
    void clear();

    // return size of the set
    int size() const;
  
    // return true if an element is found; false otherwise
    bool find(ELEMENT_TYPE) const;
        
private:
    struct Elem {
        ELEMENT_TYPE info;
        Elem *prev, *next;
    };
    Elem *_head, *_tail;
    int _size;
    
    // common code for copy constructor and assignment
    void copyCode(const Set & v);
    
    // common code for deallocation
    void destructCode();
    
    // private method for output set elements
    ostream& dump(ostream& out, const Set &v) const;
    
    friend ostream& operator<< (ostream&, const Set&);
};

#endif
