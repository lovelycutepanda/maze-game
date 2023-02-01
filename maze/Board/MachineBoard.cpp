/* This is the implementation file for the Machine Board class. */


#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/wx.h>
#include "MachineBoard.h"
#include <vector>

MachineBoard::MachineBoard(wxWindow* parent, const int row, const int col, 
                           std::vector<std::vector<bool>>&verticalBorder, 
                           std::vector<std::vector<bool>>&horizontalBorder) : 
                           Board(parent, row, col, verticalBorder, horizontalBorder) {
    visited.resize(getRow(), std::vector<bool>(getCol(), false));
    walked.resize(getRow(), std::vector<bool>(getCol(), false));

    Bind(wxEVT_PAINT, &MachineBoard::OnPaint, this);
}

void MachineBoard::OnPaint(wxPaintEvent& WXUNUSED(event)) {

    wxPaintDC dc(this);

    drawStartAndGoal(dc);
    
    wxRect squareRect(wxSize(getSquareSize(), getSquareSize()));

    // set visited grid background
    wxDCBrushChanger brushChanger(dc, *wxCYAN_BRUSH);
    squareRect.SetTop(0);
    for (int posY = 0; posY < getRow(); posY++) {
        for (int posX = 0; posX < getCol(); posX++) {
            if (!visited[posY][posX]) continue;
            squareRect.SetLeft(posX * getSquareSize());
            dc.DrawRectangle(squareRect);
        }
        squareRect.Offset(0, getSquareSize());
    }

    // set walked grid background
    dc.SetBrush(*wxRED_BRUSH);
    squareRect.SetTop(0);
    for (int posY = 0; posY < getRow(); posY++) {
        for (int posX = 0; posX < getCol(); posX++) {
            if (!walked[posY][posX]) continue;
            squareRect.SetLeft(posX * getSquareSize());
            dc.DrawRectangle(squareRect);
        }
        squareRect.Offset(0, getSquareSize());
    }

    drawBorder(dc);
}

void MachineBoard::visitGrid(int posY, int posX) {
    if (visited[posY][posX])
        return;
    visited[posY][posX] = true;
    RefreshRect(wxRect(posX * getSquareSize(), posY * getSquareSize(), getSquareSize(), getSquareSize()));
    Update();
}

void MachineBoard::walkGrid(int posY, int posX) {
    walked[posY][posX] = true;
    RefreshRect(wxRect(posX * getSquareSize(), posY * getSquareSize(), getSquareSize(), getSquareSize()));
    Update();
}