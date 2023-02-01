/* This is the header file for the Depth-First search (DFS) generator.
 * DFS algorithm explores a path and removes the border along the grid, until it reaches a visited 
 * grid.
 * By randomizing the next direction to search for, the paths will not seem systematic.
 * In this maze game, I use the iterative method along with stack to implement the DFS generator.
 */


#include "Generator.h"
#include <vector>

#ifndef DFSGENERATOR_H
#define DFSGENERATOR_H

class DFSGenerator : public Generator {
public:
    DFSGenerator(const int, const int);
    virtual void getBorder(std::vector<std::vector<bool>>&, std::vector<std::vector<bool>>&);
};

#endif // DFSGENERATOR_H