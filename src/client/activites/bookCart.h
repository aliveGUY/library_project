#pragma once

#include <wx/wx.h>
#include "../state/state.h"

class BookCart : public wxPanel
{
public:
    BookCart(wxWindow *parent, State *state) : wxPanel(parent, wxID_ANY), state(state)
    {
       wxStaticText *text = new wxStaticText(this, wxID_ANY, "Cart");


        wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
        sizer->Add(text, 0, wxALIGN_CENTER | wxALL, 10);
        SetSizer(sizer);
    }


private:
    State *state;
};
