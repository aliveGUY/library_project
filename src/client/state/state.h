#pragma once

#include <iostream>

#include <vector>
#include <string>

#include "../components/book.h"
#include "observer.h"

using namespace std;

class State
{
public:
    State();
    string GetActivity();
    std::vector<Book> GetData();
    void SetActivity(string activity);
    void RegisterObserver(Observer *o);

private:
    Observer *observer;
    string currentActivity;
    std::vector<Book> currentData;
};

State::State()
{
    currentActivity = "login";

    currentData = {
        Book("Stock price Prediction a referential approach on how to", "Andrzej Sapkowski", wxColor("#fd7f6f")),
        Book("Stock price Prediction a referential approach on how to", "Andrzej Sapkowski", wxColor("#7eb0d5")),
        Book("Stock price Prediction a referential approach on how to", "Andrzej Sapkowski", wxColor("#b2e061")),
        Book("Stock price Prediction a referential approach on how to", "Andrzej Sapkowski", wxColor("#bd7ebe")),
        Book("Stock price Prediction a referential approach on how to", "Andrzej Sapkowski", wxColor("#ffb55a")),
        Book("Stock price Prediction a referential approach on how to", "Andrzej Sapkowski", wxColor("#ffee65")),
        Book("Stock price Prediction a referential approach on how to", "Andrzej Sapkowski", wxColor("#beb9db")),
        Book("Stock price Prediction a referential approach on how to", "Andrzej Sapkowski", wxColor("#fdcce5")),
        Book("Stock price Prediction a referential approach on how to", "Andrzej Sapkowski", wxColor("#8bd3c7")),
    };
}

std::vector<Book> State::GetData()
{
    return currentData;
}

string State::GetActivity()
{
    return currentActivity;
}

void State::RegisterObserver(Observer *o)
{
    observer = o;
}

void State::SetActivity(string activity)
{
    currentActivity = activity;
    observer->UpdateActivity(currentActivity);
}