
// PART 3
//
// implement a group of C++ classes that implement a Warzone player orders using the following design:
// orders are created by the player during their turn and placed into the player’s list of orders

// written by Chris Anglin --- 40216346 

#include "Orders.h"

//   ---   Order   ---   

// default constructor
Order::Order() {}

// copy constructor
Order::Order(Order& existingOrder)
{
    this->effect = existingOrder.effect;
}

//   ---   Deploy   ---  

// default constructor
Deploy::Deploy() {}

// copy constructor
Deploy::Deploy(Deploy& existingDeploy)
{
    this->effect = existingDeploy.effect;
}

void Deploy::validate()
{

}

void Deploy::execute()
{
    this->validate();
}

//   ---   Advance   ---  

// default constructor
Advance::Advance() {}

// copy constructor
Advance::Advance(Advance& existingAdvance)
{
    this->effect = existingAdvance.effect;
}

void Deploy::validate()
{

}

void Deploy::execute()
{
    this->validate();
}

//   ---   Bomb   ---  

// default constructor
Bomb::Bomb() {}

// copy constructor
Bomb::Bomb(Bomb& existingBomb)
{
    this->effect = existingBomb.effect;
}

void Bomb::validate()
{

}

void Bomb::execute()
{
    this->validate();
}

//   ---   Blockade   ---  

// default constructor
Blockade::Blockade() {}

// copy constructor
Blockade::Blockade(Blockade& existingBlockade)
{
    this->effect = existingBlockade.effect;
}

void Blockade::validate()
{

}

void Blockade::execute()
{
    this->validate();
}

//   ---   Airlift   ---  

// default constructor
Airlift::Airlift() {}

// copy constructor
Airlift::Airlift(Airlift& existingAirlift)
{
    this->effect = existingAirlift.effect;
}

void Airlift::validate()
{

}

void Airlift::execute()
{
    this->validate();
}

//   ---   Negotiate   ---  

// default constructor
Negotiate::Negotiate() {}

// copy constructor
Negotiate::Negotiate(Negotiate& existingNegotiate)
{
    this->effect = existingNegotiate.effect;
}

void Negotiate::validate()
{

}

void Negotiate::execute()
{
    this->validate();
}

//   ---   OrdersList   ---   

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