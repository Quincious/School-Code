#include "map.h"

template<typename KEY, typename T>
Map<KEY,T>::Map()
{
	_head = new Elem;
    _tail = new Elem;
    _head->prev = 0;
    _head->next = _tail;
    _tail->prev = _head;
    _tail->next = 0;
    _size = 0;
}

template<typename KEY, typename T>
Map<KEY,T>::Map(const Map<KEY,T> &rhs)
{
	copyCode(rhs);
}

template<typename KEY, typename T>
Map<KEY,T>::~Map(){
    destructCode();
}

template<typename KEY, typename T>
Map<KEY,T>& Map<KEY,T>::operator=(const Map<KEY,T> &rhs){
    if (this != &rhs) {
        destructCode();
        copyCode(rhs);
    }
    return *this;
}

template<typename KEY, typename T>
bool Map<KEY,T>::insert(KEY key, T data){
    if( find(key) == end()){
        Elem *p = new Elem;
		p->key = key;
        p->data = data;
        Elem *cur = _head->next;
        while(cur != _tail){
            if (cur->key > key)
                break;
            cur = cur->next;
        }
        // insert new node
        p->next = cur;
        p->prev = cur->prev;
        cur->prev->next = p;
        cur->prev = p;
        _size++;
        return true;
    }
    return false;
}

template <typename KEY, typename T>
bool Map<KEY,T>::erase(KEY key){
    Elem *cur = _head->next;
    while(cur != _tail){
        if (cur->key == key){  // found it
            cur->prev->next = cur->next;
            cur->next->prev = cur->prev;
            delete cur;
            _size--;
            return true;
        }
        cur = cur->next;
    }
    return false;
}

template<typename KEY, typename T>
void Map<KEY,T>::clear(){
    Elem *cur;
    while (_head->next != _tail) {
        cur = _head->next;
        _head->next = cur->next;
        cur->next->prev = _head;
        delete cur;
    }
    _size = 0;
}

template<typename KEY, typename T>
typename Map<KEY,T>::Iterator Map<KEY,T>::find(KEY key) const{
    Elem *cur = _head->next;
    while(cur != _tail){
        if (cur->key == key)
            return Iterator(cur);
        cur = cur->next;
    }
    return Iterator(_tail);
}

template<typename KEY, typename T>
T&  Map<KEY,T>::operator[](KEY key){
   // fill in here
			
	if(find(key) == end())
	{		
		Elem *el = new Elem;
		el->key = key;
		
		Elem *cur = _head->next;
		while(cur != _tail)
		{
			if(cur->key > key)
				break;
			cur = cur->next;
		}
		
		el->next = cur;
		el->prev = cur->prev;
		cur->prev->next = el;
		cur->prev = el;
		_size++;
				
		return find(key)->data;
	}
	else
	{
		return find(key)->data;
	}
   
}

template<typename KEY, typename T>
void Map<KEY,T>::copyCode(const Map<KEY,T> &v)
{
    // set up the empty list
    _head = new Elem;
    _tail = new Elem;
    _head->prev = 0;
    _head->next = _tail;
    _tail->prev = _head;
    _tail->next = 0;

    // copy elements from tail to head 
    Elem *cur = v._tail->prev;
    while ( cur != v._head) {
        insert(cur->key, cur->data); // insert always add to front
        cur = cur->prev;
    }
    _size = v._size;
}

template<typename KEY, typename T>
void Map<KEY,T>::destructCode(){
    Elem *cur;
    while (_head != _tail) {
        cur = _head;
        _head = _head->next;
        delete cur;
    }
    delete _head;
    _head = 0;
    _tail = 0;
    _size = 0;
}

template<typename KEY, typename T>
ostream& Map<KEY,T>::dump(ostream& out, const Map<KEY,T> &v) const{
    Elem *cur = v._head->next;
    while (cur != v._tail) {
        out << cur->key << " " << cur->data << "\n";
        cur = cur->next;
    }
    return out;
}

template<typename KEY, typename T>
ostream& operator<< (ostream& out, const Map<KEY,T> &v){
    return v.dump(out, v);
}