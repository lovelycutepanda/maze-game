/* This is the implementation file for the class MazeApp.
 * It serves as the basis class for the whole application and is used to initialize the main frame.
 */


#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/wx.h>
#include "MainFrame.h"

class MazeApp : public wxApp {
public:
    virtual bool OnInit() {
        MainFrame* mainFrame = new MainFrame();
        mainFrame->Show(true);
        return true;
    }
};

IMPLEMENT_APP(MazeApp);