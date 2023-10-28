#include <wx/wx.h>
#include "../bridge/olc_net.h"
#include <chrono>
#include <iostream>

enum class CustomMsgTypes : uint32_t
{
    ServerAccept,
    ServerDeny,
    ServerPing,
    MessageAll,
    ServerMessage,
};

class MyFrame : public wxFrame, public olc::net::client_interface<CustomMsgTypes>
{
public:
    MyFrame();

private:
    void OnPing(wxCommandEvent &event);
    void MessageAll(wxCommandEvent &event);
    void CheckForMessages();
    void OnTimer(wxTimerEvent &event); // Timer event handler

    wxTimer messageTimer;
    wxStaticText *pingText;
    wxStaticText *messageText;
};

MyFrame::MyFrame() : wxFrame(nullptr, wxID_ANY, "Hello World")
{
    wxPanel *panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(panel, 1, wxEXPAND | wxALL, 5);

    wxButton *pingButton = new wxButton(panel, wxID_ANY, "Ping");
    wxButton *messageButton = new wxButton(panel, wxID_ANY, "Message");
    pingText = new wxStaticText(panel, wxID_ANY, "*empty*");
    messageText = new wxStaticText(panel, wxID_ANY, "*empty*");
    wxSizer *elemSizer = new wxBoxSizer(wxVERTICAL);

    elemSizer->Add(pingButton, 0, wxALIGN_CENTER_HORIZONTAL);
    elemSizer->Add(pingText, 0, wxALIGN_CENTER_HORIZONTAL, 0);
    elemSizer->Add(messageButton, 0, wxALIGN_CENTER_HORIZONTAL);
    elemSizer->Add(messageText, 0, wxALIGN_CENTER_HORIZONTAL, 0);

    Connect(pingButton->GetId(), wxEVT_BUTTON, wxCommandEventHandler(MyFrame::OnPing));
    Connect(messageButton->GetId(), wxEVT_BUTTON, wxCommandEventHandler(MyFrame::MessageAll));

    panel->SetSizerAndFit(elemSizer);
    this->SetSizerAndFit(sizer);

    messageTimer.Bind(wxEVT_TIMER, &MyFrame::OnTimer, this); // Bind timer event to OnTimer method
    messageTimer.Start(1000);                                // Adjust the interval as needed                            // Start the timer (adjust the interval as needed)
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

            pingText->SetLabel(std::to_string(std::chrono::duration<double>(timeNow - timeThen).count()));
        }
        break;

        case CustomMsgTypes::ServerMessage:
        {
            // Server has responded to a ping request
            uint32_t clientID;
            msg >> clientID;
            std::cout << "Hello from [" << clientID << "]\n";
            messageText->SetLabel("Hello from [" + std::to_string(clientID) + "]");
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
    MyFrame *frame = new MyFrame();
	frame->ConnectToServer("192.168.68.110", 60000);
    frame->Show(true);
    return true;
}

wxIMPLEMENT_APP(MyApp);
