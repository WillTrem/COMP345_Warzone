#pragma once

#include "Player.h"
#include "Map.h"
#include "Cards.h"
#include "LogObserver.h"

#include <map>
#include <string>
#include <iostream>
#include <memory>

using namespace std;

// ********** OBSERVER ********** //
Observer::Observer() {}
Observer::~Observer() {}
void Observer::Update()
{
    // Provide the implementation for the pure virtual function
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
        (*i)->Update();
};

// ********** SUBJECT ********** //

// ********** ILOGGABLE ********** //
ILoggable::~ILoggable() = default;

std::string ILoggable::stringToLog()
{
    return "Default log string";
}
// ********** ILOGGABLE ********** //
