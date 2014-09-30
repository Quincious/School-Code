	/**   CS515 Lab10
	File: btree.cpp
	Name: Jonathan Hart
	Section: 2
	Date: 10/30/13
	Collaboration Declaration: Ian D'Elia
	*/

#include "btree.h"


void BTree::insert(int newKey, string item){
    BTreeNode *split = root->insert(newKey, item);
    if(split) {
        // splitting root; new root has two children
        BInternal *newRoot = new BInternal();
        newRoot->child[0] = root;
        newRoot->child[1] = split;
        newRoot->keys[1] = newKey;
        newRoot->currChildren = 2;
        root = newRoot;
    }
}

void BTreeNode::indent(int depth){
    for(int i=0; i<depth; i++)
        cout << "\t";
}

void BLeaf::dump(int depth){
    indent(depth);
    if( size > 0 ) {
        int i;
        for(i = 0; i<size-1; i++)
            cout << keys[i] << ":" << data[i] << " ";
        cout << keys[i] << ":" << data[i];
    }
    else
        cout << "Empty";
    cout << endl;
}


void BInternal::dump(int depth){
    indent(depth);
    cout << "[";
    int i;
    for(i=1; i<currChildren-1; i++)
        cout << keys[i] << ",";
    cout << keys[i];
    cout <<"]" << endl;
    
    for(int i=0; i<currChildren; i++)
        child[i]->dump(depth+1);
}


BLeaf * BLeaf::insert(int &newKey, string item){
    // first need to find position for insert into current node
    // then decide if current node has overflown or not
    // if so need to split the node
    
    int i;
    for(i = 0; i< size;i++)
    {
		if(newKey < keys[i])
			break;
	}
	
	if(i == size)
	{
		keys[i] = newKey;
		data[i] = item;
	
	}
	else
	{
		for(int j = size; j > i; j--)
		{
			keys[j] = keys[j-1];
			data[j] = data[j-1];					
		}
		keys[i] = newKey;
		data[i] = item;
	}	
	size++;	
	
	if(size > MAX)
	{
		BLeaf * newB = new BLeaf();
		
		for(int j = 0; j < size/2; j++)
		{
			newB->keys[j] = this->keys[(MAX + 1)/2 + j];
			newB->data[j] = this->data[(MAX + 1)/2 + j];
		}
		
		this->size = (MAX + 1) / 2;
		newB->size = (MAX + 1) / 2;
				
		newKey = this->keys[(MAX + 1)/2];		
		
		return newB;
	}    
    
    return 0;
}



BInternal * BInternal::insert(int &newKey, string item){
    // following indexing and call insert recursively on child nodes
    // if return value is not null, which means the child node has split,
    // then update the current indexing nodes
    
    int addKey = newKey;
    
    int i;
    for(i = 0; i< currChildren;i++)
    {
		if(addKey < keys[i])
			break;
	}	
    
	BTreeNode *split = child[i - 1]->insert(addKey, item);       
      
    
    if(split)
    {		
		int k;
		for(k = 0; k < currChildren; k++)
		{
			if(addKey < keys[k])
				break;
		}
		if(k == currChildren)
		{
			keys[k] = addKey;
			child[k] = split;
		
		}
		else
		{
			for(int j = currChildren; j > k; j--)
			{
				keys[j] = keys[j-1];
				child[j] = child[j-1];					
			}
			keys[k] = addKey;
			child[k] = split;
		}
		currChildren++;
		
		if(currChildren > MAX)
		{
			BInternal *newI = new BInternal();
			
			for(int j = 0; j < (MAX + 1)/2; j++)
			{
				newI->keys[j] = this->keys[(MAX + 1)/2 + j];
				newI->child[j] = this->child[(MAX + 1)/2 + j];
			}
						
			newI->currChildren = ((MAX + 1) / 2);
			this->currChildren = ((MAX + 1)/ 2);
			
			newKey = this->keys[(MAX + 1)/ 2];
			
			return newI;
		}
	}
    
    return 0;
}

