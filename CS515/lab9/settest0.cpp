#include <iostream>
#include <cstdlib>
#include <cassert>
#include "set.h"
using namespace std;

int main(){
    Set t;
    int numbers[] = {50, 25, 75, 10, 30, 60, 80, 5, 15, 27, 55, 1};
    
    int size = 12;
    // try to insert a sorted set of numbers   
    for(int i = 0; i < size; i++){
        t.insert( numbers[i]);
        assert(t.size() == i+1); 
        t.printTree();
        cout << "************************************" << endl;
    }
    
    t.insert(80); // re-insert 80
    assert(t.size() == 12);
    t.printTree();
    cout << "************************************" << endl;    
    cout << "************ delete ****************" << endl;
    cout << "************************************" << endl;
    
    t.erase(80);
    assert(t.size() == 11);
    t.printTree();
    cout << "******************delete(80)******************" << endl;
    
    t.erase(80);  // re-erase 80
    assert(t.size() == 11);
    t.printTree();
    cout << "****************************delete(80)********" << endl;
    
    t.erase(15);
    assert(t.size() == 10);
    t.printTree();
    cout << "*******************delete(15)*****************" << endl;
    
    t.erase(1);
    assert(t.size() == 9);
    t.printTree();
    cout << "*********************delete(1)***************" << endl;
    
    t.erase(5);
    assert(t.size() == 8);
    t.printTree();
    cout << "*********************delete(5)***************" << endl;

    t.erase(10);
    assert(t.size() == 7);
    t.printTree();
    cout << "**********************delete(10)**************" << endl;

}
