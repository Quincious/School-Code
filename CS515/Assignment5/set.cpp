/** CS515 Assignment5
	File: sites.cpp, set.cpp
	Name: Jonathan Hart
	Section: 2
	Date: 12/13/13
	Collaboration Declaration: none
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
		 _head->prev = 0;
		 _tail->next = 0;
	}
	  
		// copy constructor
		Set::Set(const Set &rhs)
		{
		   copyCode(rhs);
        
    }	
			
	void Set::copyCode(const Set &v)
	{
		Elem *p1;
		   _head = new Elem;
            _tail = new Elem;
            _size = 0;

          if ( v._size == 0){
            
            _head->next = _tail;
			_tail->prev = _head;
          } 
          else { 
			  _head->next = _tail;
			_tail->prev = _head;
			p1 = v._head->next;
			while(p1 != v._tail)
			{
				insert(p1->info);
				p1 = p1->next;
			}
			
			}
	}
	   
		// destructor
		Set::~Set()
		{	
			destructCode();			
			
		}
		
		void Set::destructCode()
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
			
			destructCode();
			copyCode(rhs);			
			
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
	  
		ostream& Set::dump(ostream& out, const Set &v)
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
		
		ostream& operator<< (ostream& out, Set& s)
		{				
			return s.dump(out, s);
		}
		 
		Set::Iterator Set::find(ELEMENT_TYPE value) const
		{
			Elem *curr = _head->next;
			while(curr != _tail)
			{
				if(curr->info == value)
					return Iterator(curr);
				curr = curr->next;
			}
			return Iterator(_tail);
		}		
		
		ELEMENT_TYPE& Set::Iterator:: operator*()
		{
			return _cur->info;
		}
		
		Set::Iterator Set::Iterator:: operator++(int)
		{
			Iterator res = *this;
			_cur = _cur->next;
			return res;
		}
		
		Set::Iterator Set::Iterator:: operator--(int)
		{
			Iterator res = *this;
			_cur = _cur->prev;
			return res;
		}
		
		bool Set::Iterator:: operator==(Iterator it)
		{
			return _cur == it._cur;
		}
		
		bool Set::Iterator:: operator!=(Iterator it)
		{
			return _cur != it._cur;
		}
		
		Set::Iterator Set::begin() const
		{
			return Iterator(_head->next);
		}
		
		Set::Iterator Set::end() const
		{
			return Iterator(_tail);
		}
		
		// set join and intersect
Set operator&(const Set& s1, const Set& s2)
{
	Set retVal;
	Set::Iterator it;	
	it = s1.begin();
	
	while( it != s1.end())
	{
		if(s2.find(*it) != s2.end())
			retVal.insert(*it);
			
			it++;
	}
	
	return retVal;
}

Set operator|(const Set& s1, const Set& s2)
{
	Set retVal;
	Set::Iterator it;	
	it = s1.begin();
	
	while( it != s1.end())
	{
		retVal.insert(*it);
		it++;
	}
	
	it = s2.begin();
	
	while( it != s2.end())
	{
		retVal.insert(*it);
		
		it++;
	}
	
	return retVal;
}

// set difference 
Set operator-(const Set& s1, const Set& s2)
{
	Set retVal;
	Set::Iterator it;	
	it = s1.begin();
	
	while( it != s1.end())
	{
		if(s2.find(*it) == s2.end())
			retVal.insert(*it);
			
			it++;
	}
	
	return retVal;
}

// set equality
bool operator==(const Set& s1, const Set& s2)
{
	Set::Iterator it1, it2;	
	it1 = s1.begin();
	it2 = s2.begin();
	
	if(s1.size() != s2.size())
		return false;
	
	
	while( it1 != s1.end())
	{
		if(*it1 != *it2)
			return false;
			
			it1++;
			it2++;
	}
	
	return true;
}
		
	
		
			
		