#pragma once

#include "Player.h"
#include "Map.h"
#include "Cards.h"

#include <map>
#include <string>
#include <iostream>
#include <memory>
#include <list>

using namespace std;

class Observer
{
public:
    Observer();
    ~Observer();
    void Update();
};

class Subject
{
public:
    virtual void Attach(Observer *o);
    virtual void Detach(Observer *o);
    virtual void Notify(const ILoggable &i);
    Subject();
    ~Subject();

private:
    list<Observer *> *_observers;
};

class ILoggable
{
public:
    virtual ~ILoggable();
    virtual std::string stringToLog();
};
