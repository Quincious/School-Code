template<typename T>
Set<T>::Set(){
    _head = new Elem;
    _tail = new Elem;
    _head->prev = 0;
    _head->next = _tail;
    _tail->prev = _head;
    _tail->next = 0;
    _size = 0;
}

template<typename T>
Set<T>::Set(const Set &v){
    copyCode(v);
}

template<typename T>
Set<T>::~Set(){
    destructCode();
}

template<typename T>
Set<T>& Set<T>::operator=(const Set<T> &rhs){
    if (this != &rhs) {
        destructCode();
        copyCode(rhs);
    }
    return *this;
}

template<typename T>
bool  Set<T>::insert(T value){
    if( find(value) == end()){
        Elem *p = new Elem;
        p->info = value;
        Elem *cur = _head->next;
        while(cur != _tail){
            if (cur->info > value)
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

template<typename T>
typename Set<T>::Iterator Set<T>::find(T value) const{
    Elem *cur = _head->next;
    while(cur != _tail){
        if (cur->info == value)
            return Iterator(cur);
        cur = cur->next;
    }
    return Iterator(_tail);
}


template <typename T>
bool Set<T>::erase(T value){
    Elem *cur = _head->next;
    while(cur != _tail){
        if (cur->info == value){  // found it
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

template<typename T>
void Set<T>::clear(){
    Elem *cur;
    while (_head->next != _tail) {
        cur = _head->next;
        _head->next = cur->next;
        cur->next->prev = _head;
        delete cur;
    }
    _size = 0;
}

template<typename T>
int Set<T>::size() const{
    return _size;
}

template<typename T>
void Set<T>::copyCode(const Set<T> &v)
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
        insert(cur -> info); // insert always add to front
        cur = cur->prev;
    }
    _size = v._size;
}

template<typename T>
void Set<T>::destructCode(){
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

template<typename T>
ostream& Set<T>::dump(ostream& out, const Set<T> &v) const{
    Elem *cur = v._head->next;
    while (cur != v._tail) {
        out << cur->info << " ";
        cur = cur->next;
    }
    return out;
}

template<typename T>
ostream& operator<< (ostream& out, const Set<T> &v){
    return v.dump(out, v);
}


