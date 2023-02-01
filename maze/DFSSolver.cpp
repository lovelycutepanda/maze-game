/* This is the implementation file for the Depth-First search (DFS) solver. */


#include "Solver.h"
#include "DFSSolver.h"
#include <vector>
#include <stack>

DFSSolver::DFSSolver(const int row, const int col, std::vector<std::vector<bool>>& verticalBorder, 
					 std::vector<std::vector<bool>>& horizontalBorder, MachineBoard* board) : 
					 Solver(row, col, verticalBorder, horizontalBorder, board) { }

void DFSSolver::solve() {
	std::vector<std::pair<int, int>> path;
	DFS(0, 0, path);
	move(path);
}

bool DFSSolver::DFS(int posY, int posX, std::vector<std::pair<int, int>>& path) {

	if (visited[posY][posX])
		return false;

	// add current grid to the path
	visited[posY][posX] = true;
	getBoard()->visitGrid(posY, posX);
	path.push_back({ posY, posX });
	if (posX == getCol() - 1 && posY == getRow() - 1)
		return true;

	// go to each direction and explore the path until either goal is reached or dead end is met
	for (dir direction : directions) {
		int newX = posX + dirToVal[direction], newY = posY + dirToVal[direction + 1];
		if (!isMoveValid(posY, posX, newY, newX))
			continue;
		if (DFS(newY, newX, path))
			return true;
	}

	// if no further path returns true, a dead end is met and the grid is removed from the path
	path.pop_back();
	return false;
}
