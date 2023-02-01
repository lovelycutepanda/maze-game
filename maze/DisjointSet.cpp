/* This is the implementation file for the Disjoint Set class. */


#include "DisjointSet.h"

DisjointSet::DisjointSet(int row, int col) : row(row), col(col) {
	// reshape 2D matrix into 1D array
	parent.resize(row * col, -1);
}

int DisjointSet::find(int posX, int posY) {
	int index = convert(posX, posY);
	while (parent[index] >= 0)
		index = parent[index];
	return index;
}

bool DisjointSet::group(int posX1, int posY1, int posX2, int posY2) {

	int index1 = find(posX1, posY1);
	int index2 = find(posX2, posY2);

	// return false if root labels are same, meaning the two grids are already groupped
	if (index1 == index2) return false;

	// add depth if both trees have equal depth
	bool addDepth = (parent[index1] == parent[index2]);

	// index1 is deeper
	if (parent[index1] < parent[index2]) parent[index2] = index1;
	else {
		parent[index1] = index2;
		parent[index2] -= addDepth;
	}
	return true;
}

int DisjointSet::convert(int posX, int posY) {
	return posY * col + posX;
}