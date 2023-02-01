/* This is the implementation file for the Prim's algorithm generator. */


#include "Generator.h"
#include "PrimGenerator.h"
#include <vector>
#include <random>

PrimGenerator::PrimGenerator(const int row, const int col) : Generator(row, col) {}

void PrimGenerator::getBorder(std::vector<std::vector<bool>> &verticalBorder, 
                              std::vector<std::vector<bool>> &horizontalBorder) {
    
    std::vector<std::vector<bool>> visited(getRow(), std::vector<bool>(getCol(), false));
    
    // each element in path is in form { fromX, fromY, toX, toY }
    std::vector<std::vector<int>> path;
    
    std::random_device dev;
    std::mt19937 rng(dev());

    // initialization
    for (int i = 0; i < 4; i++)
        path.push_back({ 0, 0, dirToVal[i], dirToVal[i + 1] });
        
    visited[0][0] = true;

    while (path.size()) {

        // get random item from path
        int index = rng() % path.size();
        std::vector<int>& item = path[index];
        int fromX = item[0], fromY = item[1], toX = item[2], toY = item[3];

        // swap index item with last item and pop
        item = path[path.size() - 1];
        path.pop_back();

        if (toX < 0 || toX >= getCol() || toY < 0 || toY >= getRow() || visited[toY][toX])
            continue;
        visited[toY][toX] = true;

        // set border according to vertical and horizontal move
        bool isVerticalMove = (fromX == toX);
        if (isVerticalMove)
            horizontalBorder[std::min(fromY, toY)][fromX] = false;
        else
            verticalBorder[fromY][std::min(fromX, toX)] = false;

        // discover further paths
        if (toY == getRow() - 1 && toX == getCol() - 1)
            continue;

        for (dir direction : directions)
            path.push_back({ toX, toY, toX + dirToVal[direction], toY + dirToVal[direction + 1] });
    }
}

