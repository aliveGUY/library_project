#pragma once
#include "../../bridge/olc_net.h"

#include <iostream>

#include <vector>
#include <string>

#include "../components/book.h"
#include "observer.h"

using namespace std;

enum class CustomMsgTypes : uint32_t
{
    ServerAccept,
    ServerDeny,
    ServerPing,
    MessageAll,
    ServerMessage,
};

class State : public olc::net::client_interface<CustomMsgTypes>
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
    currentData = {
        Book("Gone with the Wind", "Margaret Mitchell", wxColor("#fd7f6f")),
        Book("Jane Eyre", "Charlotte Bronte", wxColor("#7eb0d5")),
        Book("Pride and Prejudice", "Jane Austen", wxColor("#b2e061")),
        Book("To Kill a Mockingbird", "Harper Lee", wxColor("#bd7ebe")),
        Book("The Hobbit (The Lord of the Rings, #0)", "J.R.R. Tolkien", wxColor("#ffb55a")),
        Book("Wuthering Heights", "Emily Bronte", wxColor("#ffee65")),
        Book("Little Women", "Louisa May Alcott", wxColor("#beb9db")),
        Book("A Tale of Two Cities", "Charles Dickens", wxColor("#fdcce5")),
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