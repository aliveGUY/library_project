#pragma once

#include <iostream>
#include <string>

#include <wx/wx.h>
#include <wx/graphics.h>

#include "../helpers/textOverflow.h"
#include "book.h"
#include "../state/state.h"

class BookCard : public wxWindow
{
private:
    wxColour color;
    std::string title;
    std::string author;

    Book book;
    State *state;

public:
    BookCard(wxWindow *parent, State *state, wxWindowID id, const Book &book, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize);

    wxSize DoGetBestSize() const override
    {
        return FromDIP(wxSize(100, 130));
    }

private:
    void OnPaint(wxPaintEvent &event);
    void OnClick(wxMouseEvent &event);


};

BookCard::BookCard(wxWindow *parent, State *state, wxWindowID id, const Book &book, const wxPoint &pos, const wxSize &size)
    : wxWindow(parent, id, pos, size), book(book), state(state)
{

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    wxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);

    auto controlsPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    sizer->Add(controlsPanel, 1, wxEXPAND | wxALL, 5);

    auto title = new wxStaticText(controlsPanel, wxID_ANY, handleTextOverflow(book.GetTitle(), 30), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL);
    mainSizer->Add(title, 2, wxALL | wxEXPAND);

    auto author = new wxStaticText(controlsPanel, wxID_ANY, handleTextOverflow("by " + book.GetAuthor(), 30));
    mainSizer->Add(author, 1, wxALL);

    controlsPanel->SetSizer(mainSizer);
    this->SetSizer(sizer);

    Bind(wxEVT_PAINT, &BookCard::OnPaint, this);
    Bind(wxEVT_LEFT_DOWN, &BookCard::OnClick, this);
    title->Bind(wxEVT_LEFT_DOWN, &BookCard::OnClick, this);
    author->Bind(wxEVT_LEFT_DOWN, &BookCard::OnClick, this);
}

void BookCard::OnPaint(wxPaintEvent &event)
{
    wxPaintDC dc(this);
    auto gc = wxGraphicsContext::Create(dc);
    if (gc)
    {
        wxRect rect = GetClientRect();
        rect.Deflate(FromDIP(2));

        const auto roundness = FromDIP(4);

        gc->SetPen(wxPen(book.GetColor()));
        gc->SetBrush(wxBrush(book.GetColor()));

        gc->DrawRoundedRectangle(rect.GetX(), rect.GetY(), rect.GetWidth(), rect.GetHeight(), roundness);

        delete gc;
    }
}

void BookCard::OnClick(wxMouseEvent &event)
{
    state->SetActivity("book preview");
    std::cout << color << "\n";
}