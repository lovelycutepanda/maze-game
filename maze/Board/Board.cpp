/* This is the implementation file for the Board class. */


#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/wx.h>
#include "Board.h"

Board::Board(wxWindow* parent, const int row, const int col, 
             std::vector<std::vector<bool>> &verticalBorder, 
             std::vector<std::vector<bool>> &horizontalBorder) : wxPanel(parent, wxID_ANY), 
             WIDTH(1200), HEIGHT(800), BORDER_SIZE(3), row(row), col(col), finished(false),
             verticalBorder(verticalBorder), horizontalBorder(horizontalBorder) {
    SetBackgroundColour(*wxWHITE);
    squareSize = std::min(WIDTH / getCol(), HEIGHT / getRow());
    SetInitialSize(getBoardSize());
}

int Board::getRow() const {
    return row;
};

int Board::getCol() const {
    return col;
};

int Board::getSquareSize() const {
    return squareSize;
};

bool Board::isFinished() const {
    return finished;
}

void Board::setFinished(bool finished) {
    this->finished = finished;
}

bool Board::isVerticalBorder(int posY, int posX) const {
    if (posY < 0 || posY > getRow() || posX < 0 || posX > getCol() - 1)
        return false;
    return verticalBorder[posY][posX];
}

bool Board::isHorizontalBorder(int posY, int posX) const {
    if (posY < 0 || posY > getRow() - 1 || posX < 0 || posX > getCol())
        return false;
    return horizontalBorder[posY][posX];
}

wxSize Board::getBoardSize() const {
    return wxSize(getCol() * getSquareSize(), getRow() * getSquareSize());
}

void Board::drawStartAndGoal(wxDC& dc) {
    wxDCPenChanger penChanger(dc, *wxTRANSPARENT_PEN);
    wxRect squareRect(wxSize(getSquareSize(), getSquareSize()));

    // set start
    wxDCBrushChanger brushChanger(dc, *wxYELLOW_BRUSH);
    squareRect.SetLeft(0);
    squareRect.SetTop(0);
    dc.DrawRectangle(squareRect);

    // set goal
    dc.SetBrush(*wxGREEN_BRUSH);
    squareRect.SetLeft((getCol() - 1) * getSquareSize());
    squareRect.SetTop((getRow() - 1) * getSquareSize());
    dc.DrawRectangle(squareRect);
}

void Board::drawBorder(wxDC& dc) {
    wxDCBrushChanger brushChanger(dc, *wxBLACK_BRUSH);

    wxRect verticalRect(wxSize(BORDER_SIZE * 2, getSquareSize()));
    wxRect horizontalRect(wxSize(getSquareSize(), BORDER_SIZE * 2));

    // set vertical borders
    for (int posY = 0; posY < getRow(); posY++) {
        verticalRect.SetLeft(-BORDER_SIZE);
        dc.DrawRectangle(verticalRect);
        for (int posX = 0; posX < getCol() - 1; posX++) {
            if (!isVerticalBorder(posY, posX)) continue;
            verticalRect.SetLeft((posX + 1) * getSquareSize() - BORDER_SIZE);
            dc.DrawRectangle(verticalRect);
        }
        verticalRect.SetLeft(getCol() * getSquareSize() - BORDER_SIZE);
        dc.DrawRectangle(verticalRect);
        verticalRect.Offset(0, getSquareSize());
    }

    // set horizontal borders
    for (int posX = 0; posX < getCol(); posX++) {
        horizontalRect.SetTop(-BORDER_SIZE);
        dc.DrawRectangle(horizontalRect);
        for (int posY = 0; posY < getRow() - 1; posY++) {
            if (!isHorizontalBorder(posY, posX)) continue;
            horizontalRect.SetTop((posY + 1) * getSquareSize() - BORDER_SIZE);
            dc.DrawRectangle(horizontalRect);
        }
        horizontalRect.SetTop(getRow() * getSquareSize() - BORDER_SIZE);
        dc.DrawRectangle(horizontalRect);
        horizontalRect.Offset(getSquareSize(), 0);
    }
}