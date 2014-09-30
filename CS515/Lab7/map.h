// a Map to map string -> set of int
// implemented with sorted linked list


#ifndef MAP_H
#define MAP_H
#include <iostream>
#include <string>
using namespace std;
#include "set.h"

typedef string KEY;     // key is string type
typedef Set T;          // data is Set of ints

class Map{
private:
    struct Elem {
        KEY key;
        T data;
        Elem *prev, *next;
    };
    Elem *_head, *_tail;  // list sentinel
    int _size;
    
    // common code for copy constructor and assignment
    void copyCode(const Map & v);
    
    // common code for deallocation
    void destructCode();
    
    // helper method to output Map elements
    ostream& dump(ostream& out, const Map &v);
    
public:
    // iterator class for Map
    class Iterator{
    public:
        Iterator(){}
        explicit Iterator(Elem *cur):_cur(cur) {}
        Elem& operator*();
        Elem* operator->();
        Iterator operator++(int);
        Iterator operator--(int);
        bool operator==(Iterator);
        bool operator!=(Iterator); 
    private:
        Elem* _cur;
    };
    
    Map();
    Map(const Map &rhs);
    ~Map();
    Map& operator=(const Map &rhs);
    
    bool insert(KEY, T);
    bool erase(KEY);
    Iterator find(KEY);
    T& operator[](KEY);
    void clear();
    int size() const; 
    Iterator begin() const; 
    Iterator end() const; 
};

#endif
