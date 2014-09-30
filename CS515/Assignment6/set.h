// set implemented with doubly and head sentinal linked list

#ifndef INTSET_H
#define INTSET_H
#include <iostream>
using namespace std;

template<typename T>
class Set{
 private:
    struct Elem {
        T info;
        Elem *prev, *next;
    };
    Elem *_head, *_tail;
    int _size;
    
    // common code for copy constructor and assignment
    void copyCode(const Set & v);
    
    // common code for deallocation
    void destructCode();
   
    public:
    class Iterator{
    public:
        Iterator(){}
        explicit Iterator(Elem *cur):_cur(cur) {}
        Elem& operator*(){ return *_cur; }
        Elem* operator->(){ return _cur; }
        Iterator operator++(int){
            Iterator res = *this; _cur = _cur->next; return res;
        };
        Iterator operator--(int){
            Iterator res = *this; _cur = _cur->prev; return res;
        };
        bool operator==(Iterator it){
            return _cur == it._cur;
        }
        bool operator!=(Iterator it){
            return _cur != it._cur;
        }
    private:
        Elem* _cur;
    };
    Iterator begin() const { return Iterator(_head->next); }
    Iterator end() const { return Iterator(_tail); }
    
    // constructs empty set
    Set();
  
    // copy constructor
    Set(const Set &rhs);
   
    // destructor
    ~Set();
    
    // assignment operator
    Set& operator=(const Set &rhs);
    
    // insert an element into the Set; return true if successful
    bool insert(T);
    
    // remove an element from the Set; return true if successful
    bool erase(T);
    
    // return an iterator pointing to the end if an element is not found
    // otherwise, return an iterator to the element
    Iterator find(T) const;
    
    // remove all elements from Set
    void clear();

    // return size of the Set
    int size() const;
    
    // output set elements
    ostream& dump(ostream& out, const Set &v) const;
    

};

template<class T>
ostream& operator<< (ostream&, const Set<T>&);

#include "set.cpp"   // must include source file for template compilation
#endif
