#include <wx/wx.h>
#include "MainActivity.h"

class MyApp : public wxApp
{
public:
    bool OnInit() override;
};

bool MyApp::OnInit()
{
    State state;
    MainActivity *frame = new MainActivity(state, "Hello World", wxDefaultPosition, wxDefaultSize);
    frame->ConnectToServer("192.168.68.110", 60000);
    frame->Show(true);
    return true;
}

wxIMPLEMENT_APP(MyApp);
