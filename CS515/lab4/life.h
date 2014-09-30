#ifndef _life_h
#define _life_h

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
using namespace std;


// create a 2D dynamic boolean array
// parameter:
//    size : size of the array.
// returns: pointer to the size*size array. 
bool** createGrid(int size);

// display the value of a 2D dynamic boolean array;
// will display X for true and . for false. 
// parameter:
//    grid: pointer to a 2D dynamic boolean array;
//    size: size of the array
// returns: void
void displayGrid(bool** grid, int size);



// input the values of a 2D dynamic boolean array from a file
// parameters:
//    grid: pointer to a 2D dynamic boolean array;
//    size: size of the array
//    filename: input file name
// returns: void
void inputGrid(bool** grid, int size, char* filename);



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
void nextGeneration(bool** grid, int size);



// calculate the neighbor count of a cell in a 2D dynamic boolean array
// a true value neighboring cell will be counted as 1.
// 
// parameters:
//    grid: pointer to a 2D dynamic boolean array;
//    size: size of the array
//    m: x-coordinate of the cell 
//    n: y-coordinate of the cell
// returns: number of counts
int getNeighborCount(bool** grid, int size, int m, int n);


// delete a 2D dynamic boolean array
// parameter:
//    grid: pointer to a 2D dynamic boolean array 
//    size : size of the array.
// returns: void
void deleteGrid(bool** grid, int size);

#endif
