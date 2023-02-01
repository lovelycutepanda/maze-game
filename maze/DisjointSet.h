/* This is the header file for the Disjoint Set class.
 * A Disjoint Set is used to keep track of the groupings.
 * If two elements from two distinct groups are groupped, the two groups will be merged together.
 * It is used for the Kruskal's algorithm, which involves groupings of grids.
 * Unlike usual implementation where method group should return void, I choose to return boolean here
 * since it can be used to inform whether the grids are already groupped originally.
 */


#include <vector>

#ifndef DISJOINTSET_H
#define DISJOINTSET_H

class DisjointSet {
public:
	DisjointSet(int, int);

	// get the root label of the grid
	int find(int, int);

	// union the two selected grids, returns false if two grids are already groupped else true
	bool group(int, int, int, int);

private:
	// negative means parent is itself with tree depth = magnitude, 
	// otherwise parent is the index indicated by the value
	std::vector<int> parent;

	// convert 2D position into 1D virtual position
	int convert(int, int);
	int row, col;
};

#endif // DISJOINTSET_H

