#pragma once

#include "../components/bookWrapper.h"
#include "../state/state.h"

class DashboardActivity : public wxPanel
{
public:
    DashboardActivity(wxWindow *parent, State state)
        : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize)
    {
        wxPanel *books = BookWrapper(this, state.GetData());
        wxButton *switchButton = new wxButton(this, wxID_ANY, "Log out");

        wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
        sizer->Add(switchButton, 0, wxALL | wxEXPAND, 10);
        sizer->Add(books, 1, wxALL | wxEXPAND, 10);
        SetSizer(sizer);
    }
};
