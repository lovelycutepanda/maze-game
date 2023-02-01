/* This is the implementation file for the Depth-First search (DFS) generator. */


#include "Generator.h"
#include "DFSGenerator.h"
#include <vector>
#include <stack>
#include <random>

DFSGenerator::DFSGenerator(const int row, const int col) : Generator(row, col) {}

void DFSGenerator::getBorder(std::vector<std::vector<bool>> &verticalBorder, 
                             std::vector<std::vector<bool>> &horizontalBorder) {
    
    // each element in path is in form { fromX, fromY, toX, toY }
    std::stack<std::vector<int>> path;
    
    // randomize
    std::random_device dev;
    std::mt19937 rng(dev());
    std::shuffle(directions.begin(), directions.end(), rng);

    // initialization
    for (dir direction : directions)
        path.push({ 0, 0, dirToVal[direction], dirToVal[direction + 1] });
    visited[0][0] = true;

    while (!path.empty()) {

        // get top item from path
        std::vector<int>& item = path.top();
        int fromX = item[0], fromY = item[1], toX = item[2], toY = item[3];
        path.pop();
        if (toX < 0 || toX >= getCol() || toY < 0 || toY >= getRow() || visited[toY][toX])
            continue;
        visited[toY][toX] = true;

        // set border according to vertical and horizontal move
        bool isVerticalMove = (fromX == toX);
        if (isVerticalMove)
            horizontalBorder[std::min(fromY, toY)][fromX] = false;
        else
            verticalBorder[fromY][std::min(fromX, toX)] = false;

        // discover further paths in randomized directions
        if (toY == getRow() - 1 && toX == getCol() - 1)
            continue;
        std::shuffle(directions.begin(), directions.end(), rng);
        for (dir direction : directions)
            path.push({ toX, toY, toX + dirToVal[direction], toY + dirToVal[direction + 1] });
    }
}

