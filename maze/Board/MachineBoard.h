/* This is the header file for the Machine Board class.
 * Instance of this class is "controlled" by the solver agent chosen by the user.
 * It does not accept any key inputs and shows only the bot search progress and the final result.
 * The search progress is visualized by blue grids, while final path result is visualized by red 
 * grids.
 */


#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/wx.h>
#include "Board.h"
#include <vector>

#ifndef MACHINEBOARD_H
#define MACHINEBOARD_H

class MachineBoard : public Board {
public:
    MachineBoard(wxWindow*, const int, const int, std::vector<std::vector<bool>>&, 
                 std::vector<std::vector<bool>>&);
    virtual void OnPaint(wxPaintEvent&);

    // called by bot during the search progress
    void visitGrid(int, int);

    // called by bot after result is found
    void walkGrid(int, int);

private:

    // grids visited during the bot search progress
    std::vector<std::vector<bool>> visited;

    // grids corresponding to final path result
    std::vector<std::vector<bool>> walked;
};

#endif // MACHINEBOARD_H




