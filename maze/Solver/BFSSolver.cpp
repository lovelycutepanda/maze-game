/* This is the implementation file for the Breadth-First search (BFS) agent. */


#include "Solver.h"
#include "BFSSolver.h"
#include <vector>
#include <queue>

BFSSolver::BFSSolver(const int row, const int col, std::vector<std::vector<bool>>& verticalBorder, 
					 std::vector<std::vector<bool>>& horizontalBorder, MachineBoard* board) : 
					 Solver(row, col, verticalBorder, horizontalBorder, board) {
	parent.resize(getRow(), std::vector<std::pair<int, int>>(getCol(), { -1, -1 }));
}

void BFSSolver::solve() {
	std::vector<std::pair<int, int>> path;
	BFS();
	backTrace(path);
	move(path);
}

void BFSSolver::BFS() {

	// initialization
	std::queue<std::pair<int, int>> grids;
	grids.push({ 0, 0 });

	while (true) {

		// get next grid and visit grid
		std::pair<int, int>& grid = grids.front();
		int posY = grid.first, posX = grid.second;
		visited[posY][posX] = true;
		getBoard()->visitGrid(posY, posX);
		grids.pop();
		if (posX == getCol() - 1 && posY == getRow() - 1)
			return;

		// go to each direction and add grid to visit list if move is possible
		for (dir direction : directions) {
			int newX = posX + dirToVal[direction], newY = posY + dirToVal[direction + 1];
			if (!isMoveValid(posY, posX, newY, newX))
				continue;
			grids.push({ newY, newX });
			parent[newY][newX] = { posY, posX };
		}
	}
	
	return;
}

void BFSSolver::backTrace(std::vector<std::pair<int, int>>& path) {

	// trace back from goal
	int posY = getRow() - 1, posX = getCol() - 1;
	while (posY != 0 || posX != 0) {

		// add previous grid to path
		std::pair<int, int>& grid = parent[posY][posX];
		int lastY = grid.first, lastX = grid.second;
		path.push_back({ posY, posX });
		posY = lastY; posX = lastX;
	}
	path.push_back({ 0, 0 });
	std::reverse(path.begin(), path.end());
}