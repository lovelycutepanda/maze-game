/* This is the header file for the Wilson's algorithm generator.
 * Wilson's algorithm is a random walk algorithm without loops.
 * A random grid is picked, and a random walk is done until a found grid is reached.
 * The borders along the walk path are eliminated and the path then joins the found grid. 
 * Any loops during the walk should be overrided by later paths. 
 * To realize this, I use a map to record the arrow direction. 
 * Any loop will result in overrding the original arrow direction, and the loop body will not be 
 * visited as we recover the path from the arrows.
 */


#include "Generator.h"
#include <vector>

#ifndef WILSONGENERATOR_H
#define WILSONGENERATOR_H

class WilsonGenerator : public Generator {
public:
    WilsonGenerator(const int, const int);
    virtual void getBorder(std::vector<std::vector<bool>>&, std::vector<std::vector<bool>>&);

private:
    std::vector<std::vector<bool>> visited;
    void randomWalk(int, int, std::vector<dir>&);
};

#endif // WILSONGENERATOR_H