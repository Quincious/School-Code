			/**   CS515 Lab9
	File: set.cpp
	Name: Jonathan Hart
	Section: 2
	Date: 10/23/13
	Collaboration Declaration: Ian D'Elia
	*/
			
			// Copyright 2013 KJ
			// a set ADT implemented with an AVL tree
			#include "set.h"

			// default constructor
			Set::Set():_root(0), _size(0){}

			// common copy code for copying a tree recursively
			Set::Elem* Set::copyCode(Elem *node){
				if (node)
					return new Elem(node->info, copyCode(node->left), copyCode(node->right), node->height);
				else
					return 0;
			}

			Set::Set(const Set& rhs){
				_root = copyCode(rhs._root);
			}

			// overloaded assignment opertor
			Set& Set::operator=(const Set &rhs){
				if(this != &rhs){
					destructCode(_root);
					_root = copyCode(rhs._root);
				}
				return *this;
			}

			// common destruct code for deallocation and make an empty tree
			void Set::destructCode(Elem *& node){
				if (node){
					destructCode(node->left);
					destructCode(node->right);
					delete node;
				}
				node = 0;
			}

			// destructor
			Set::~Set(){
				destructCode(_root);
			}

			// return size of the set elements
			int Set::size() const{
				return _size;
			}

			// insert an element
			void Set::insert(ELEMENT_TYPE x) {
				insert(x, _root);
			}

			// helper method for recusively insertion
			void Set::insert(ELEMENT_TYPE x, Elem *& node) {
				if (node == 0){ // insert here
					node = new Elem(x, 0, 0);
					_size++;
				}
				// move to left
				else if (x < node->info) {
					insert(x, node->left);
				}
				// move to right
				else if (x > node->info) {
					insert(x, node->right);
				}
				
				if (height(node->left) - height(node->right) == 2) { // calculate load factor
					if(x < node->left->info) // outside case
						rotateRight(node);
					else  // inside case
						doubleRotateRight(node);
				}
				
				if (height(node->left) - height(node->right) == -2) { // calculate load factor
					if (x > node->right->info) // outside case
						rotateLeft(node);
					else  // inside case
						doubleRotateLeft(node);
				}
				node->height = max(height(node->left), height(node->right)) + 1; // update height
			}

			// remove an element
			void Set::erase(ELEMENT_TYPE x){
				erase(x, _root);
			}

			// helper method for recusively removal
			void Set::erase(ELEMENT_TYPE x, Elem *& node){
				if (node == 0)  // item not found
					return;
				else if(x>node->info)
					 erase(x, node->right);
				else if(x < node->info)
					 erase(x, node->left);    
				else
				{
					if(node->right&&node->left)//two child
					{
						Elem *successor = node->right;
						while(successor->left)
							successor = successor->left;
							
						node->info = successor->info;
						
						if(successor->right)
							successor = successor->right;
						else
						{
							destructCode(successor);
						}
							
							
						_size--;						
					}
					else 
					{
						if(node->left)
							node = node->left;
						else if(node->right)
							node = node->right;
						else
							destructCode(node);
													
							_size--;
						}			
						
							
						
						return;
				}	
				
				if (height(node->left) - height(node->right) == 2) 
				{ 
					if(height(node->right) < height(node->left)) 
						rotateRight(node);
					else  
						doubleRotateRight(node);
				}
						
				if (height(node->left) - height(node->right) == -2) 
				{ 
					if (height(node->right) > height(node->left)) 
						rotateLeft(node);
					else 
						doubleRotateLeft(node);
				}				
				
				return; 
			}

			// single right rotation
			void Set::rotateRight(Elem *& node) {
				// you fill in here
				Elem * tmp = node->left; 
				
				if(tmp->rightThread)
					node->left = 0;
				else
					node->left = tmp->right;
					
				tmp->right = node;
				tmp->rightThread = false;
				
				if(!node->rightThread)
					node->height = max(height(node->left), height(node->right)) + 1;
				else
					node->height = height(node->left) + 1;
					
				node = tmp;
				
			}

			// single left rotation
			void Set::rotateLeft(Elem *& node){
				// you fill in here
				Elem * tmp = node->right; 
				node->right = tmp->left; 
				tmp->left = node; 
				tmp->height++;
				node->height--;
				node = tmp;
			}

			// double right rotation
			void Set::doubleRotateRight(Elem *& node) {
				// you fill in here
				rotateLeft(node->right);
				rotateRight(node);    
			}

			// double left rotation
			void Set::doubleRotateLeft(Elem *& node) {
				// you fill in here
				rotateRight(node->left);
				rotateLeft(node);
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

			// print tree "laying down"
			void Set::printTree() {
				printTree(0, _root);
			}

			// output the structure of tree. The tree is output as "lying down"
			// in which root is the LEFT most node.
			void Set::printTree(int level, Elem *node) {
				int i;
				if (node) {
					printTree(level+1, node->right);
					for (i=0; i<level; i++)
						cout << "\t";
					cout << node->info << "(" << node->height << ")" << endl;
					printTree(level+1, node->left);
				}
			}
