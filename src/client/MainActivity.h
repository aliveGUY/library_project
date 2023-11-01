#pragma once
#include "../bridge/olc_net.h"
#include <chrono>
#include <iostream>

#include <wx/wx.h>
#include <wx/wrapsizer.h>
#include <wx/splitter.h>

#include <string>
#include <vector>

#include "activites/dashboard.h"
#include "activites/login.h"
#include "activites/bookPreview.h"

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
    DashboardActivity *dasboard;
    BookPreview *bookPreview;
};

MainActivity::MainActivity(State *state, const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
    state->RegisterObserver(this);
    dasboard = new DashboardActivity(this, state);
    login = new LoginActivity(this, state);
    bookPreview = new BookPreview(this, state);

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(dasboard, 1, wxEXPAND | wxALL, 5);
    sizer->Add(login, 1, wxEXPAND | wxALL, 5);
    sizer->Add(bookPreview, 1, wxEXPAND | wxALL, 5);
    SetSizer(sizer);

    state->SetActivity("login");
}

void MainActivity::UpdateActivity(string activity)
{
    dasboard->Show(activity == "dashboard");
    login->Show(activity == "login");
    bookPreview->Show(activity == "book preview");
    Layout();
}
