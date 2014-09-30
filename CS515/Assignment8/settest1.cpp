#include "set.h"
#include <cassert>
#include <iostream>
using namespace std;


int main(){
    Set s1;
    s1.insert(21);
	cout << "***********Inserted 21" << endl;
	cout << s1;
    s1.insert(4);
	cout << "***********Inserted 4" << endl;
	cout << s1;
    s1.insert(61);
	cout << "***********Inserted 61" << endl;
	cout << s1;
    s1.insert(2);
	cout << "***********Inserted 2" << endl;
	cout << s1;
    s1.insert(35);
	cout << "***********Inserted 35" << endl;
	cout << s1;
    s1.insert(3);
	cout << "***********Inserted 3" << endl;
	cout << s1;
    s1.insert(8);
	cout << "***********Inserted 8" << endl;
	cout << s1;
    s1.insert(31);
	cout << "***********Inserted 31" << endl;
	cout << s1;
    s1.insert(12);
	cout << "***********Inserted 12" << endl;
	cout << s1;
    s1.insert(33);
	cout << "***********Inserted 33" << endl;
	cout << s1;
    s1.insert(45);
	cout << "***********Inserted 45" << endl;
	cout << s1;
    s1.insert(49);
	cout << "***********Inserted 49" << endl;
	cout << s1;
    s1.insert(17);
	cout << "***********Inserted 17" << endl;
	cout << s1;
    s1.insert(18);
	cout << "***********Inserted 18" << endl;
	cout << s1;
    s1.insert(19);
	cout << "***********Inserted 19" << endl;
	cout << s1;
    s1.insert(20);
	cout << "***********Inserted 20" << endl;
	cout << s1;
	s1.insert(20);
	cout << "***********Inserted 20" << endl;
	cout << s1;
    
    assert(s1.size()==16);
    
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
    
    it = s1.find(98);
    assert(it == s1.end());
    
    it = s1.find(17);
    assert( it->info == 17);

	return 0;
}
