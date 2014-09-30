#include <map>
#include "DisjointSet0.h"
using namespace std;
    
    /**
	 * Creates a singleton set from the parameter.
	 */
void DisjointSet::createSet(int p)
{
	parents[p] = p;
	depths[p] = 0;//singleton set has depth of 0;
}
    
    /**
	 * Finds and returns the representative of the set which contains the
	 * parameter. Implements path compression.
	 */
int DisjointSet::findSet(int p)
{
	if(parents[p] == p)//found representative
		return p;
	else
	{
		parents[p] = findSet(parents[p]);//compression
		return parents[p];
	}
}
    
    /**
	 * Combines the sets which contain the parameters. Return false if two 
     * parameters are already in the same set; otherwise, union the two sets
     * by rank and return true. Implements union by rank
	 */
bool DisjointSet::unionSets(int p, int q)
{
	//get set reps
	int parentSet1 = findSet(p);
	int parentSet2 = findSet(q);
	
	if(parentSet1 == parentSet2)//if same set, cant union
		return false;
	else
	{
		//only time depth would increase is during union of sets
		//with same depth.
		if(depths[parentSet1] == depths[parentSet2])
		{
			parents[parentSet2] = parentSet1;
			depths[parentSet1]++;
		}
		else if(depths[parentSet1] > depths[parentSet2])
			parents[parentSet2] = parentSet1;
		else
			parents[parentSet1] = parentSet2;
			
		return true;
	}
		
}
    

