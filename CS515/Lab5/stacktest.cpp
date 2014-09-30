// This test driver tests stack constructors and public interface methods using asserts

#include "stack.h"

int main(){
    stack mystack;
    
    cout << "testing empty stack" << endl;
    assert(mystack.size()==0);
    assert(mystack.capacity()==8);
    assert(mystack.empty()==true);
    
    
    cout << "...done\ntesting stack operations" << endl;
    mystack.push(2);
    mystack.push(4);
    mystack.push(6);
    mystack.push(8);
    mystack.push(10);
    mystack.push(12);
    assert(mystack.size()==6);
    assert(mystack.capacity()==8);
    assert(mystack.empty()==false);
    
    assert(mystack.top()==12);
    mystack.pop();
    assert(mystack.top()==10);
    mystack.pop();
    assert(mystack.size()==4);
    assert(mystack.capacity()==8);
    assert(mystack.empty()==false);
    
    // push more and check for capacity growth
    mystack.push(14);
    mystack.push(16);
    mystack.push(18);
    mystack.push(20);
    mystack.push(22);
    mystack.push(24);
    assert(mystack.size()==10);
    assert(mystack.capacity()==16);
    assert(mystack.empty()==false);
    assert(mystack.top() == 24);
    
    cout << "...done\ntesting copy constructor" << endl;
    stack newstack = mystack;
    assert(newstack.size()==10);
    assert(newstack.capacity()==16);
    assert(newstack.empty()==false);
    
    // check values on new stack
    assert(newstack.top()==24);
    newstack.pop();
    assert(newstack.top()==22);
    newstack.pop();
    assert(newstack.top()==20);
    newstack.pop();
    assert(newstack.top()==18);
    newstack.pop();
    assert(newstack.top()==16);
    newstack.pop();
    assert(newstack.top()==14);
    newstack.pop();
    assert(newstack.top()==8);
    newstack.pop();
    assert(newstack.top()==6);
    newstack.pop();
    assert(newstack.top()==4);
    newstack.pop();
    assert(newstack.top()==2);
    newstack.pop();
    
    assert(newstack.size()==0);
    assert(newstack.capacity()==16);
    assert(newstack.empty()==true);

    // check original stack here
    assert(mystack.top()==24);
    assert(mystack.size()==10);
    assert(mystack.capacity()==16);
    assert(mystack.empty()==false);
    
    // add more value and check stack growth
    for (int i=0; i<100; i++) {
        mystack.push(i);
    }
    assert(mystack.top()==99);
    assert(mystack.size()==110);
    assert(mystack.capacity()==128);
    cout << "...done\n";

}

