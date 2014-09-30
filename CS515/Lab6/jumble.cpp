#include "charlist.h"
#include <cstdlib>
#include <sstream>
using namespace std;

int main(){
    string line;
    cout << "Input word and key to jumble: ";
    while(getline(cin, line)){
        stringstream s(line);
        CharList clist;
        int pos;
        string str;
        s >> str;
        cout << str << " is jumbled by key ";
        for(int i = 0; i < str.length(); i++){
            s >> pos;
            if( pos % 2){ // odd number
                clist.insertFront(str[i]);
            } else {
                clist.insertRear(str[i]);
            }
            cout << pos; 
        }
        cout << " to " << clist.toStr() << endl;
        cout << "Input word and key to jumble: ";
    }
    cout << endl;
}
