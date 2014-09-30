// a generic Map implemented with doubly and head sentinal linked list


#ifndef MAP_H
#define MAP_H
#include <iostream>
#include <string>

using namespace std;

template <typename KEY, typename T>
class Map{
private:
    struct Elem {
        KEY key;
        T data;
        Elem *prev, *next;
    };
    Elem *_head, *_tail;
    int _size;
    
    // common code for copy constructor and assignment
    void copyCode(const Map & v);
    
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
    
    
    // constructs empty Map
    Map();
    
    // copy constructor
    Map(const Map &rhs);
    
    // destructor
    ~Map();
    
    // assignment operator
    Map& operator=(const Map &rhs);
    
    // insert an element into the Map; return true if successful
    bool insert(KEY, T);
    
    // remove an element from the Map; return true if successful
    bool erase(KEY);
    
    // remove all elements from Map
    void clear();
    
    // return size of the Map
    int size() const { return _size; }
    
    // return an iterator pointing to the end if an element is not found,
    // otherwise, return an iterator to the element
    Iterator find(KEY) const;
    
    T& operator[](KEY);
    // overloaded subscript operator
    
    // output Map elements
    ostream& dump(ostream& out, const Map &v) const;
    
    
};

template<typename KEY, typename T>
ostream& operator<< (ostream&, const Map<KEY, T>&);

#include "map.cpp"  // must include source file for template compilation
#endif
