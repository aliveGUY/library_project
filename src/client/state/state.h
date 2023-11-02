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
    ClientLogin
};

class State : public olc::net::client_interface<CustomMsgTypes>
{
public:
    State();
    void SetActivity(string activity);
    void SetActivity(string activity, Book *book);
    void RegisterObserver(Observer *o);
    void OnLogin();

public:
    string GetActivity();
    std::vector<Book> GetData();
    Book *GetSelectedBook();

private:
    void OnPing(wxCommandEvent &event);
    void MessageAll(wxCommandEvent &event);
    void CheckForMessages(wxTimerEvent &event);

public:
    bool bookIsSelected = false;

private:
    Observer *observer;
    string currentActivity;
    std::vector<Book> currentData;

    Book *selectedBook;

    wxTimer messageTimer;
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

    messageTimer.Bind(wxEVT_TIMER, &State::CheckForMessages, this);
    messageTimer.Start(1000);
}

void State::SetActivity(string activity)
{
    currentActivity = activity;
    observer->UpdateActivity(currentActivity);
}

void State::SetActivity(string activity, Book *book)
{
    currentActivity = activity;
    selectedBook = book;
    bookIsSelected = true;
    observer->UpdateActivity(currentActivity);
}

Book *State::GetSelectedBook()
{
    return selectedBook;
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

void State::OnLogin()
{
    olc::net::message<CustomMsgTypes> msg;
    msg.header.id = CustomMsgTypes::ClientLogin;

    string body = "username: admin\npassword: admin";

    msg << body;
    Send(msg);
}

void State::OnPing(wxCommandEvent &event)
{
    olc::net::message<CustomMsgTypes> msg;
    msg.header.id = CustomMsgTypes::ServerPing;

    // Caution with this...
    std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();

    msg << timeNow;
    Send(msg);
}

void State::MessageAll(wxCommandEvent &event)
{
    olc::net::message<CustomMsgTypes> msg;
    msg.header.id = CustomMsgTypes::MessageAll;
    Send(msg);
}

void State::CheckForMessages(wxTimerEvent &event)
{
    while (IsConnected() && !Incoming().empty())
    {
        auto msg = Incoming().pop_front().msg;
        switch (msg.header.id)
        {
        case CustomMsgTypes::ClientLogin:
        {
            std::cout << "Logged in\n";
            SetActivity("dashboard");
        }
        break;

        case CustomMsgTypes::ServerAccept:
        {
            // Server has responded to a ping request
            std::cout << "Server Accepted Connection\n";
        }
        break;

        case CustomMsgTypes::ServerPing:
        {
            // Server has responded to a ping request
            std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();
            std::chrono::system_clock::time_point timeThen;
            msg >> timeThen;
            std::cout << "Ping: " << std::chrono::duration<double>(timeNow - timeThen).count() << "\n";
        }
        break;

        case CustomMsgTypes::ServerMessage:
        {
            // Server has responded to a ping request
            uint32_t clientID;
            msg >> clientID;
            std::cout << "Hello from [" << clientID << "]\n";
        }
        break;
        }
    }
}