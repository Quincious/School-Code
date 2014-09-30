/**   CS515 Lab4
File: life.cpp
Name: Ian D'Elia
Section: 2
Date: 09/18/13
Collaboration Declaration: Jonathan Hart
*/
#include "life.h"

// input the values of a 2D dynamic boolean array from a file
// parameters:
//    grid: pointer to a 2D dynamic boolean array;
//    size: size of the array
//    filename: input file name
// returns: void
void inputGrid(bool** grid, int size, char * filename ){
    ifstream infile(filename);
    if (!infile){
        cerr << "Error open file." << endl;
        return; 
    }
    int row, col;
    char buf[256];
    while (infile.getline(buf, 256)){
        stringstream s(buf);
        s >> row >> col; 
        grid[row][col] = true;
    }
}

// create a 2D dynamic boolean array
// parameter:
//    size : size of the array.
// returns: pointer to the size*size array.
bool** createGrid(int size){

    bool ** grid;
    grid = new bool*[size];
    for( int i = 0 ; i < size ; i++ )
    {
      grid[i] = new bool[size];
    }
    for(int i = 0;i<size;i++)
    {
		for(int j = 0;j<size;j++)
		{
			grid[i][j]=false;
		}
	}
    // you fill in here
    
    return grid;
}

// display the value of a 2D dynamic boolean array;
// will display X for true and . for false.
// parameter:
//    grid: pointer to a 2D dynamic boolean array;
//    size: size of the array
// returns: void
void displayGrid(bool** grid, int size)
{
    std::cout << '\n';
    for (int i=0; i < size; i++) {
        for (int j=0; j < size; j++)
            if (grid[i][j] == true)
                std::cout << "X ";
            else
                std::cout << ". ";
        std::cout << '\n';
    }
}

// calculate the next configuration of life game based on a 2D dynamic boolean array
// The next configuration is computed by counting simultaneously the number of living
// neighbors for each cell.
// If a cell has 2 living neighbors, then its status does not change;
// if a cell has 3 living neighbors, then it will be alive in the next generation;
// any other number of living neighbors and it will be dead in the next generation.
//
// parameters:
//    grid: pointer to a 2D dynamic boolean array;
//    size: size of the array
// returns: void
void nextGeneration(bool ** World, int size)
{
    int neighborCnt=0;
    
    bool ** temp = createGrid(size);   // temporary workspace for computing next generation
    
    // you fill in here
    for(int i = 0;i<size;i++)
    {
		for(int j=0;j<size; j++)
		{
         neighborCnt = getNeighborCount(World,size,i,j);
         if(neighborCnt==2)
         {
			 temp[i][j] = World[i][j];
			 }
         else if(neighborCnt==3)
         {
			 temp[i][j]=true;
		 }
		 else
		 {
			 temp[i][j]=false;
		 }
	 }
	 
 }
   for(int i = 0;i<size;i++)
    {
		for(int j = 0;j<size;j++)
		{
			World[i][j]=temp[i][j];
		}
	}
	deleteGrid(temp,size);
   
}


// calculate the neighbor count of a cell in a 2D dynamic boolean array
// a true value neighboring cell will be counted as 1.
//
// parameters:
//    grid: pointer to a 2D dynamic boolean array;
//    size: size of the array
//    m: x-coordinate of the cell
//    n: y-coordinate of the cell
// returns: number of counts
int getNeighborCount(bool ** World, int size, int row, int col){
    //  1 2 3       These are the positions of the
    //  4 x 5       neighbors of x. Each is checked
    //  6 7 8       below for alive/dead.
    
    int cnt=0;
    
    if (row > 0) {
        if (col > 0 && World[row-1][col-1] == true)          // check 1
            cnt++;
        if (col < size-1 && World[row-1][col+1] == true)     // check 3
            cnt++;
        if (World[row-1][col] == true)                       // check 2
            cnt++;
    }
    
    if (row < size - 1) {
        if (col > 0 && World[row+1][col-1] == true)          // check 6
            cnt++;
        if (col < size - 1 && World[row+1][col+1] == true)   // check 8
            cnt++;
        if (World[row+1][col] == true)                       // check 7
            cnt++;
    }
    
    if (col > 0 && World[row][col-1] == true)                // check 4
        cnt++;
    if (col < size - 1 && World[row][col+1] == true)         // check 5
        cnt++;
    
    return cnt;
}

// delete a 2D dynamic boolean array
// parameter:
//    grid: pointer to a 2D dynamic boolean array
//    size : size of the array.
// returns: void
void deleteGrid(bool** grid, int size){
    for (int i=0; i < size; i++){
        delete [] grid[i];
    }
    delete [] grid; 
}

