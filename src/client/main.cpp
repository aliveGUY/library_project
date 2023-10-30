#include "../bridge/olc_net.h"
#include <chrono>
#include <iostream>

#include <wx/wx.h>
#include <wx/wrapsizer.h>
#include <wx/splitter.h>

#include <string>
#include <vector>

#include "components/bookCard.h"
#include "components/bookWrapper.h"

#include "activites/dashboard.h"
#include "activites/login.h"

#include "state/state.h"
#include "state/observer.h"

using namespace std;

enum class CustomMsgTypes : uint32_t
{
    ServerAccept,
    ServerDeny,
    ServerPing,
    MessageAll,
    ServerMessage,
};

class MyFrame : public wxFrame, public Observer, public olc::net::client_interface<CustomMsgTypes>
{
public:
    MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size);

private:
    void OnPing(wxCommandEvent &event);
    void MessageAll(wxCommandEvent &event);
    void CheckForMessages();
    void OnTimer(wxTimerEvent &event);
    void SwitchPanel(string activity);
    void Update();

    wxTimer messageTimer;

private:
    State state;
    wxPanel *dasboard;
    wxPanel *login;
};

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size), state()
{

    dasboard = new DashboardActivity(this, state);
    login = new LoginActivity(this, &state);
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(dasboard, 1, wxEXPAND | wxALL, 5);
    sizer->Add(login, 1, wxEXPAND | wxALL, 5);
    SetSizer(sizer);

    messageTimer.Bind(wxEVT_TIMER, &MyFrame::OnTimer, this);
    messageTimer.Start(1000);

    SwitchPanel("login");
}

void MyFrame::SwitchPanel(string activity)
{
    dasboard->Show(activity == "dashboard");
    login->Show(activity == "login");

    Layout();
}
void MyFrame::Update()
{
    SwitchPanel(state.GetActivity());
}

void MyFrame::OnPing(wxCommandEvent &event)
{
    olc::net::message<CustomMsgTypes> msg;
    msg.header.id = CustomMsgTypes::ServerPing;

    // Caution with this...
    std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();

    msg << timeNow;
    Send(msg);
}

void MyFrame::MessageAll(wxCommandEvent &event)
{
    olc::net::message<CustomMsgTypes> msg;
    msg.header.id = CustomMsgTypes::MessageAll;
    Send(msg);
}

void MyFrame::OnTimer(wxTimerEvent &event)
{
    CheckForMessages();
}

void MyFrame::CheckForMessages()
{
    while (IsConnected() && !Incoming().empty())
    {
        auto msg = Incoming().pop_front().msg;
        switch (msg.header.id)
        {
        case CustomMsgTypes::ServerAccept:
        {
            // Server has responded to a ping request
            std::cout << "Server Accepted Connection\n";
        }
        break;

        case CustomMsgTypes::ServerPing:
        {
            // Server has responded to a ping request
            std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();
            std::chrono::system_clock::time_point timeThen;
            msg >> timeThen;
            std::cout << "Ping: " << std::chrono::duration<double>(timeNow - timeThen).count() << "\n";
        }
        break;

        case CustomMsgTypes::ServerMessage:
        {
            // Server has responded to a ping request
            uint32_t clientID;
            msg >> clientID;
            std::cout << "Hello from [" << clientID << "]\n";
        }
        break;
        }
    }
}

class MyApp : public wxApp
{
public:
    bool OnInit() override;
};

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame("Hello World", wxDefaultPosition, wxDefaultSize);
    frame->ConnectToServer("192.168.68.110", 60000);
    frame->Show(true);
    return true;
}

wxIMPLEMENT_APP(MyApp);
