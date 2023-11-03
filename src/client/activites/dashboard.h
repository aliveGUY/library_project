#pragma once

#include "../components/bookWrapper.h"
#include "../state/state.h"

class DashboardActivity : public wxPanel
{
public:
    DashboardActivity(wxWindow *parent, State *state)
        : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize), state(state)
    {
        wxPanel *books = BookWrapper(this, state->GetData(), state);
        wxButton *switchButton = new wxButton(this, wxID_ANY, "Log out");
        wxButton *cartButton = new wxButton(this, wxID_ANY, "Cart");
        switchButton->Bind(wxEVT_BUTTON, &DashboardActivity::LoginOut, this);
        cartButton->Bind(wxEVT_BUTTON, &DashboardActivity::OpenCart, this);

        wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
        sizer->Add(switchButton, 0, wxALL | wxEXPAND, 10);
        sizer->Add(cartButton, 0, wxALL |  wxEXPAND, 10);
        sizer->Add(books, 1, wxALL | wxEXPAND, 10);
        SetSizer(sizer);
    }

private:
    void LoginOut(wxCommandEvent &event)
    {
        state->SetActivity("login");
    }

    void OpenCart(wxCommandEvent &event)
    {
        state->SetActivity("book cart");
    }

private:
    State *state;
};
