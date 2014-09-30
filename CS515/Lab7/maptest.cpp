#include "map.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int main(){
    Map m;
    Set s;
    s.insert(3);
    s.insert(1);
    s.insert(2);
    assert(m.insert("a", s)==true);
    assert(m.insert("a", s) == false);
    
    cout << "Map content:" << endl; 
    Map::Iterator iter = m.begin();
    for(iter = m.begin(); iter != m.end(); iter++){
        cout << "key: " << iter->key << "\t\tdata: " << iter->data << endl;
    }
    
    cout << "Map content:" << endl;
    m["a"].insert(10);  // overloaded [] operator
    iter = m.begin();
    for(iter = m.begin(); iter != m.end(); iter++){
        cout << "key: " << iter->key << "\t\tdata: " << iter->data << endl;
    }

    m["b"].insert(0); // overloaded [] operator
    m["b"].insert(125);
    m["c"].insert(500);
    assert(m.size() == 3);
    cout << "Map content:" << endl;
    iter = m.begin();
    for(iter = m.begin(); iter != m.end(); iter++){
        cout << "key: " << iter->key << "\t\tdata: " << iter->data << endl;
    }

    assert(m.erase("a") == true);
    assert(m.erase("a") == false);
    assert(m.size() == 2);
    assert(m.find("b") == m.begin());
}
