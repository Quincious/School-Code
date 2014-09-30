#include "set.h"
#include <cassert>
#include <iostream>
using namespace std;


int main(){
    Set s1;
    s1.insert(21);
    s1.insert(4);
    s1.insert(61);
    s1.insert(2);
    s1.insert(35);
    s1.insert(3);
    s1.insert(8);
    s1.insert(31);
    s1.insert(12);
    s1.insert(33);
    s1.insert(45);
    s1.insert(49);
    s1.insert(17);
    
    assert(s1.size()==13);
    
    // test output
    cout << s1; 
    
    // test iterator
    Set::Iterator it; 
    it = s1.begin();
    while( it != s1.end() ){
        cout << it->info << " ";
        it++;
    }
    cout << endl;
    
    
    it = s1.find(18);
    assert(it == s1.end());
    
    it = s1.find(17);
    assert( it->info == 17);
    
    // test erase
    cout << endl << "---->erase 33" << endl;
    s1.erase(33);
    assert(s1.size()==12);
    cout << s1;
    it = s1.begin();
    while( it != s1.end() ){
        cout << it->info << " ";
        it++;
    }
    cout << endl;
    
    cout << endl << "---->erase 49" << endl;
    s1.erase(49);
    assert(s1.size()==11);
    cout << s1;
    it = s1.begin();
    while( it != s1.end() ){
        cout << it->info << " ";
        it++;
    }
    cout << endl;
    
    cout << endl << "---->erase 8" << endl;
    s1.erase(8);
    assert(s1.size()==10);
    cout << s1;
    it = s1.begin();
    while( it != s1.end() ){
        cout << it->info << " ";
        it++;
    }
    cout << endl;
    
    cout << endl << "---->erase 35" << endl;
    s1.erase(35);
     assert(s1.size()==9);
    cout << s1;
    it = s1.begin();
    while( it != s1.end() ){
        cout << it->info << " ";
        it++;
    }
    cout << endl;
    
    cout << endl << "---->erase 2" << endl;
    s1.erase(2);
     assert(s1.size()==8);
    cout << s1;
    it = s1.begin();
    while( it != s1.end() ){
        cout << it->info << " ";
        it++;
    }
    cout << endl;
    
    cout << endl << "---->erase 61" << endl;
    s1.erase(61);
     assert(s1.size()==7);
    cout << s1;
    it = s1.begin();
    while( it != s1.end() ){
        cout << it->info << " ";
        it++;
    }
    cout << endl;

    cout << endl << "---->erase 4" << endl;
    s1.erase(4);
     assert(s1.size()==6);
    cout << s1;
    it = s1.begin();
    while( it != s1.end() ){
        cout << it->info << " ";
        it++;
    }
    cout << endl;
    
    cout << endl << "---->erase 31" << endl;
    s1.erase(31);
     assert(s1.size()==5);
    cout << s1;
    it = s1.begin();
    while( it != s1.end() ){
        cout << it->info << " ";
        it++;
    }
    cout << endl;
    
    cout << endl << "---->erase 17" << endl;
    s1.erase(17);
     assert(s1.size()==4);
    cout << s1;
    it = s1.begin();
    while( it != s1.end() ){
        cout << it->info << " ";
        it++;
    }
    cout << endl;
    
    cout << endl << "---->erase 12" << endl;
    s1.erase(12);
     assert(s1.size()==3);
    cout << s1;
    it = s1.begin();
    while( it != s1.end() ){
        cout << it->info << " ";
        it++;
    }
    cout << endl;
    
    cout << endl << "---->erase 21" << endl;
    s1.erase(21);
    assert(s1.size() == 2);
    cout << s1;
    it = s1.begin();
    while( it != s1.end() ){
        cout << it->info << " ";
        it++;
    }
    cout << endl;
    
    cout << endl << "---->erase 45" << endl;
    s1.erase(45);
    assert(s1.size() == 1);
    cout << s1;
    it = s1.begin();
    while( it != s1.end() ){
        cout << it->info << " ";
        it++;
    }
    cout << endl;
    
    cout << endl << "---->erase 3" << endl;
    s1.erase(3);
    assert(s1.size() == 0 );
    cout << "should be empty" << endl;
    cout << s1;
    it = s1.begin();
    while( it != s1.end() ){
        cout << it->info << " ";
        it++;
    }
    cout << endl;
    
}
