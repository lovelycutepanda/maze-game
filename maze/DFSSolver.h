/* This is the header file for the Depth-First search (DFS) agent.
 * DFS algorithm explores a path until dead end is met, then explores the next path and so on.
 * In this maze game, I use a recursive function that returns a boolean value indicating whether the
 * goal is reached.
 * This ensures that once the goal is reached, all recursing functions called will return immediately.
 */


#include "Solver.h"
#include <vector>

#ifndef DFSSOLVER_H
#define DFSSOLVER_H

class DFSSolver : public Solver {
public:
    DFSSolver(const int, const int, std::vector<std::vector<bool>>&, 
              std::vector<std::vector<bool>>&, MachineBoard*);
    virtual void solve();

private:
    bool DFS(int, int, std::vector<std::pair<int, int>>&);
};

#endif // DFSSOLVER_H