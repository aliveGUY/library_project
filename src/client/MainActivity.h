#pragma once
#include "../bridge/olc_net.h"
#include <chrono>
#include <iostream>

#include <wx/wx.h>
#include <wx/wrapsizer.h>
#include <wx/splitter.h>

#include <string>
#include <vector>

#include "activites/login.h"

#include "state/state.h"
#include "state/observer.h"

using namespace std;

class MainActivity : public wxFrame, public Observer
{
public:
    MainActivity(State *state, const wxString &title, const wxPoint &pos, const wxSize &size);

private:
    void UpdateActivity(string activity);

    wxTimer messageTimer;

private:
    wxPanel *login;
};

MainActivity::MainActivity(State *state, const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
    state->RegisterObserver(this);
    login = new LoginActivity(this, state);

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(login, 1, wxEXPAND | wxALL, 5);
    SetSizer(sizer);

    state->SetActivity("login");
}

void MainActivity::UpdateActivity(string activity)
{
    // login->Show(activity == "login");
    std::cout << activity << "\n";

    Layout();
}
