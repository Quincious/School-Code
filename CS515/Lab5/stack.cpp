#include "stack.h"


// assignment operator
// parameter:
//    rhs: the stack object to be assigned from 
// returns: a deep copy of the rhs stack object
stack& stack::operator=(const stack& rhs) {
    if (this != &rhs){
        if ( rhs._arr != 0 ){
            _capacity = rhs._capacity;
            _tos = rhs._tos;
            delete [] _arr;
            _arr = new string[_capacity];
            for ( int i=0; i<_tos; i++ )
                _arr[i] = rhs._arr[i];
        }
        else{
            delete [] _arr;
            _arr = 0;
            _tos = 0;
        }
    }
    return *this;
}

stack::stack(int i)
{
	_tos = 0;
	_capacity = i;
	_arr = new string[_capacity];
}

stack::stack(const stack& toCopy)
{	
	_tos = toCopy._tos;
	_capacity = toCopy._capacity;
	_arr = new string[_capacity];
	for ( int i=0; i<_tos; i++ )
		_arr[i] = toCopy._arr[i];

}

stack::~stack()
{
	delete [] _arr;
}
void stack::push(const string x)
{
	_arr[_tos] = x;
	_tos++;
	if(_tos == _capacity)
	{
		_capacity = _capacity * 2;
		string *tempArr = new string[_capacity];
		for(int i = 0; i < _capacity/2; i++)
			tempArr[i] = _arr[i];
			
		delete [] _arr;
		_arr = new string[_capacity];
		
		for(int i = 0; i < _capacity/2; i++)
			_arr[i] = tempArr[i];
			
		delete [] tempArr;
	}
		
}

void stack::pop()
{
	_tos--;
}

string& stack::top()
{
	return _arr[_tos - 1];
}

bool stack::empty()
{
	return (_tos == 0);
}

int stack::size()
{
	return _tos;
}

int stack::capacity()
{
	return _capacity;
}

void stack::print(std::ostream& os)
{
	/*for(int i = 0; i < _tos; i++)
		os << _arr[i] << endl;*/
}