/* This is the header file for the Main Frame class.
 * This class is used to display the frame for GUI and is essential to any GUI application.
 * In this frame, I keep a list of botID to clarify the algorithm chosen.
 * Also, according to the botID, a different board is created.
 * A Machine Board instance requires the parameters from an existing board (Player or Machine), so it 
 * will only be created if a board exists before calling SolveMaze method.
 */


#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/wx.h>
#include "Board/Board.h"
#include "Generator/Generator.h"
#include <vector>

class MainFrame : public wxFrame {
public:
    MainFrame();

private:
    enum botID {
        DFSGeneration,
        KruskalGeneration,
        PrimGeneration,
        WilsonGeneration,
        DFSSolve,
        BFSSolve,
        AStarSolve
    };

    Board* board;

    // used to position board and resize window
    wxSizer* mainSizer;
    int row, col;
    std::vector<std::vector<bool>> verticalBorder;
    std::vector<std::vector<bool>> horizontalBorder;

    void OnAbout(wxCommandEvent&);

    // creates a Player Board instance according to generator algorithm
    void GenerateMaze(botID);

    // solves the current board instance according to solver algorithm
    void SolveMaze(botID);
};