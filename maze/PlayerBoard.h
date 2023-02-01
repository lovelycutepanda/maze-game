/* This is the header file for the Player Board class.
 * The user can input keys WASD to move the character in the respective directions. 
 * Movements will be blocked when encountering borders in certain direction.
 * Upon reaching the goal, a message will appear and the user is no longer able to control the 
 * character movement.
 */


#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/wx.h>
#include "Board.h"
#include <vector>

#ifndef PLAYERBOARD_H
#define PLAYERBOARD_H

class PlayerBoard : public Board {
public:
    PlayerBoard(wxWindow*, const int, const int, std::vector<std::vector<bool>>&, 
                std::vector<std::vector<bool>>&);
    virtual void OnPaint(wxPaintEvent&);
    void OnKeyDown(wxKeyEvent&);

private:
    int const MARGIN;
    int posX, posY;
    wxImage playerIcon;
};

#endif // PLAYERBOARD_H




