	/**   CS515 Lab6
	File: set.cpp, charlist.cpp
	Name: Jonathan Hart
	Section: 2
	Date: 10/04/13
	Collaboration Declaration: Ian D'Elia
	*/
	
	#include "set.h"
	#include <cassert>
	#include <iostream>
	using namespace std;


	Set::Set()
	{	
		 _head = new Elem;
		 _tail = new Elem;
		 _size = 0;
		 _head->next = _tail;
		 _tail->prev = _head;		
	}


	  
		// copy constructor
		Set::Set(const Set &rhs)
		{
		   Elem *p1;
		   _head = new Elem;
            _tail = new Elem;
            _size = 0;

          if ( rhs._size == 0){
            
            _head->next = _tail;
			_tail->prev = _head;
          } 
          else { 
			  _head->next = _tail;
			_tail->prev = _head;
			p1 = rhs._head->next;
			while(p1 != rhs._tail)
			{
				insert(p1->info);
				p1 = p1->next;
			}
			
			}
        
    }
			
			
			
			
	
	   
		// destructor
		Set::~Set()
		{
			
			Elem *cur = _head;
			Elem *next = _head->next;
			while(next != _tail)
			{
				delete cur;
				cur = next;
				next = cur->next;
			}
			delete cur;	
			delete next;
					
			
		}
		
		// assignment operator
		Set& Set::operator=(const Set &rhs)
		{
			Elem *cur = _head;
			Elem *next = _head->next;
			while(next != _tail)
			{
				delete cur;
				cur = next;
				next = cur->next;
			}
			delete cur;
			delete next;
			
			_head = new Elem;
			_tail = new Elem;
			_size = 0;
			_head->next = _tail;
			_tail->prev = _head;
			
			Elem *p1;

          
          if(rhs._size != 0){ 
			 _head->next = _tail;
			_tail->prev = _head;
			p1 = rhs._head->next;
			while(p1 != rhs._tail)
			{
				insert(p1->info);
				p1 = p1->next;
			}
			
			}
			
			return *this;
		}
		
		// insert an int into the set; return true if element is inserted
		void Set::insert(ELEMENT_TYPE t)
		{
		 Elem *nop = new Elem;
		 nop->info = t;
         if(_size == 0)
         {
	      _head->next=nop;
	      _tail->prev=nop;
	      nop->next=_tail;
	      nop->prev=_head;
	      _size++;
			 
		 }
		 else
		 {
		  Elem *cur = _head->next;
		  while(cur != _tail)
			{
				if(nop->info == cur->info)
				{
				delete nop;
					break;
					}
				else if(nop->info < cur->info)
				{
					cur->prev->next = nop;
					nop->prev = cur->prev;
					nop->next = cur;
					cur->prev = nop;
					_size++;
					break;
				}
				cur = cur->next;
							
			}
			if(cur == _tail)//reached tail
			{
				_tail->prev->next = nop;
				nop->prev = _tail->prev;
				nop->next = cur;
				_tail->prev = nop;
				_size++;
				
			}
			
		}
			
		}
		
		// remove an int from the set; return true of the element is moved, 
		void Set::erase(ELEMENT_TYPE t)
		{
			Elem *cur = _head->next;
			while(cur != _tail)
			{
				if(cur->info==t)
				 {
					 cur->prev->next = cur->next;
					 cur->next->prev = cur->prev;
					 delete cur;
					 _size--;
					 break;
				 }
				cur = cur->next;
			}			
			
		}
		
		// remove all elements from set
		void Set::clear()
		{
			Elem *cur = _head;
			
			while(cur->next != _tail)
			{
				Elem *el = cur->next;
				cur->next = el->next;
				delete el;				
			}
			_size = 0;	
		}

		// return size of the set
		int Set::size() const
		{
		return _size;		
		}
	  
		// return true if an element is found; false otherwise
		bool Set::find(ELEMENT_TYPE t) const
		{
			bool found = false;
			Elem *cur = _head->next;
			while(cur != _tail)
			{
				if(cur->info==t)
				 found = true;
				cur = cur->next;
			}
			return found;
		}
		ostream& Set::dump(ostream& out, const Set &v) const
		{
			Elem *nop = v._head->next;
			while(nop != v._tail)
			{
				out << nop->info << " ";
				nop = nop->next;
			}
			out << endl;
			
			return out;
		}
		
		ostream& operator<< (ostream& out, const Set& s)
		{	
			
			return s.dump(out, s);
		}
		 
			
			
			
			
			
		
