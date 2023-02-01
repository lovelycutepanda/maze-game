/* This is the header file for the Prim's algorithm generator.
 * Prim's algorithm is a minimum spanning tree generation algorithm by finding the edge with the least
 * weight among edges connected to discovered nodes, and connecting the new node.
 * Since the weight between every neighbouring grids is the same, It can be done by randomly picking a
 * neighbour not yet found among the list of found grids and eliminating the border.
 */


#include "Generator.h"
#include <vector>

#ifndef PRIMGENERATOR_H
#define PRIMGENERATOR_H

class PrimGenerator : public Generator {
public:
    PrimGenerator(const int, const int);
    virtual void getBorder(std::vector<std::vector<bool>>&, std::vector<std::vector<bool>>&);
};

#endif // PRIMGENERATOR_H