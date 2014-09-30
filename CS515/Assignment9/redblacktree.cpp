	/**   CS515 Assignment9
	File: redblacktree.cpp
	Name: Jonathan Hart
	Section: 2
	Date: 11/5/13 
	Collaboration Declaration: 
	*/


#include "redblacktree.h"


RedBlackNode::RedBlackNode(){};

RedBlackNode::RedBlackNode(int newKey):key(newKey){};

// default constructor
// create sentinel nodes, nil and root
RedBlackTree::RedBlackTree(){
    nil = new RedBlackNode;
    nil->left = nil->right = nil->parent = nil;
    nil->red = false;
    nil->key = numeric_limits<int>::min(); // minimum int value
    
    root = new RedBlackNode;
    root->parent = root->left = root->right = nil;
    root->key = numeric_limits<int>::max(); // maximum int value
    root->red = false;
}

// left rotation on node
void RedBlackTree::leftrotate(RedBlackNode * node) {
   // you fill in here

	RedBlackNode * node2;
	node2 = node->right;
	node->right = node2->left;

	if(node2->left != nil)
		node2->left->parent = node;

	node2->parent = node->parent;

	if(node->parent == nil)
		root = node2;
	else
	{
		if(node == node->parent->left)
			node->parent->left = node2;
		else
			node->parent->right = node2;
	}

	node2->left = node;
	node->parent = node2;
}

// right rotation on node
void RedBlackTree::rightrotate(RedBlackNode * node) {
    // you fill in here
	RedBlackNode * node2;
	node2 = node->left;
	node->left = node2->right;

	if(node2->right != nil)
		node2->right->parent = node;

	node2->parent = node->parent;

	if(node->parent == nil)
		root = node2;
	else
	{
		if(node == node->parent->right)
			node->parent->right = node2;
		else
			node->parent->left = node2;
	}

	node2->right = node;
	node->parent - node2;
}

// inert a new key into the Red Black Tree
// if key already exist no operation is done
	RedBlackNode* RedBlackTree::insert(int newKey){
		// Step 1:
		// create the node; and insert the node with standard BST insert
		
		RedBlackNode * node = new RedBlackNode(newKey);
		node->left = nil;
		node->right = nil;
		node->red = true;	

		RedBlackNode* prev = root;
		RedBlackNode* cur = root->left;
		while( cur != nil) {
			prev = cur;
			if ( newKey == cur->key ){
				delete node;
				return 0;
			}
			
			if ( node->key > cur->key ) {
				cur = cur->left;
			} else
				cur = cur->right;
		}
		// set new node's parent
		node->parent = prev;
		
		//if(prev == root)
		//	node->red = false;
		
		// connect parent to new node
		if ( prev == root || newKey > prev->key)  {
			prev->left = node;
		} else {
			prev->right = node;
		}
		// Step 2:
		// restore Red Black Tree property
		// note that the insertion could only voilate the following:
		// of "If a node is red, then its parent is black".
		// All other Red Black Tree properties hold.
		
		RedBlackNode * node2;

		while (node->parent->red)
		{
			if(node->parent == node->parent->parent->left)
			{
				node2 = node->parent->parent->right;
				if(node2->red)
				{
					node->parent->red = false;
					node2->red = false;
					node->parent->parent->red = true;
					node = node->parent->parent;
				}
				else
				{
					if( node == node->parent->right)
					{
						node = node->parent;
						leftrotate(node);
					}
					node->parent->red = false;
					node->parent->parent->red = true;
					rightrotate(node->parent->parent);
				}
			}
			else
			{
				node2 = node->parent->parent->left;
				if(node2->red)
				{
					node->parent->red = false;
					node2->red = false;
					node->parent->parent->red = true;
					node = node->parent->parent;
				}
				else
				{
					if( node == node->parent->left)
					{
						node = node->parent;
						rightrotate(node);
					}
					node->parent->red = false;
					node->parent->parent->red = true;
					leftrotate(node->parent->parent);
				}
			}
		}
		root->red = false;
		
		return 0;
	}

// binary search tree insert for testing purpose
RedBlackNode* RedBlackTree::BSTinsert(int newKey){
    // create the node;
    RedBlackNode * node = new RedBlackNode(newKey);
	node->left = nil;
	node->right = nil;
	node->red = true;

	RedBlackNode* prev = root;
    RedBlackNode* cur = root->left;
    while( cur != nil) {
        prev = cur;
        if ( newKey == cur->key ){
            delete node;
            return 0;
        }
        
        if ( node->key > cur->key ) {
            cur = cur->left;
        } else
            cur = cur->right;
    }
    // set new node's parent
    node->parent = prev;
    
    // connect parent to new node
    if ( prev == root || newKey > prev->key)  {
        prev->left = node;
    } else {
        prev->right = node;
    }
    
    // insert the node with standard BST insert
    
    return node;
}


// destructor
RedBlackTree::~RedBlackTree(){
    if ( root->left != nil )  // not an empty tree
        destructCode(root->left);
    delete root;
    delete nil;
}

// destructor code for deallocation
void RedBlackTree::destructCode(RedBlackNode *& p){
    if ( p->left != nil )
        destructCode(p->left);
    if ( p->right != nil )
        destructCode(p->right);
    delete p;
    p = 0;
}


// output the structure of tree. The tree is output as "lying down"
// in which _root is the LEFT most Elem.
// Red nodes are printed with brackets() and the nil leaf nodes are not printed
void RedBlackTree::printTree(ostream& out, int level, RedBlackNode *p){
    int i;
    if ( p != nil ) {
        printTree(out, level+1, p->right);
        for( i=0; i<level; i++ )
            out << "\t";
        if ( p->red )
            out << "(" << p->key << ")\n";
        else
            out << p->key << '\n';
        printTree(out, level+1, p->left);
    }
}

ostream& RedBlackTree::dump(ostream &out){
    if ( root->left == nil ) // tree empty
      return out;
    printTree(out, 0, root->left);   // print tree structure
}

// outputs using overloaded << operator
ostream& operator << (ostream &s, RedBlackTree &v){
    v.dump(s);
    return s;
}





