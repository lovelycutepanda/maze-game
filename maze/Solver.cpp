/* This is the implementation file for the Solver abstract class. 
 * Implementation of method solve is provided in subclasses.
 */


#include "Solver.h"
#include <vector>

Solver::Solver(const int row, const int col, std::vector<std::vector<bool>>& verticalBorder, 
			   std::vector<std::vector<bool>>& horizontalBorder, MachineBoard* board) : 
			   row(row), col(col), verticalBorder(verticalBorder), horizontalBorder(horizontalBorder), 
			   board(board) { 
	
	// Each pair of consecutive elements is unique, and we may extract two integers using this vector
	// instead of extracting a pair element
	dirToVal = { -1, 0, 1, 0, -1 };
	directions = { LEFT, UP, DOWN, RIGHT };
	visited.resize(getRow(), std::vector<bool>(getCol(), false));
}

int Solver::getRow() const {
    return row;
};

int Solver::getCol() const {
    return col;
};

MachineBoard* Solver::getBoard() const {
    return board;
}

void Solver::move(std::vector<std::pair<int, int>>& path) {
    for (std::pair<int, int> &grid : path) {
		int posY = grid.first, posX = grid.second;
        getBoard()->walkGrid(posY, posX);
    }
}

bool Solver::isMoveValid(int posY, int posX, int newY, int newX) {
	bool isVertical = (posX == newX);
	if (newX < 0 || newX >= getCol() || newY < 0 || newY >= getRow() || visited[newY][newX])
		return false;
	if (isVertical && horizontalBorder[std::min(posY, newY)][posX])
		return false;
	if (!isVertical && verticalBorder[posY][std::min(posX, newX)])
		return false;
	return true;
}