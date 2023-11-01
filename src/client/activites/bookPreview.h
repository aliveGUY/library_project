#pragma once
#include <wx/wx.h>

class BookPreview : public wxPanel
{
public:
    BookPreview(wxWindow *parent, State state);

private:
    void Back(wxCommandEvent &event);

private: 
    State *state;
};

BookPreview::BookPreview(wxWindow *parent, State state) : wxPanel(parent, wxID_ANY), state(state)
{
    wxButton *switchButton = new wxButton(this, wxID_ANY, "Back to dashboard");
    switchButton->Bind(wxEVT_BUTTON, &BookPreview::Back, this);

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(switchButton, 0, wxALIGN_CENTER | wxALL, 10);
    SetSizer(sizer);
}

void BookPreview::Back(wxCommandEvent &event)
{
    state->SetActivity("dashboard");
}