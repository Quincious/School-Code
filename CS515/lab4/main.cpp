#include "life.h"

/* Program will read from a config file for initial setting of the world
 * then continue to evolve the next generation until user input n.
 */

int main(int argc, char** argv){
    if (argc != 3){
        cout << "Usage: game size inputfile" << endl;
        exit(1);
    }
    int size = atoi(argv[1]);
    bool ** grid = createGrid(size);
    inputGrid(grid, size, argv[2]);
    displayGrid(grid, size);
    char userResponse;
    std::cout << "\nDo you want to see the next generation (y/n)? ";
    std::cin >> userResponse;
    while (userResponse == 'y' || userResponse == 'Y') {
        nextGeneration(grid, size);
        displayGrid(grid, size);
        std::cout << "\nDo you want to see the next generation (y/n)? ";
        std::cin >> userResponse;
    }
    cout << endl; 
    
    deleteGrid(grid, size);
    return 0;
}


