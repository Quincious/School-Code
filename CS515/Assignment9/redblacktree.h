#ifndef REDBLACK_TREE
#define REDBLACK_TREE

#include<cmath>
#include<limits>
#include<iostream>
using namespace std;


class RedBlackNode {
    friend class RedBlackTree;
public:
    RedBlackNode();
    RedBlackNode(int newKey);
private:
    int key;
    bool red; // false if node is black
    RedBlackNode *left;
    RedBlackNode *right;
    RedBlackNode *parent;
};

class RedBlackTree {
public:
    RedBlackTree();
    ~RedBlackTree();
    void print() const;
    RedBlackNode* insert(int newkey);
    RedBlackNode* BSTinsert(int newkey);
    void leftrotate(RedBlackNode *);
    void rightrotate(RedBlackNode *);
    bool search(int key);
    ostream& dump(ostream &out);
private:
    RedBlackNode *root;
    RedBlackNode *nil;
    void destructCode(RedBlackNode *&);
    void printTree(ostream&, int, RedBlackNode *);
};

ostream& operator << (ostream &s, RedBlackTree &v);

#endif

