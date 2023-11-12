#pragma once

#include "Player.h"
#include "Map.h"
#include "Cards.h"
#include "LogObserver.h"

#include <map>
#include <string>
#include <iostream>
#include <memory>
#include <fstream>

using namespace std;

// ********** OBSERVER ********** //
Observer::Observer()
{
}
Observer::~Observer()
{
}
// ********** OBSERVER ********** //

// ********** SUBJECT ********** //
Subject::Subject()
{
    _observers = new list<Observer *>;
}
Subject::~Subject()
{
    delete _observers;
}
void Subject::Attach(Observer *o)
{
    _observers->push_back(o);
};
void Subject::Detach(Observer *o)
{
    _observers->remove(o);
};
void Subject::Notify(const ILoggable &loggable)
{
    list<Observer *>::iterator i = _observers->begin();
    for (; i != _observers->end(); ++i)
        (*i)->Update(loggable);
};

// ********** SUBJECT ********** //

// ********** ILOGGABLE ********** //
ILoggable::~ILoggable() = default;

std::string ILoggable::stringToLog() const
{
    return "Default log string";
}
// ********** ILOGGABLE ********** //

// ********** LOGOBSERVER ********** //

void LogObserver::Update(const ILoggable &loggable)
{
    // Open the file in append mode
    std::ofstream file("GameLog.txt", std::ios::app);

    if (file.is_open())
    {
        // Write the log entry to the file
        file << "Logging to GameLog.txt: " << loggable.stringToLog() << std::endl;

        // Close the file
        file.close();
    }
    else
    {
        // Handle the case where the file couldn't be opened
        std::cerr << "Unable to open GameLog.txt for writing." << std::endl;
    }
}
// ********** LOGOBSERVER ********** //
