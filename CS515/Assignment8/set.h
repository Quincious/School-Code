// Copyright 2013 KJ
// a set ADT implemented with a right-threaded AVL tree with a dummy root node
#ifndef _SET_H_
#define _SET_H_

#include <iostream>
#include <string>
#include <algorithm> // for max()
#include <limits>
using namespace std;

typedef int ELEMENT_TYPE;  // a set for elements of ELEMENT_TYPE

class Set {
private:
    struct Elem {
        ELEMENT_TYPE info;
        Elem *left;
        Elem *right;
        int height;  // node height
        bool rightThread;
        
        // Elem constructor
        Elem(){}
        Elem(const ELEMENT_TYPE &theElement, Elem *theLeft, Elem *theRight, int h = 0, bool rt = false)
        : info(theElement), left(theLeft), right(theRight), height(h), rightThread(rt) {}
    };
    Elem *_root;
    int _size;
    
    // common destruction code
    void destructCode(Elem *&);
    
    // helper method for inserting a node
    void insert(Elem *&, ELEMENT_TYPE, Elem *);
    
    // return the address of the minimum node in the tree
    Elem* findMin(Elem *node);
    
    // print out the tree level by level
    void printTree(ostream&, int, Elem *);
    
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
    
    // return the balance factor of a node
    int balanceFactor(Elem *cur);
    
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
    
    Iterator begin() const;
    Iterator end() const;
    
    // default constructor; constructs empty set
    Set();
    
    // destructor
    ~Set();
    
    // insert an element into the set;
    void insert(ELEMENT_TYPE);
    
    // If found, return an iterator points to the element;
    // otherwise returns an iterator to set::end()
    Iterator find(ELEMENT_TYPE) const;
    
    // return size of the set
    int size() const;
    
    // output set elements as an AVL tree lying down
    void printTree();
    
    // outputs information in tree in inorder traversal order
    ostream& dump(ostream& out);
};

// outputs using overloaded << operator
ostream& operator<< (ostream&, Set&);

#endif  // _SET_H_
