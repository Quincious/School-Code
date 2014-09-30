	/**   CS515 Assignment7
	File: set.cpp
	Name: Jonathan Hart
	Section: 2
	Date: 10/23/13 (a day late but in my defense, threaded binary trees are really hard to erase nodes in)
	Collaboration Declaration: My white board. Without it, this would have been impossible.
	*/

#include "set.h"

Set::Set():_size(0){
    // create a dummy root node
    _root = new Elem;
    _root->info = numeric_limits<int>::max();
    _root->left = _root;  // empty tree
    _root->right = 0;
    _root->rightThread = false;
}

Set::~Set(){
    if (_root->left != _root)  // not an empty tree
        destructCode(_root->left);
    delete _root;
}

void Set::destructCode(Elem *& p){
	if(p->left)
		destructCode(p->left);
	
	if(p->right && !p->rightThread)
		destructCode(p->right);
		
	delete p;
}

// returns true if the new node is inserted, otherwise false
bool Set::insert(ELEMENT_TYPE v){
    if (insert(_root->left, v, _root)){
        _size++;
        return true;
    }
    return false;
}

// insert helper method
// returns true if the new node is inserted, otherwise false
bool Set::insert(Elem *&cur, const ELEMENT_TYPE &value, Elem *lastLeft){
    if (cur == _root || cur == 0) {
        cur = new Elem;
        cur->info = value;
        cur->left = 0;
        cur->right = lastLeft;
        cur->rightThread = true;
        return true;
    }
    
    if (value == cur->info){
        return false;
    }
    // insert at left
    if (value < cur->info)
        return insert( cur->left, value, cur);
    
    // insert at right
    if (!cur->rightThread){
        return insert(cur->right, value, lastLeft);
    } else {  // current's right is a thread; add a new node
        cur->rightThread = false;
        cur->right = new Elem;
        cur->right->info = value;
        cur->right->left = 0;
        cur->right->right = lastLeft;
        cur->right->rightThread = true;
        return true;
    }
}

// print out tree elements in depth first in order
void Set::depthFirstInOrder(){
   Elem *cur = _root->left;
   Elem *prev;
   
   if(cur == _root)
		return;
   
   while(cur->left)
		cur = cur->left;
		
	while(cur != _root)
	{
		cout << cur->info << " ";
		
		prev = cur;
		cur = cur->right;
		
		if(!prev->rightThread)
		{
			if(cur->left)
			{
				while(cur->left)
					cur = cur->left;
			}
		}		
	}	
	
}

void Set::breadthFirst(){
   // fill in here
    Elem *cur = _root->left;
    queue<Elem*> q;
    
	q.push(cur);
	
	while(!q.empty())
	{
		Elem *e = q.front();
		q.pop();
		if(e->left)
			q.push(e->left);
			
		if(e->right && !e->rightThread)
			q.push(e->right);
			
		cout << e->info << " ";
		
	}
	
}

int Set::size() const{
    return _size;
}

// output the structure of tree. The tree is output as "lying down"
// in which _root is the LEFT most Elem.
void Set::printTree(ostream& out, int level, Elem *p){
    int i;
    if (p) {
        if (p->right && !p->rightThread)
            printTree(out, level+1,p->right);
        for(i=0;i<level;i++)
            out << "\t";
        out << p->info << '\n';
        printTree(out, level+1,p->left);
    }
}

// outputs information in tree in inorder traversal order
ostream& Set::dump(ostream &out){
    if ( _root == _root->left) // tree empty
        return out;
    printTree(out, 0, _root->left); // print tree structure
	return out;
}


// outputs using overloaded << operator
ostream& operator << (ostream &s, Set &v){
    v.dump(s);
    return s;
}

Set::Iterator Set::begin() const{
    Elem *cur = _root->left;

	if(cur == _root)
		return Iterator(cur);

	while(cur->left)
		cur = cur->left;
	
    return Iterator(cur);
}

Set::Iterator Set::end() const{
    Elem *cur = _root->left;
	Elem *prev;

	if(cur == _root)
		return Iterator(cur);

	while(cur->left)
		cur = cur->left;

	while(cur != _root)
	{		
		prev = cur;
		cur = cur->right;
		
		if(!prev->rightThread)
		{
			if(cur->left)
			{
				while(cur->left)
					cur = cur->left;
			}
		}		
	}
	
    return Iterator(cur);
}

