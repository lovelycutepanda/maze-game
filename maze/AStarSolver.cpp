/* This is the implementation file for the A* search agent. */


#include "Solver.h"
#include "AStarSolver.h"
#include <vector>
#include <queue> // priority_queue

AStarSolver::AStarSolver(const int row, const int col, std::vector<std::vector<bool>>& verticalBorder, 
						 std::vector<std::vector<bool>>& horizontalBorder, MachineBoard* board) : 
						 Solver(row, col, verticalBorder, horizontalBorder, board) {
	parent.resize(getRow(), std::vector<std::pair<int, int>>(getCol(), { -1, -1 }));
}

void AStarSolver::solve() {
	std::vector<std::pair<int, int>> path;
	AStar();
	backTrace(path);
	move(path);
}

void AStarSolver::AStar() {

	// initialization
	// in-line comparison function for priority queue
	auto comp = [&](std::pair<int, int>& grid1, std::pair<int, int>& grid2) -> bool {
		return heuristic(grid1) > heuristic(grid2);
	};
	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, 
						decltype(comp)> grids (comp);
	grids.push({ 0, 0 });

	while (true) {

		// get grid with lowest heuristic value (closest) and visit grid
		std::pair<int, int> grid = grids.top();
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

			// mark parent of grid for back tracing
			parent[newY][newX] = { posY, posX };
		}
	}
	
	return;
}

void AStarSolver::backTrace(std::vector<std::pair<int, int>>& path) {

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

// use vector L1 norm (Manhattan norm) distance as the heuristic function, may replace by any norm
int AStarSolver::heuristic(std::pair<int, int>& grid) {
	return getRow() - 1 - grid.first + getCol() - 1 - grid.second;
}