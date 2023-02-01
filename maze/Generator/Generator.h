/* This is the header file for the Generator abstract class.
 * This class is used to initialize instances from different subclasses
 * The getBorder method implementation is entirely dependent on the algorithm chosen and is hence 
 * purely virtual.
 */


#include <vector>

#ifndef GENERATOR_H
#define GENERATOR_H

class Generator {
public:
    enum dir {
        LEFT = 0,
        DOWN = 1,
        RIGHT = 2,
        UP = 3,
        NONE = -1
    };

    Generator(const int, const int);
    virtual void getBorder(std::vector<std::vector<bool>>&, std::vector<std::vector<bool>>&) = 0;
    int getRow() const;
    int getCol() const;

    std::vector<int> dirToVal;

    // a list of directions in dir
    std::vector<dir> directions;
    std::vector<std::vector<bool>> visited;

private:
    const int row;
    const int col;
};

#endif // GENERATOR_H




