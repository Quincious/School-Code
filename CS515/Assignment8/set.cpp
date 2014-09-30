	/**   CS515 Assignment8
	File: set.cpp
	Name: Jonathan Hart
	Section: 2
	Date: 10/30/13 (a day late but in my defense, threaded trees are really hard)
	Collaboration Declaration: That guy in the PAC. Couldn't have done it without him :)
	*/


// a set ADT implemented with a right-threaded AVL tree
// the set supports iterators

#include "set.h"

// default constructor
Set::Set(){
	_root = new Elem(0,0,0);
	_size = 0;
}

// return size of the set elements
int Set::size() const{
	return _size;
}

// insert an element
void Set::insert(ELEMENT_TYPE x) {
    insert(_root->left, x, _root);
}

// helper method for recusively insertion
// cur: current root
// value: element type value
// lastLeft: pointer to the last left node for threading
void Set::insert(Elem *& cur, ELEMENT_TYPE value, Elem *lastLeft) {
    if (cur == 0 || cur == _root)// insert here
	{ 
		cout << "Inserting....." << endl;
		cur = new Elem(value, 0, lastLeft);
		cur->rightThread = true;
		_size++;
	}
	else if(cur->info == value)
		return;
	else if (value < cur->info) // move to left
	{
		insert(cur->left,value, cur);
	}	
	else if (value > cur->info) // move to right
	{		
		if(cur->rightThread)
		{
			cur->right = new Elem(value, 0, lastLeft);
			cur->right->rightThread = true;
			cur->rightThread = false;
			_size++;
		}
		else
			insert(cur->right, value, lastLeft);
	}
	
				
	if (balanceFactor(cur) == 2) { // calculate load factor
		if(value < cur->left->info) // outside case
		{
			//cout << "Balance = 2. Rotate Right." << endl;
			rotateRight(cur);
		}
		else  // inside case
		{
			//cout << "Balance = 2. Double Rotate Right." << endl;
			doubleRotateRight(cur);			
		}
	}
				
	if (balanceFactor(cur) == -2) { // calculate load factor
		if (value > cur->right->info)
		{
			//cout << "Balance = -2. Rotate Left." << endl; // outside case
			rotateLeft(cur);
		}
		else  // inside case
		{
			//cout << "Balance = -2. Double Rotate Left." << endl;
			doubleRotateLeft(cur);
		}
	}

	if(cur->rightThread)
		cur->height = max(height(cur->left), -1) + 1; // update height
	else
		cur->height = max(height(cur->left), height(cur->right)) + 1; // update height
	cout << "Updated height- " << cur->info << "(" << cur->height << ")" << endl;
}

// If found, return an iterator points to the element;
// otherwise returns an iterator to set::end()
Set::Iterator Set::find(ELEMENT_TYPE v) const{
    // you fill in here
	Elem *cur = _root->left;
	Elem *prev;

	while(cur->left)
		cur = cur->left;

	while(cur != _root)
	{
		if (cur->info == v)
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
		
    return Iterator(end());	
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


// you also need to complete the implementation of the 4 AVL rotation methods
// single right rotation
void Set::rotateRight(Elem *& node) {
	// you fill in here
	//cout << "Rotate Right" << endl;
	Elem * tmp = node->left; 
				
	if(!tmp->rightThread)
		node->left = tmp->right;
	else
		node->left = 0;
		
	tmp->rightThread = false;	
	tmp->right = node;	
	
	if(node->rightThread)
		node->height = max(height(node->left), -1) + 1;		
	else
		node->height = max(height(node->left), height(node->right)) + 1;
	//cout << "(RR)Updated height- " << node->info << "(" << node->height << ")" << endl;
		
	if(tmp->rightThread)
		tmp->height = max(height(node->left), -1) + 1;
	else
		tmp->height = max(height(tmp->left), height(tmp->right)) + 1;
	//cout << "(RR)Updated height- " << tmp->info << "(" << tmp->height << ")" << endl;

	node = tmp;				
}

// single left rotation
void Set::rotateLeft(Elem *& node){
	// you fill in here
	//cout << "Rotate Left" << endl;
	Elem * tmp = node->right; 
				
	if(!tmp->left)
	{
		node->rightThread = true;
		node->right = tmp;
	}
	else
		node->right = tmp->left;

	tmp->left = node;
	
	if(node->rightThread)
		node->height = max(height(node->left), -1) + 1;
	else
		node->height = max(height(node->left), height(node->right)) + 1;
	//cout << "(RL)Updated height- " << node->info << "(" << node->height << ")" << endl;
		
	if(tmp->rightThread)
		tmp->height = max(height(node->left), -1) + 1;
	else
		tmp->height = max(height(tmp->left), height(tmp->right)) + 1;
	//cout << "(RL)Updated height- " << tmp->info << "(" << tmp->height << ")" << endl;
		
	node = tmp;	
}

// double right rotation
void Set::doubleRotateRight(Elem *& node) {
	// you fill in here
	rotateLeft(node->left);
	rotateRight(node);    
}

// double left rotation
void Set::doubleRotateLeft(Elem *& node) {
	// you fill in here
	rotateRight(node->right);
	rotateLeft(node);
}


// return the height of a node
int Set::balanceFactor(Elem *cur) {
    int heightRight = cur->rightThread ? -1 : height(cur->right);
    int heightLeft = height(cur->left);
    return heightLeft - heightRight;
}

// return the height of a node
int Set::height(Elem *node) {
    return node == 0 ? -1 : node->height;
}

// return the address of the minimum node in the tree
Set::Elem* Set::findMin(Elem *node) {
    if (node == 0)
        return node;
    while (node->left)  // move to the leftmost node
        node = node->left;
    return node;
}

// output the structure of tree. The tree is output as "lying down"
// in which _root is the LEFT most Elem.
void Set::printTree(ostream& out, int level, Elem *p){
    int i;
    if (p) {
        if (p->right && !p->rightThread)
            printTree(out, level+1,p->right);
        for(i=0;i<level;i++) {
            out << "\t";
        }
        cout << p->info << "(" << p->height << ")" << endl;
        printTree(out, level+1, p->left);
    }
}

// outputs information in tree in inorder traversal order
ostream& Set::dump(ostream &out){
    if (_root == _root->left) {// tree empty
        return out;
    }
    printTree(out, 0, _root->left);   // print tree structure
}

// destructor
Set::~Set(){
    if (_root->left != _root){  // not an empty tree
        destructCode(_root->left);
    }
    delete _root;
}

// common destruction code
void Set::destructCode(Elem *& p){
    if (p->left != 0) {
        destructCode(p->left);
    }
    if (!p->rightThread) {
        destructCode(p->right);
    }
    delete p;
}

// outputs using overloaded << operator
ostream& operator << (ostream &s, Set &v){
    v.dump(s);
    return s;
}

bool Set::Iterator::operator==(Set::Iterator it)
{	
	return (it->info == _cur->info);
}

bool Set::Iterator::operator!=(Set::Iterator it)
{	
	return (it->info != _cur->info);
}

Set::Elem* Set::Iterator::operator->()
{	
	return _cur;
}
Set::Elem& Set::Iterator::operator*()
{	
	return *_cur;
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
