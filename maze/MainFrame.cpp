/* This is the implementation file for the Main Frame class. */


#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/wx.h>
#include "wx/numdlg.h" // wxGetNumberFromUser
#include "MainFrame.h"

// Boards
#include "Board/Board.h"
#include "Board/PlayerBoard.h"
#include "Board/MachineBoard.h"

// Generators
#include "Generator/Generator.h"
#include "Generator/DFSGenerator.h"
#include "Generator/KruskalGenerator.h"
#include "Generator/PrimGenerator.h"
#include "Generator/WilsonGenerator.h"

// Solvers
#include "Solver/Solver.h"
#include "Solver/DFSSolver.h"
#include "Solver/BFSSolver.h"
#include "Solver/AStarSolver.h"

#include <vector>

MainFrame::MainFrame() : wxFrame(NULL, wxID_ANY, "maze game"), board(NULL), row(-1), col(-1) {

    // buttons for generating new maze
    wxMenu* menuNewMaze = new wxMenu;
    menuNewMaze->Append(DFSGeneration, "DFS",
        "Create a maze using depth-first search algorithm");
    menuNewMaze->Append(KruskalGeneration, "Kruskal",
        "Create a maze using Kruskal's algorithm");
    menuNewMaze->Append(PrimGeneration, "Prim",
        "Create a maze using Prim's algorithm");
    menuNewMaze->Append(WilsonGeneration, "Wilson",
        "Create a maze using Wilson's algorithm");

    // buttons for solving existing maze
    wxMenu* menuSolve = new wxMenu;
    menuSolve->Append(DFSSolve, "DFS",
        "Solve the maze using depth-first search algorithm");
    menuSolve->Append(BFSSolve, "BFS",
        "Solve the maze using breadth-first search algorithm");
    menuSolve->Append(AStarSolve, "A*",
        "Solve the maze using A* search algorithm");

    // help button
    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    // set up menu bar
    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuNewMaze, "&New maze");
    menuBar->Append(menuSolve, "&Solve");
    menuBar->Append(menuHelp, "&Help");

    SetMenuBar(menuBar);

    // sizer for board
    mainSizer = new wxBoxSizer(wxVERTICAL);

    // status bar
    CreateStatusBar();
    SetStatusText("");

    // dynamic event bindings, in-line functions are used for simplicity
    Bind(wxEVT_MENU, [=](wxCommandEvent&) {GenerateMaze(DFSGeneration);}, DFSGeneration);
    Bind(wxEVT_MENU, [=](wxCommandEvent&) {GenerateMaze(KruskalGeneration);}, KruskalGeneration);
    Bind(wxEVT_MENU, [=](wxCommandEvent&) {GenerateMaze(PrimGeneration);}, PrimGeneration);
    Bind(wxEVT_MENU, [=](wxCommandEvent&) {GenerateMaze(WilsonGeneration);}, WilsonGeneration);
    Bind(wxEVT_MENU, [=](wxCommandEvent&) {SolveMaze(DFSSolve);}, DFSSolve);
    Bind(wxEVT_MENU, [=](wxCommandEvent&) {SolveMaze(BFSSolve);}, BFSSolve);
    Bind(wxEVT_MENU, [=](wxCommandEvent&) {SolveMaze(AStarSolve);}, AStarSolve);
    Bind(wxEVT_MENU, &MainFrame::OnAbout, this, wxID_ABOUT);
}

void MainFrame::OnAbout(wxCommandEvent& event) {
    wxMessageBox("Your goal is to move from the top left to the bottom right.\n"
        "However, there are borders that block you from moving across.\n"
        "To control your character movement, use WASD control.\n"
        "Try to find the fastest path to the green square!\n"
        "If you cannot solve it, you may also solve using the bots.",
        "About this maze game", wxOK | wxICON_INFORMATION);
}

void MainFrame::GenerateMaze(botID bot) {

    // remove existing board if exists
    if (board) {
        if (!board->isFinished()) {
            wxMessageDialog dialog(this,
                "Are you sure to abandon this game?",
                "Message box text",
                wxCENTER | wxYES | wxNO | wxICON_INFORMATION);
            dialog.SetYesNoLabels("Yes", "No");
            if (dialog.ShowModal() == wxID_NO)
                return;
        }
        delete board;
        board = NULL;
        mainSizer->Clear(true);
    }

    row = wxGetNumberFromUser("Please enter the number of rows for the maze.\n"
        "It should be between 4 and 20.\n"
        "Default value is 12.",
        "Number of rows:", wxEmptyString,
        12, 4, 20, this);
    if (row == -1) return;

    col = wxGetNumberFromUser("Please enter the number of columns for the maze.\n"
        "It should be between 6 and 30.\n"
        "Default value is 18.",
        "Number of columns:", wxEmptyString,
        18, 6, 30, this);
    if (col == -1) return;

    SetStatusText("Generating maze...");

    // obtain borders from chosen algorithm
    Generator* generator = NULL;
    switch (bot) {
    case (DFSGeneration):
        generator = new DFSGenerator(row, col);
        break;
    case (KruskalGeneration):
        generator = new KruskalGenerator(row, col);
        break;
    case (PrimGeneration):
        generator = new PrimGenerator(row, col);
        break;
    case (WilsonGeneration):
        generator = new WilsonGenerator(row, col);
        break;
    default:
        break;
    }

    // reset borders
    verticalBorder = std::vector<std::vector<bool>>(row, std::vector<bool>(col - 1, true));
    horizontalBorder = std::vector<std::vector<bool>>(row - 1, std::vector<bool>(col, true));

    if (generator) generator->getBorder(verticalBorder, horizontalBorder);

    delete generator;
    generator = NULL;

    // display board for play
    board = new PlayerBoard(this, row, col, verticalBorder, horizontalBorder);
    mainSizer->AddStretchSpacer(1);
    mainSizer->Add(board, wxSizerFlags().TripleBorder().CenterHorizontal());
    mainSizer->AddStretchSpacer(1);
    board->SetFocus();

    SetSizerAndFit(mainSizer);
    mainSizer->Layout();

    SetStatusText("");
}

void MainFrame::SolveMaze(botID bot) {

    // return if there is no existing board
    if (!board) {
        wxMessageBox("There is no maze game currently. Please start a new maze game first!");
        return;
    }

    SetStatusText("Solving maze...");

    // regenerate board
    delete board;
    board = NULL;
    mainSizer->Clear(true);

    board = new MachineBoard(this, row, col, verticalBorder, horizontalBorder);
    mainSizer->AddStretchSpacer(1);
    mainSizer->Add(board, wxSizerFlags().TripleBorder().CenterHorizontal());
    mainSizer->AddStretchSpacer(1);
    board->SetFocus();

    SetSizerAndFit(mainSizer);
    mainSizer->Layout();

    // obtain solver from chosen algorithm
    Solver* solver = NULL;
    switch (bot) {
    case (DFSSolve):
        solver = new DFSSolver(row, col, verticalBorder, horizontalBorder, (MachineBoard*)board);
        break;
    case (BFSSolve):
        solver = new BFSSolver(row, col, verticalBorder, horizontalBorder, (MachineBoard*)board);
        break;
    case (AStarSolve):
        solver = new AStarSolver(row, col, verticalBorder, horizontalBorder, (MachineBoard*)board);
        break;
    default:
        break;
    }

    solver->solve();

    wxMessageBox("We have found the path to the goal!");
    SetStatusText("Maze solved!");
}