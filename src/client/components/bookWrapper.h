#pragma once
#include <string>
#include <vector>

#include "book.h"
#include "bookCard.h"
#include "../state/state.h"

wxPanel *BookWrapper(wxWindow *parent, std::vector<Book> booksData, State *state)
{
    auto controlsPanel = new wxScrolled<wxPanel>(parent, wxID_ANY);
    controlsPanel->SetScrollRate(0, 10);

    auto mainSizer = new wxBoxSizer(wxVERTICAL);

    auto text = new wxStaticText(controlsPanel, wxID_ANY, "Colors");
    mainSizer->Add(text, 0, wxALL, 5);

    auto colorPaneSizer = new wxWrapSizer(wxHORIZONTAL);
    for (auto &book : booksData)
    {
        auto colorPane = new BookCard(controlsPanel, state, wxID_ANY, book);
        colorPaneSizer->Add(colorPane, 0, wxRIGHT | wxBOTTOM, 5);
    }

    mainSizer->Add(colorPaneSizer, 0, wxALL, 5);

    mainSizer->AddStretchSpacer();
    mainSizer->AddSpacer(5);

    controlsPanel->SetSizer(mainSizer);

    return controlsPanel;
}
