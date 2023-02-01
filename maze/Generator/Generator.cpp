/* This is the implementation file for the Generator abstract class.
 * Implementation of method getBorder is provided in subclasses.
 */


#include "Generator.h"
#include <vector>

Generator::Generator(const int row, const int col) : row(row), col(col) {

    // Each pair of consecutive elements is unique, and we may extract two integers using this vector
    // instead of extracting a pair element
    dirToVal = { -1, 0, 1, 0, -1 };
    directions = { LEFT, UP, DOWN, RIGHT };
    visited.resize(getRow(), std::vector<bool>(getCol(), false));
}

int Generator::getRow() const {
    return row;
};

int Generator::getCol() const {
    return col;
};