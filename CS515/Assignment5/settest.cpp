// test driver for set ADT with built-in iterator
#include "set.h"
#include <cassert>
#include <iostream>
using namespace std;


int main(){
    Set s1;
    Set::Iterator it; 
    
    s1.erase("a");
    s1.insert("a");
    s1.insert("b");
    s1.insert("c");
    assert(s1.size()==3);
    s1.insert("c");
    assert(s1.size()==3);

    cout << "++basic operations and iterators++"<< endl;
    it = s1.begin(); 
    while( it != s1.end() ){
        cout << *it << " ";
        it++;
    }
    cout << endl;
    
    assert(s1.find("e")==s1.end());
    assert(s1.find("c")!=s1.end());
    s1.erase("c");
    assert(s1.size()==2);
    assert(s1.find("c")==s1.end());

    s1.insert("m");
    s1.insert("l");
    s1.insert("e");
    it = s1.begin(); 
    while( it != s1.end() ){
        cout << *it << " ";
        it++;
    }
    cout << endl;
    
    s1.insert("o");
    s1.insert("f");
    s1.insert("r");
    
    it = s1.begin();
    while( it != s1.end() ){
        cout << *it << " ";
        it++;
    }
    cout << endl;
    
    s1.insert("o");
    s1.insert("v");
    s1.insert("d");
    
    it = s1.begin();
    while( it != s1.end() ){
        cout << *it << " ";
        it++;
    }
    cout << endl;
    assert(s1.size()==10);
       
    
    s1.erase("o");
    assert(s1.size()==9);
    s1.erase("o");
    assert(s1.size()==9);
    s1.erase("b");
    assert(s1.size()==8);
    it = s1.begin();
    while( it != s1.end() ){
        cout << *it << " ";
        it++;
    }
    cout << endl;
    
    // test overloaded operator <<
    cout << s1 << endl;
    
    // test copy constructor
    cout << "++copy constructor and set equality++"<< endl;
    Set s2 = s1;
    assert(s2.size()==8);
    assert(s2 == s1);
    
    s1.clear();
    assert(s1.size()==0);
    assert(s1.find("a")==s1.end());
    assert(s1.find("f")==s1.end());
    
    assert(s2.size()==8);
    cout << s2 << endl; 
   
    // test assignment operator
    cout << "++assignment operator and set equality++"<< endl;
    s1.insert("aa");
    cout << s1 << endl;
    s1 = s2;
    assert(s1==s2);
    
    
    s1.clear();
    s1.insert("a");
    s1.insert("b");
    s1.insert("c");
    s1.insert("d");
    s1.insert("v");
    s1.insert("k");
    s1.insert("n");
    s1.insert("r");
    cout << "s1 :" << s1 << endl;
    cout << "s2 :" << s2 << endl;
    Set tmp;
    
    cout << "++set difference ++"<< endl;
    tmp  = s1 - s2;
    cout << "difference: " << tmp << endl;
    
    // set intersec
    cout << "++set intersec++"<< endl;
    tmp = s1 & s2;
    cout << "intersec: " << tmp << endl;
    
    cout << "++set join"<< endl;
    tmp = s1 | s2;
    cout << "join: " << tmp << endl;
    
    
    
    
}