Set::Iterator Set::find(ELEMENT_TYPE value) const{
    Elem *cur = _root->left;
	Elem *prev;

	while(cur->left)
		cur = cur->left;

	while(cur != _root)
	{
		if (cur->info == value)
            return Iterator(cur);
		
		prev = cur;
		cur = cur->right;
		
		if(!prev->rightThread)
		{
			if(cur->left)
			{
				while(cur->left)
					cur = cur->left;
			}
		}		
	}

    return Iterator(_root);
}

bool Set::erase(ELEMENT_TYPE value)
{    
	bool found = false;
	Elem *cur = _root->left;
	Elem *prev = 0;
	Elem *temp = 0;
	Elem *prevThread = 0;

	while(cur->left)
		cur = cur->left;

	while(cur != _root)
	{
		if (cur->info == value)
		{
            found = true;
			break;
		}
		
		prev = cur;
		cur = cur->right;
		
		if(!prev->rightThread)
		{
			if(cur->left)
			{
				while(cur->left)
					cur = cur->left;
			}
		}		
	}

	if(found)
	{
		if(_size == 1)//when only one node remains
		{
			cur->right = 0;
			cur->left = 0;
			destructCode(cur);
			_root->left = _root;
			_size--;
			return found;
		}
		else if(!prev)//only happens when deleting lowest val node
		{			
			prev = _root->left;
			while(prev->left != cur)
				prev = prev->left;
		}
		else if((prev->rightThread && prev->right == cur) || (prev->right != cur && prev->left != cur))
		{			
			prevThread = prev;
			prev = _root;

			while(true)
			{
				if(prev->left == cur)
					break;
				else if(prev == _root)
					prev = prev->left;
				else if(prev->right == cur || prev->left == cur)
					break;
				else if(cur->info > prev->info)				
					prev = prev->right;				
				else //cur->info < prev->info
					prev = prev->left;
			}
		}

		if(!cur->left && cur->rightThread)//has no child;
		{
			if(prev->right == cur)
			{
				prev->rightThread = true;
				prev->right = cur->right;
			}
			else
				prev->left = 0;
			

			cur->right = 0;
			cur->left = 0;
			destructCode(cur);
			_size--;
		}
		else if(!cur->left && cur->right && !cur->rightThread)//has only right child
		{			
			temp = cur->right;

			if(prev->right == cur)
				prev->right = temp;
			else
				prev->left = temp;

			if(prevThread)
				prevThread->right = temp;	

			cur->right = 0;
			cur->left = 0;
			destructCode(cur);	
			_size--;
		}
		else if(cur->left && cur->rightThread)//has only left child
		{
			temp = cur->left;
			Elem *nop = temp;

			while(!nop->rightThread)
				nop = nop->right;
			
			nop->right = cur->right;

			if(prev->right == cur)
				prev->right = temp;
			else
				prev->left = temp;

			if(prevThread)
				prevThread->right = cur->right;	
			
			cur->right = 0;
			cur->left = 0;
			destructCode(cur);
			_size--;
		}
		else//Has two children
		{
			temp = cur->right;
			Elem *tempPrev = 0;
			
			//Find left most right node to replace cur
			while(temp->left)
			{
				tempPrev = temp;
				temp = temp->left;
			}
			cur->info = temp->info;

			if(tempPrev)
			{
				if(temp->right)
					tempPrev->left = temp->right;
			}
			else//if first right node is furthest left right node
			{				
				cur->right = temp->right;

				if(temp->rightThread)
					cur->rightThread = true;
			}

			if(prevThread)
				prevThread->right = cur;				

			temp->right = 0;
			temp->left = 0;
			destructCode(temp);
			_size--;
			
		}
	}

    return found;
}

Set::Elem* Set::Iterator::operator->()
{	
	return _cur;
}
Set::Elem& Set::Iterator::operator*()
{	
	return *_cur;
}

bool Set::Iterator::operator==(Set::Iterator it)
{	
	return (it->info == _cur->info);
}

bool Set::Iterator::operator!=(Set::Iterator it)
{	
	return (it->info != _cur->info);
}

Set::Iterator Set::Iterator::operator++(int) 
{	
	if(_cur->rightThread)
	{
		_cur = _cur->right;
		return *this;
	}
	else
	{
		_cur = _cur->right;

		while(_cur->left)
			_cur = _cur->left;
	}

	return Iterator(_cur);		
}