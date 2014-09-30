// test driver that uses Binary Search Tree insert
// You can use this driver to test your rotation methods


#include "redblacktree.h"

int main(){
    int i;
    RedBlackTree t;
    RedBlackNode * ptr;
    
    i = 3;
    ptr = t.BSTinsert(i);
    cout << "****insert " << i << "************************************" << endl;
    cout << t;
    
    i = 22;
    t.BSTinsert(i);
    cout << "****insert " << i << "************************************" << endl;
    cout << t;
    
    i = 15;
    t.BSTinsert(i);
    cout << "****insert " << i << "************************************" << endl;
    cout << t;

    i = 2;
    t.BSTinsert(i);
    cout << "****insert " << i << "************************************" << endl;
    cout << t;
    
    i = 12;
    t.BSTinsert(i);
    cout << "****insert " << i << "************************************" << endl;
    cout << t;
    
    i = 25;
    t.BSTinsert(i);
    cout << "****insert " << i << "************************************" << endl;
    cout << t;

    cout << "****right rotate at 3************************************" << endl;
    t.rightrotate(ptr);
    cout << t;
}