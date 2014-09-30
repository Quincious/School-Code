	/**   CS515 Lab8
	File: set.cpp
	Name: Jonathan Hart
	Section: 2
	Date: 10/16/13
	Collaboration Declaration: Ian D'Elia
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
    printTree(out, 0, _root->left);   // print tree structure
}


// outputs using overloaded << operator
ostream& operator << (ostream &s, Set &v){
    v.dump(s);
    return s;
}

