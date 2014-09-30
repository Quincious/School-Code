// Copyright 2013 KJ
// a set ADT implemented with an AVL tree
#ifndef _SET_H_
#define _SET_H_

#include <iostream>
#include <string>
#include <algorithm> // for max()
using namespace std;

typedef int ELEMENT_TYPE;  // a set for elements of ELEMENT_TYPE

class Set {
 private:
    struct Elem {
        ELEMENT_TYPE info;
        Elem *left;
        Elem *right;
        int height;
        
        // Elem constructor
        Elem(const ELEMENT_TYPE &theElement, Elem *theLeft, Elem *theRight, int h = 0)
                    : info(theElement), left(theLeft), right(theRight), height(h) {}
    };
    
    Elem *_root;
    int _size;

    // common code for deallocation
    void destructCode(Elem *&);
    
    // common copy code for copying a tree recursively
    Elem* copyCode(Elem *);
    
    // helper method for inserting a node
    void insert(ELEMENT_TYPE, Elem *&);
    
    // helper method for deleting a node
    void erase(ELEMENT_TYPE, Elem *&);

    // helper method for finding a node
    Elem* find(ELEMENT_TYPE, Elem *);
    
    // helper method to return the address of the minimum node in the tree
    Elem* findMin(Elem *node);
    
    // print out the tree level by level
    void printTree(int, Elem *);
    
    // single right rotation
    void rotateRight(Elem *&);
    
    // single left rotation
    void rotateLeft(Elem *&);
    
    // double right rotation
    void doubleRotateRight(Elem *&);
    
    // double left rotation
    void doubleRotateLeft(Elem *&);
    
    // return the height of a node
    int height(Elem *);

 public:
    
    // default constructor; constructs empty set
    Set();

    // copy constructor
    Set(const Set&);
    
    // destructor
    ~Set();

    // assignment operator
    Set& operator=(const Set&);
    
    // insert an element into the set;
    void insert(ELEMENT_TYPE);

    // remove an element from the set;
    void erase(ELEMENT_TYPE);

    // If found, return true
    bool find(ELEMENT_TYPE) const;

    // return size of the set
    int size() const;

    // print tree in laying down
    void printTree();

    // outputs information in tree in inorder traversal order
    ostream& dump(ostream& out);
};

// outputs using overloaded << operator
ostream& operator<< (ostream&, Set&);

#endif  // _SET_H_
