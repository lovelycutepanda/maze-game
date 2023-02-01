/* This is the header file for the Kruskal's algorithm generator.
 * Kruskal's algorithm is a minimum spanning tree generation algorithm by connecting edges with least 
 * weight.
 * Since the weight between every neighbouring grids is the same, It can be done by creating a 
 * randomized list of borders and eliminating border if the grids separated are not in the same group.
 * To realize this, I implemented a Disjoint Set class to keep track of the groupings of grids.
 */


#include "Generator.h"
#include <vector>

#ifndef KRUSKALGENERATOR_H
#define KRUSKALGENERATOR_H

class KruskalGenerator : public Generator {
public:
    KruskalGenerator(const int, const int);
    virtual void getBorder(std::vector<std::vector<bool>>&, std::vector<std::vector<bool>>&);
};

#endif // KRUSKALGENERATOR_H