#pragma once

#include <wx/wx.h>
#include "../state/state.h"

class LoginActivity : public wxPanel
{
public:
    LoginActivity(wxWindow *parent, State *state) : wxPanel(parent, wxID_ANY), state(state)
    {
        wxButton *switchButton = new wxButton(this, wxID_ANY, "Login");
        switchButton->Bind(wxEVT_BUTTON, &LoginActivity::Login, this);

        wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
        sizer->Add(switchButton, 0, wxALIGN_CENTER | wxALL, 10);
        SetSizer(sizer);
    }

private:
    void Login(wxCommandEvent& event)
    {
        state->OnLogin();
    }

private:
    State *state;
};
