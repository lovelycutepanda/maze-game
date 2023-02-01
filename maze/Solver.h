/* This is the header file for the Solver abstract class.
 * This class contains a Machine Board object pointer, which allows it to "control" the machine board
 * directly like how a human player controls the player board.
 * This class handles move validation, as well as printing visited grids and result path in the board.
 * The solve method implementation is entirely dependent on the algorithm chosen and is hence purely 
 * virtual. 
 */


#include "MachineBoard.h"
#include <vector>

#ifndef SOLVER_H
#define SOLVER_H

class Solver {
public:
    enum dir {
        LEFT = 0,
        DOWN = 1,
        RIGHT = 2,
        UP = 3
    };

    Solver(const int, const int, std::vector<std::vector<bool>>&, std::vector<std::vector<bool>>&, 
           MachineBoard*);
    virtual void solve() = 0;
    int getRow() const;
    int getCol() const;
    MachineBoard* getBoard() const;

    // call this method with the path to print the path in the machine board
    void move(std::vector<std::pair<int, int>>&);
    bool isMoveValid(int, int, int, int);

    std::vector<int> dirToVal;

    // a list of directions 
    std::vector<dir> directions;
    std::vector<std::vector<bool>> visited;

private:
    int row, col;
    MachineBoard* board;
    std::vector<std::vector<bool>>& verticalBorder, & horizontalBorder;
};

#endif // SOLVER_H

