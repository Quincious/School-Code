#include "skiplist.h"

// construct a new skipnode with given key and height 
SkipList::SkipNode::SkipNode( ELEMENT_TYPE in, int h ) : info(in), height(h){
    nextNodes = new SkipNode* [h+1]; // height 0 un-used
    for ( int x = 1; x <= height; x++ ){
        nextNodes[x] = 0;
    }
}

// SkipNode dustructor 
SkipList::SkipNode::~SkipNode(){
    delete [] nextNodes;
}

// SkipList constructor: construct an empty skiplist of max height m and and probability p; current height initialize to 1
SkipList::SkipList(int m, float p) : _curHeight(1), _maxHeight(m), _probability(p){
    // Create head with intMin and tail with intMax;
    int intMin = numeric_limits<int>::min(); // minimum int value
    int intMax = numeric_limits<int>::max(); // maximum int value
    _head = new SkipNode(intMin, _maxHeight);   //
    _tail = new SkipNode(intMax, _maxHeight);
    // attach them to form an empty list
    for ( int x = 1; x <= _maxHeight; x++ ){
        _head->nextNodes[x] = _tail;
    }
    srand(time(0));
}

// copy constructor
SkipList::SkipList(const SkipList& v): _probability(v._probability), _maxHeight(v._maxHeight), _curHeight(v._curHeight){
    copyCode(v);
}

// overloaded operator assignment
SkipList& SkipList::operator=(const SkipList &rhs){
    if (this != &rhs) {
        destructCode();
        copyCode(rhs);
    }
    return *this;
}

// commom code for destruction 
void SkipList::destructCode(){
    // Walk bottom level nodes and delete all
    SkipNode * cur;
    cur = _head;
    while ( _head->nextNodes[1] != _tail ){
        _head = _head->nextNodes[1];
        delete cur;
        cur = _head;
    }
    delete _head;
    delete _tail;
}

// destructor
SkipList::~SkipList(){
    destructCode(); 
}

// Returns a random height between 1 and maximum node height. 
int SkipList::randomLevel(){
    int level = 1;
    // (double)rand()/RAND_MAX return a random number between (0, 1)
    while ( ((double)rand()/RAND_MAX < _probability) && (level < _maxHeight))
        level++;
    return level;
    
    //for testing/debugging; produces deterministic node heights. 
    //static int i = 0;
    //int level[10] = {4, 2, 2, 2, 3, 3, 4, 3, 1, 3};
    //return level[i++];
}

// insert a node key into the skiplist, return false if key already exists
// otherwise insert key and return true. 
bool SkipList::insert( ELEMENT_TYPE info ){
    // pointer array to keep track of the next nodes at the insertion point
    SkipNode ** lookBack = new SkipNode * [_maxHeight+1];
    SkipNode* cur = _head;
    
    int curInfo;
    // find where new node goes
    for ( int h = _curHeight; h >= 1; h-- ){  
        curInfo = cur->nextNodes[h]->info;
        while ( curInfo < info ){
            cur = cur->nextNodes[h];
            curInfo = cur->nextNodes[h]->info;
        }
        lookBack[h] = cur; // keep track of previous node
    }
    cur = cur->nextNodes[1]; // move to next node at level 1
    curInfo = cur->info;
    
    int lvl = 0;
    // If dup, return false
    if ( curInfo == info ){
        delete [] lookBack; 
        return false;
    }
    else{ // Perform an insert
        lvl = randomLevel();
        // prepare insertion point
        // check if node has higher level that the current height
        if ( lvl > _curHeight ){
            for ( int i = _curHeight + 1; i <= lvl; i++ )
                lookBack[i] = _head;
            _curHeight = lvl;
        }
        // Insert new element
        cur = new SkipNode(info, lvl);
        for ( int i = 1; i <= lvl; i++ ){
            cur->nextNodes[i] = lookBack[i]->nextNodes[i];
            lookBack[i]->nextNodes[i] = cur;
        }
        delete [] lookBack;
        return true;
    }
}

// return ture if the key is found, otherwise false
bool SkipList::find(ELEMENT_TYPE info){
    int curInfo = 0;
    SkipNode* cur = _head;
    // find starts at top level
    for ( int h = _curHeight; h >= 1; h-- ){
        curInfo = cur->nextNodes[h]->info;
        while ( curInfo < info ){   // remain the current level before move down a level
            cur = cur->nextNodes[h];
            curInfo = cur->nextNodes[h]->info;
        }
    }
    
    return (curInfo == info);
}

// helper method to output skiplist
ostream& SkipList::dump(ostream& os, const SkipList &v) const{
    SkipNode * cur = v._head -> nextNodes[1];
    while ( cur != v._tail ){
        for ( int h = 1; h <= cur->height; h++ )
            os << cur->info << '\t';
        os << endl;
        cur = cur->nextNodes[1];
    }
    return os;
}

// overloaded output operator
ostream& operator<< ( ostream& out, const SkipList &v ){
    return v.dump(out, v);
}


// erase a node key from the skiplist, return false if key doesnot exists
// otherwise erase key and return true.
bool SkipList::erase( ELEMENT_TYPE info ){
		
	SkipNode ** lookBack = new SkipNode * [_maxHeight+1];
    SkipNode* cur = _head;
    
    int curInfo;
    
    for ( int h = _curHeight; h >= 1; h-- ){  
        curInfo = cur->nextNodes[h]->info;
        while ( curInfo < info){
            cur = cur->nextNodes[h];
            curInfo = cur->nextNodes[h]->info;
        }
        lookBack[h] = cur;
    }
    
    if(cur != _tail)
		cur = cur->nextNodes[1];
    
    if(cur->info == info)
    {		
		for(int h = 1; h <= cur->height; h++)
		{
			lookBack[h]->nextNodes[h] = cur->nextNodes[h];
		}
		
		for(int i = 1; i<= cur->height; i++)
			delete cur->nextNodes[i];
		delete cur;
		
		return true;
	}
	
    return false;
}


// common copy code
void SkipList::copyCode(const SkipList &v)
{
	int intMin = numeric_limits<int>::min(); // minimum int value
    int intMax = numeric_limits<int>::max(); // maximum int value
    
	SkipNode origCurr = v->_head;
	
	_head = new SkipNode(intMin, origCurr->height);
	_tail = new SkipNode(intMax, origCurr->height);
    
	SkipNode copyCurr = _head;
	origCurr = origCurr->NextNodes[1];	
	
	while(origCurr != v->_tail)
	{
		SkipNode copyNode = new SkipNode(origCurr->info, origCurr->height);
		copyCurr->NextNodes[1] = copyNode;
		copyCurr = copyNode;

		origCurr = origCurr->NextNodes[1];
	}
	
	copyCurr->NextNodes[1] = _tail;
	
	origCurr = v->_head;
	copyCurr = _head;
	
	for ( int h = _curHeight; h >= 1; h-- )
	{
		while(origCurr != v->_tail)
		{
			SkipNode copyStart = copyCurr;
			while(copyCurr->info != origCurr->NextNodes[h]->info)
				copyCurr = copyCurr->NextNodes[1];
			
			copyStart->NextNodes[h] = copyCurr;			
			origCurr = origCurr->NextNodes[h];
		}
		
		origCurr = v->_head;
		coppyCurr = _head;		
	}
	
}

