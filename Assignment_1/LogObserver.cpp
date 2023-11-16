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
// Default Constructor
Observer::Observer()
{
}
// Destructor
Observer::~Observer()
{
}
// ********** OBSERVER ********** //

// ********** SUBJECT ********** //
// Default Constructor
Subject::Subject()
{
    _observers = new list<Observer *>;
}
// Destructor
Subject::~Subject()
{
    delete _observers;
}
// Attach function
void Subject::Attach(Observer *o)
{
    _observers->push_back(o);
};
// Detach function
void Subject::Detach(Observer *o)
{
    _observers->remove(o);
};
// Notify ILoggable
void Subject::Notify(const ILoggable &loggable)
{
    std::cout << "Notify() inside Subject reached" << endl;
    list<Observer *>::iterator i = _observers->begin();
    for (; i != _observers->end(); ++i)
        (*i)->Update(loggable);
};

// ********** SUBJECT ********** //

// ********** ILOGGABLE ********** //
// Destructor
ILoggable::~ILoggable() = default;

std::string ILoggable::stringToLog() const
{
    return "Default log string";
}
// ********** ILOGGABLE ********** //

// ********** LOGOBSERVER ********** //
// Update function
void LogObserver::Update(const ILoggable &loggable)
{
    std::cout << "LogObserver received an update: " << loggable.stringToLog() << std::endl;

    std::ofstream file("/Users/zhzha/Desktop/COMP345_Warzone/Assignment_1/GameLog.txt", std::ios::app);
    // std::ofstream file("Assignment_1/GameLog.txt", std::ios::app);
    // std::ofstream file("GameLog.txt", std::ios::app);

    if (file.is_open())
    {
        // Write the log entry to the file
        file << "------------------------------------ NEW LOG ---------------------------------" << std::endl;
        file << loggable.stringToLog() << std::endl;
        file << std::endl
             << std::endl;
        // Close the file
        file.flush();
        file.close();
    }
    else
    {
        std::cerr << "Unable to open GameLog.txt for writing. Error code: " << errno << std::endl;
    }
}

// ********** LOGOBSERVER ********** //
