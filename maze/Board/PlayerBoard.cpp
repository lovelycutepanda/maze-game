/* This is the implementation file for the Player Board class. */


#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/wx.h>
#include "PlayerBoard.h"
#include <vector>
#include "../MainFrame.h" // for setting status bar text

PlayerBoard::PlayerBoard(wxWindow* parent, const int row, const int col, 
                         std::vector<std::vector<bool>>&verticalBorder, 
                         std::vector<std::vector<bool>>&horizontalBorder) : 
                         Board(parent, row, col, verticalBorder, horizontalBorder), posX(0), posY(0),
                         MARGIN(5) {
    // set icon
    wxImage::AddHandler(new wxPNGHandler);
    playerIcon.LoadFile(wxT("panda_image.png"), wxBITMAP_TYPE_PNG);
    playerIcon.Rescale(getSquareSize() - MARGIN * 2, getSquareSize() - MARGIN * 2);

    ((MainFrame*)GetParent())->SetStatusText("");

    Bind(wxEVT_PAINT, &PlayerBoard::OnPaint, this);
    Bind(wxEVT_KEY_DOWN, &PlayerBoard::OnKeyDown, this);
}

void PlayerBoard::OnPaint(wxPaintEvent& WXUNUSED(event)) {

    wxPaintDC dc(this);

    drawStartAndGoal(dc);
    drawBorder(dc);

    dc.DrawBitmap(playerIcon, posX * getSquareSize() + MARGIN, posY * getSquareSize() + MARGIN, true);
}

void PlayerBoard::OnKeyDown(wxKeyEvent& event) {
    event.Skip();

    // neglect keys after game ended
    if (isFinished()) return;

    // corresponding movement of character
    switch (event.GetKeyCode()) {
    case 'A':
        if (posX == 0 || isVerticalBorder(posY, posX - 1))
            return;
        posX--;
        RefreshRect(wxRect(posX * getSquareSize(), posY * getSquareSize(), 
                           2 * getSquareSize(), getSquareSize()));
        break;
    case 'W':
        if (posY == 0 || isHorizontalBorder(posY - 1, posX))
            return;
        posY--;
        RefreshRect(wxRect(posX * getSquareSize(), posY * getSquareSize(), 
                           getSquareSize(), 2 * getSquareSize()));
        break;
    case 'D':
        if (posX == getCol() - 1 || isVerticalBorder(posY, posX))
            return;
        posX++;
        RefreshRect(wxRect((posX - 1) * getSquareSize(), posY * getSquareSize(), 
                           2 * getSquareSize(), getSquareSize()));
        break;
    case 'S':
        if (posY == getRow() - 1 || isHorizontalBorder(posY, posX))
            return;
        posY++;
        RefreshRect(wxRect(posX * getSquareSize(), (posY - 1) * getSquareSize(), 
                           getSquareSize(), 2 * getSquareSize()));
        break;
    default:
        return;
    }

    // end game if position is goal
    if (posX == getCol() - 1 && posY == getRow() - 1) {
        setFinished(true);
        wxMessageBox("Congratulations! You reached the goal.");
        ((MainFrame*)GetParent())->SetStatusText("You reached the goal!");
    }

    Update();
}