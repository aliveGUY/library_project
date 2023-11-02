#pragma once

#include <string>

using namespace std;

class Book
{
public:
    Book(const string &title, const string &author, const wxColor &color)
        : title(title), author(author), color(color) {}

    string GetTitle()
    {
        return title;
    }

    string GetAuthor()
    {
        return author;
    }

    wxColor GetColor()
    {
        return color;
    }

private:
    string title;
    string author;
    wxColor color;
};
