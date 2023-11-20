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
    // Destructor
    virtual ~ILoggable();
    // Base stringToLog method
    virtual std::string stringToLog() const = 0;
};

class Observer
{
public:
    // Default Constructor
    Observer();
    // Destructor
    ~Observer();
    // Base Update function
    virtual void Update(const ILoggable &loggable) = 0;
};

class Subject
{
public:
    // Attach function
    virtual void Attach(Observer *o);
    // Detach function
    virtual void Detach(Observer *o);
    // Base Notify function
    virtual void Notify(const ILoggable &i);
    // Default Constructor
    Subject();
    // Destructor
    ~Subject();

private:
    list<Observer *> *_observers;
};

class LogObserver : public Observer
{
public:
    // Override Update function
    void Update(const ILoggable &loggable) override;
};
