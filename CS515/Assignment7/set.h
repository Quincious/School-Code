// Copyright 2013 KJ
// a set implemented with right-threaded BST with a dummy root node
#ifndef _SET_H_
#define _SET_H_

#include <iostream>
#include <string>
#include <limits>
#include <queue>
using namespace std;

typedef int ELEMENT_TYPE;  // a set for string elements

class Set {
 private:
    struct Elem {
        ELEMENT_TYPE info;
        Elem *left;
        Elem *right;
        bool rightThread;  // normal right child link or a thread link
    };
    Elem *_root;
    int _size;

    // helper method for inserting record into tree.
    bool insert(Elem *& root, const ELEMENT_TYPE &value, Elem * lastLeft);

    // common code for deallocation
    void destructCode(Elem *&);

 public:
    class Iterator {
    public:
        Iterator() {}
        explicit Iterator(Elem *cur):_cur(cur) {}
        Elem& operator*();
        Elem* operator->();

        // overload only ++ operator (no -- operator)
        // operator++ will move current iterator to the in-order successor node
        Iterator operator++(int);

        // overload equality/inequality operators
        bool operator==(Iterator);
        bool operator!=(Iterator);
    private:
        Elem* _cur;
    };

    // return the first element in the container
    // (the left most (smallest) tree node in this case)
    Iterator begin() const;

    // return the past-the-end element in the container
    // (the dummy root in this case)
    Iterator end() const;

    // default constructor; constructs empty set
    Set();

    // destructor
    ~Set();

    // insert an element into the set;
    bool insert(ELEMENT_TYPE);

    // remove an element from the set;
    bool erase(ELEMENT_TYPE);

    // If found, return an iterator points to the element;
    // otherwise returns an iterator to set::end()
    Iterator find(ELEMENT_TYPE) const;

    // return size of the set
    int size() const;

    // output set elements
    void printTree(ostream&, int, Elem*);

    // print out tree elements in depth first in order
    void depthFirstInOrder();

    // print out tree elements in breadth first order
    void breadthFirst();

    // outputs information in tree in inorder traversal order
    ostream& dump(ostream& out);
};

// outputs using overloaded << operator
ostream& operator<< (ostream&, Set&);

#endif  // _SET_H_
