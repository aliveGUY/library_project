#pragma once
#include <wx/wx.h>

#include <iostream>
#include "../components/book.h"

#include <string>

using namespace std;

class BookPreview : public wxPanel
{
public:
    BookPreview(wxWindow *parent, State *state);
    bool Show(bool show);

private:
    void Back(wxCommandEvent &event);

private:
    State *state;
    Book *book;

private:
    wxStaticText *author;
    wxStaticText *title;
};

BookPreview::BookPreview(wxWindow *parent, State *state) : wxPanel(parent, wxID_ANY), state(state)
{
    wxButton *switchButton = new wxButton(this, wxID_ANY, "Back to dashboard");
    author = new wxStaticText(this, wxID_ANY, "Loading author");
    title = new wxStaticText(this, wxID_ANY, "Loading title");

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(switchButton, 0, wxALIGN_CENTER | wxALL, 10);
    sizer->Add(title, 0, wxALIGN_CENTER | wxALL, 10);
    sizer->Add(author, 0, wxALIGN_CENTER | wxALL, 10);

    switchButton->Bind(wxEVT_BUTTON, &BookPreview::Back, this);
    SetSizer(sizer);
}

void BookPreview::Back(wxCommandEvent &event)
{
    state->SetActivity("dashboard");
}

bool BookPreview::Show(bool show)
{
    std::cout << "show preview\n";

    if (state->bookIsSelected)
    {
        book = state->GetSelectedBook();

        title->SetLabel(book->GetTitle());
        author->SetLabel(book->GetAuthor());
    }

    return wxPanel::Show(show);
}
