/* This is the implementation file for the Kruskal's algorithm generator. */


#include "Generator.h"
#include "KruskalGenerator.h"
#include <vector>
#include "DisjointSet.h"
#include <random>

KruskalGenerator::KruskalGenerator(const int row, const int col) : Generator(row, col) {}

void KruskalGenerator::getBorder(std::vector<std::vector<bool>> &verticalBorder, 
                                 std::vector<std::vector<bool>> &horizontalBorder) {
    
    DisjointSet* djs = new DisjointSet(getRow(), getCol());

    // each element in borderList is in form { posX, posY, isVertical }
    std::vector<std::vector<int>> borderList;

    // add verical borders to borderList
    for (int i = 0; i < getRow(); i++)
        for (int j = 0; j < getCol() - 1; j++)
            borderList.push_back({ j, i, 1 });

    // add horizontal borders to borderList
    for (int i = 0; i < getRow() - 1; i++)
        for (int j = 0; j < getCol(); j++)
            borderList.push_back({ j, i, 0 });

    // randomize
    std::random_device dev;
    std::mt19937 rng(dev());
    std::shuffle(borderList.begin(), borderList.end(), rng);
    
    for (const auto& border : borderList) {

        // obtain grid positions of the two grids separated by the border
        int posX1 = border[0], posX2 = border[0], posY1 = border[1], posY2 = border[1];
        bool isVertical = border[2];
        if (isVertical)
            posX2++;
        else
            posY2++;

        // erase border if union is required
        if (djs->group(posX1, posY1, posX2, posY2)) {
            if (isVertical)
                verticalBorder[posY1][posX1] = false;
            else
                horizontalBorder[posY1][posX1] = false;
        }
    }
}

