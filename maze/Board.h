/* This is the header file for the Board class.
 * This class is used to initialize instances from the two board types, as well as storing the board
 * parameters.
 * Exact painting method is different for different boards so implementation of OnPaint is not 
 * provided here.
 * However, the two methods drawStartAndGoal and drawBorder can be called for all subclasses inside 
 * the respective OnPaint method.
 */


#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/wx.h>
#include <vector>

#ifndef BOARD_H
#define BOARD_H

class Board : public wxPanel {
public:
    Board(wxWindow*, const int, const int, std::vector<std::vector<bool>>&, 
          std::vector<std::vector<bool>>&);
    int getRow() const;
    int getCol() const;
    int getSquareSize() const;
    bool isFinished() const;
    void setFinished(bool);
    bool isVerticalBorder(int, int) const;
    bool isHorizontalBorder(int, int) const;

    // used for subclass OnPaint method
    void drawStartAndGoal(wxDC&);
    void drawBorder(wxDC&);

private:
    const int WIDTH;
    const int HEIGHT;
    const int BORDER_SIZE;
    int row, col, squareSize;
    bool finished;
    std::vector<std::vector<bool>>& verticalBorder, & horizontalBorder;
    wxSize getBoardSize() const;
};

#endif // BOARD_H




