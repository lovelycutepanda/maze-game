/* This is the implementation file for the Wilson's algorithm generator. */


#include "Generator.h"
#include "WilsonGenerator.h"
#include <vector>
#include <random>

WilsonGenerator::WilsonGenerator(const int row, const int col) : Generator(row, col) {
    visited.resize(getRow(), std::vector<bool>(getCol(), false));
}

void WilsonGenerator::getBorder(std::vector<std::vector<bool>> &verticalBorder, 
                                std::vector<std::vector<bool>> &horizontalBorder) {

    // initially pick a random grid, we may take the top left grid for simplicity
    visited[0][0] = true;

    // when not all grids are visited, pick random grid and perform random walk
    // again for simplicity we may pick grids from top left to bottom right
    for (int i = 0; i < getRow(); i++)
        for (int j = 0; j < getCol(); j++) {
            if (visited[i][j]) continue;
            std::vector<dir> path;
            randomWalk(i, j, path);

            // walk and eliminate borders along the path 
            int posY = i, posX = j;
            for (dir direction : path) {
                visited[posY][posX] = true;
                switch (direction) {
                case LEFT:
                    verticalBorder[posY][posX - 1] = false;
                    posX--;
                    break;
                case UP:
                    horizontalBorder[posY - 1][posX] = false;
                    posY--;
                    break;
                case RIGHT:
                    verticalBorder[posY][posX] = false;
                    posX++;
                    break;
                case DOWN:
                    horizontalBorder[posY][posX] = false;
                    posY++;
                    break;
                default:
                    break;
                }
            }
        }
}

void WilsonGenerator::randomWalk(int posY, int posX, std::vector<dir> &path) {

    // record initial position
    int originalX = posX, originalY = posY;

    // path map 
    std::vector<std::vector<dir>> arrowPath(getRow(), std::vector<dir>(getCol(), NONE));

    // randomIndex corresponds to the direction order
    std::random_device dev;
    std::mt19937 rng(dev());

    // mark down arrows in path map until an existing maze grid is found
    while (!visited[posY][posX]) {
        dir direction = directions[rng() % 4];
        int newX = posX + dirToVal[direction], newY = posY + dirToVal[direction + 1];
        if (newX < 0 || newX >= getCol() || newY < 0 || newY >= getRow())
            continue;
        arrowPath[posY][posX] = direction;
        posX = newX; 
        posY = newY;
    }

    // travel along the arrow path and record, neglect other arrows
    posX = originalX; posY = originalY;
    while (!visited[posY][posX]) {
        dir direction = arrowPath[posY][posX];
        path.push_back(direction);
        posX += dirToVal[direction]; posY += dirToVal[direction + 1];
    }
}
