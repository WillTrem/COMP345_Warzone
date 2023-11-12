#pragma once

#include <map>
#include <string>
#include <iostream>
#include <memory>
#include <list>

using namespace std;

class ILoggable
{
public:
    virtual ~ILoggable();
    virtual std::string stringToLog() const = 0;
};

class Observer
{
public:
    Observer();
    ~Observer();
    virtual void Update(const ILoggable &loggable) = 0;
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

class LogObserver : public Observer
{
public:
    void Update(const ILoggable &loggable) override;
};
