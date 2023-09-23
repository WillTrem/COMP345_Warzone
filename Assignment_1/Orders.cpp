
// PART 3
//
// implement a group of C++ classes that implement a Warzone player orders using the following design:
// orders are created by the player during their turn and placed into the player’s list of orders

// written by Chris Anglin --- 40216346 

#include "Orders.h"
#include <iostream>

using namespace std;

//   ---   Order class   ---   

// default constructor
Order::Order() {}

// copy constructor
Order::Order(Order& existingOrder)
{
    this->effect = existingOrder.effect;
}

//   ---   Deploy class   ---  

// default constructor
Deploy::Deploy() {}

// copy constructor
Deploy::Deploy(Deploy& existingDeploy)
{
    this->effect = existingDeploy.effect;
}

bool Deploy::validate()
{
    cout << "validate() called in Deploy class" << endl;
    return true;
}

void Deploy::execute()
{
    if (this->validate())
    {
        cout << "execute() called in Deploy class" << endl;
        cout << "Deploy effect: " + this->effect;
    }
}

//   ---   Advance class   ---  

// default constructor
Advance::Advance() {}

// copy constructor
Advance::Advance(Advance& existingAdvance)
{
    this->effect = existingAdvance.effect;
}

bool Advance::validate()
{
    cout << "validate() called in Advance class" << endl;
    return true;
}

void Advance::execute()
{
    if (this->validate())
    {
        cout << "execute() called in Advance class" << endl;
        cout << "Advance effect: " + this->effect;
    }
}

//   ---   Bomb class   ---  

// default constructor
Bomb::Bomb() {}

// copy constructor
Bomb::Bomb(Bomb& existingBomb)
{
    this->effect = existingBomb.effect;
}

bool Bomb::validate()
{
    cout << "validate() called in Bomb class" << endl;
    return true;
}

void Bomb::execute()
{
    if (this->validate())
    {
        cout << "execute() called in Bomb class" << endl;
        cout << "Bomb effect: " + this->effect;
    }
}

//   ---   Blockade class   ---  

// default constructor
Blockade::Blockade() {}

// copy constructor
Blockade::Blockade(Blockade& existingBlockade)
{
    this->effect = existingBlockade.effect;
}

bool Blockade::validate()
{
    cout << "validate() called in Blockade class" << endl;
    return true;
}

void Blockade::execute()
{
    if (this->validate())
    {
        cout << "execute() called in Blockade class" << endl;
        cout << "Blockade effect: " + this->effect;
    }
}

//   ---   Airlift class   ---  

// default constructor
Airlift::Airlift() {}

// copy constructor
Airlift::Airlift(Airlift& existingAirlift)
{
    this->effect = existingAirlift.effect;
}

bool Airlift::validate()
{
    cout << "validate() called in Airlift class" << endl;
    return true;
}

void Airlift::execute()
{
    if (this->validate())
    {
        cout << "execute() called in Airlift class" << endl;
        cout << "Airlift effect: " + this->effect;
    }
}

//   ---   Negotiate class   ---  

// default constructor
Negotiate::Negotiate() {}

// copy constructor
Negotiate::Negotiate(Negotiate& existingNegotiate)
{
    this->effect = existingNegotiate.effect;
}

bool Negotiate::validate()
{
    cout << "validate() called in Negotiate class" << endl;
    return true;
}

void Negotiate::execute()
{
    if (this->validate())
    {
        cout << "execute() called in Negotiate class" << endl;
        cout << "Negotiate effect: " + this->effect;
    }
}

//   ---   OrdersList class   ---   

// default constructor
OrdersList::OrdersList() {}

// copy constructor
OrdersList::OrdersList(OrdersList& existingOrdersList)
{
    this->ordersList = existingOrdersList.ordersList;
}

// add an order to the list
void OrdersList::addOrder(Order* order)
{
    ordersList.push(order);
}

// get next order on the list
Order* OrdersList::getNextOrder()
{
    // if list not empty, pop and return next order
    if (!ordersList.empty())
    {   
        Order* nextOrderPtr = ordersList.front(); 
        ordersList.pop();
        return nextOrderPtr;
    }
    else
    {   // if list is empty, print a message
        std::cout << " -- Order list is empty !";
        return nullptr;
    }
}