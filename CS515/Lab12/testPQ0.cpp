// test driver for PQ non-template version

#include "PQueue0.h"
#include <cstdlib>
#include <cassert>
using namespace std;

int main(){
    int numItems = 50;
    PQueue q;  // a queue for int elements
    
    int i, x;
    srand(time(0));
    cout << "Enqueuing..." << endl;
    for( i = 1; i < numItems; i++) {
        x = rand() % 100;
        cout << x << " ";
        q.insert( x );
    }
    
    cout << "\n\nDequeuing..." << endl;
    for( i = 1; i < numItems; i++ ) {
        x = q.findMin();
        q.deleteMin();
        cout << x << " ";
    }
    cout << endl;
    
    assert(q.size() == 0);
    q.insert(3);
    q.insert(10);
    q.insert(9);
    
    x = q.findMin();
    q.deleteMin();
    cout << x << " ";

    x = q.findMin();
    q.deleteMin();
    cout << x << " ";


    q.insert(8);
    q.insert(2);
    
    x = q.findMin();
    q.deleteMin();
    cout << x << " ";
    
    x = q.findMin();
    q.deleteMin();
    cout << x << " ";
    
    x = q.findMin();
    q.deleteMin();
    cout << x << " " << endl;
    
}

