#include "cuckoo.h"
#include <cassert>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

bool ifAllLetters(string str){
    for (int i=0; i<str.length(); i++){
        if (!isalpha(str[i]))
            return false;
    }
    return true;
}

int main(int argc, char** argv){
    if (argc != 2){
      	cout << "wrong number of arguments" << endl;
       	return 1;
    }
    
    ifstream infile(argv[1]);
    if (!infile){
    	cout << "can not open " << argv[1] << " for input." << endl;
    	return 1;
    }
    
    HashTable h;
    string str;
	while (infile >> str){
        if ( !ifAllLetters(str) )
            continue;
        h.insert(str);
    }
   
    cout << "total number of elements: " << h.size() << endl;
    assert(h.find("Alice") == true);
    assert(h.find("in") == true);
    assert(h.find("the") == true);
    assert(h.find("sand") == true);
    assert(h.find("thing") == true);
    assert(h.find("like") == true);
    assert(h.find("clear") == true);
    assert(h.find("she") == true);
    assert(h.find("sea") == false);
    assert(h.find("cat") == false);

    h.remove("clear");
    assert( h.find("clear") == false);
    h.remove("the");
    assert( h.find("the") == false);
    h.remove("like");        
    assert( h.find("like") == false);
    
    return 0;
}
