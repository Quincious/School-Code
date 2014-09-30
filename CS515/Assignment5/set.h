// a string set implemented with sorted doubly linked list with dummy header and tail nodes. 
// the set supports iterator for set traversal. 


#ifndef SET_H
#define SET_H
#include <iostream>
#include <string>

using namespace std;
typedef string ELEMENT_TYPE;  // a set for string elements


class Set{
private:
    struct Elem {
        ELEMENT_TYPE info;
        Elem *prev, *next;
    };
    
    // dummy header and tail nodes
    Elem *_head, *_tail;
    
    int _size;
    
    // common code for copy constructor and assignment
    void copyCode(const Set & v);
    
    // common code for deallocation
    void destructCode();
    
    // output set elements
    ostream& dump(ostream& out, const Set &v);
    
public:
    class Iterator{
    public:
        Iterator(){}
        explicit Iterator(Elem *cur) :_cur(cur) {}
        
        // overloaded dereference operator
        ELEMENT_TYPE& operator*();
        
        // overloaded post-increment operator
        Iterator operator++(int); 
        
        // overloaded post-decrement operator
        Iterator operator--(int);
        
        // overloaded equality operator
        bool operator==(Iterator it);
        
        // overloaded inequality operator
        bool operator!=(Iterator it);
        
    private:
        Elem* _cur;
    };
    
    // constructs empty set
    Set();
    
     // copy constructor
    Set(const Set &rhs);
    
    // destructor
    ~Set();
    
    // assignment operator
    Set& operator=(const Set &rhs);
    
    // insert an element
    void insert(ELEMENT_TYPE);
    
    // remove an element from the set
    void erase(ELEMENT_TYPE);
    
    // remove all elements from set
    void clear();
    
    // return size of the set
    int size() const; 
    
    // return an iterator to the element if val is found, or set::end() otherwise.
    Iterator find(ELEMENT_TYPE) const;
    
    // return an interator pointing at the begining of the list
    Iterator begin() const;
    
    // return an interator pointing at one element beyond the list
    Iterator end() const;
    
    // friend top level function for output
    friend ostream& operator<< (ostream&, Set&);
};

// set join and intersect
Set operator&(const Set&, const Set&);
Set operator|(const Set&, const Set&);

// set difference 
Set operator-(const Set&, const Set&);

// set equality
bool operator==(const Set& s1, const Set& s2);

#endif
