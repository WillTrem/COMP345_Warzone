
// PART 3
//
// implement a group of C++ classes that implement a Warzone player orders using the following design:
// orders are created by the player during their turn and placed into the player’s list of orders

// written by Chris Anglin --- 40216346 

#include "Orders.h"
#include <iostream>

//   ---   Order class   ---   

// default constructor
Order::Order() {}

// copy constructor
Order::Order(const Order& existingOrder)
{
    this->effect = existingOrder.effect;
}

// validate method
bool Order::validate() {return true;}

// execute method
void Order::execute() {this->executed = true;}

// stream insertion operator overload
std::ostream& operator<<(std::ostream& output, const Order& order)
{   
    output << " << operator printed an Order object" << std::endl;
    if (order.executed)
    {
        output << order.effect << std::endl;
    }
    return output;
}

//   ---   Deploy class   ---  

// default constructor
Deploy::Deploy() {}

// copy constructor
Deploy::Deploy(const Deploy& existingDeploy)
{
    this->effect = existingDeploy.effect;
}

bool Deploy::validate()
{
    std::cout << "validate() called in Deploy class" << std::endl;
    return true;
}

void Deploy::execute()
{
    if (this->validate())
    {
        std::cout << "execute() called in Deploy class" << std::endl;
        this->executed = true;
    }
}

// stream insertion operator overload
std::ostream& operator<<(std::ostream& output, const Deploy& deploy)
{   
    output << " << operator printed a Deploy object" << std::endl;
    if (deploy.executed)
    {
        output << deploy.effect << std::endl;
    }
    return output;
}

//   ---   Advance class   ---  

// default constructor
Advance::Advance() {}

// copy constructor
Advance::Advance(const Advance& existingAdvance)
{
    this->effect = existingAdvance.effect;
}

bool Advance::validate()
{
    std::cout << "validate() called in Advance class" << std::endl;
    return true;
}

void Advance::execute()
{
    if (this->validate())
    {
        std::cout << "execute() called in Advance class" << std::endl;
        this->executed = true;
    }
}

// stream insertion operator overload
std::ostream& operator<<(std::ostream& output, const Advance& advance)
{   
    output << " << operator printed an Advance object" << std::endl;
    if (advance.executed)
    {
        output << advance.effect << std::endl;
    }
    return output;
}

//   ---   Bomb class   ---  

// default constructor
Bomb::Bomb() {}

// copy constructor
Bomb::Bomb(const Bomb& existingBomb)
{
    this->effect = existingBomb.effect;
}

bool Bomb::validate()
{
    std::cout << "validate() called in Bomb class" << std::endl;
    return true;
}

void Bomb::execute()
{
    if (this->validate())
    {
        std::cout << "execute() called in Bomb class" << std::endl;
        this->executed = true;
    }
}

// stream insertion operator overload
std::ostream& operator<<(std::ostream& output, const Bomb& bomb)
{   
    output << " << operator printed a Bomb object" << std::endl;
    if (bomb.executed)
    {
        output << bomb.effect << std::endl;
    }
    return output;
}

//   ---   Blockade class   ---  

// default constructor
Blockade::Blockade() {}

// copy constructor
Blockade::Blockade(const Blockade& existingBlockade)
{
    this->effect = existingBlockade.effect;
}

bool Blockade::validate()
{
    std::cout << "validate() called in Blockade class" << std::endl;
    return true;
}

void Blockade::execute()
{
    if (this->validate())
    {
        std::cout << "execute() called in Blockade class" << std::endl;
        this->executed = true;
    }
}

// stream insertion operator overload
std::ostream& operator<<(std::ostream& output, const Blockade& blockade)
{   
    output << " << operator printed a Blockade object" << std::endl;
    if (blockade.executed)
    {
        output << blockade.effect << std::endl;
    }
    return output;
}

//   ---   Airlift class   ---  

// default constructor
Airlift::Airlift() {}

// copy constructor
Airlift::Airlift(const Airlift& existingAirlift)
{
    this->effect = existingAirlift.effect;
}

bool Airlift::validate()
{
    std::cout << "validate() called in Airlift class" << std::endl;
    return true;
}

void Airlift::execute()
{
    if (this->validate())
    {
        std::cout << "execute() called in Airlift class" << std::endl;
        this->executed = true;
    }
}

// stream insertion operator overload
std::ostream& operator<<(std::ostream& output, const Airlift& airlift)
{   
    output << " << operator printed an Airlift object" << std::endl;
    if (airlift.executed)
    {
        output << airlift.effect << std::endl;
    }
    return output;
}

//   ---   Negotiate class   ---  

// default constructor
Negotiate::Negotiate() {}

// copy constructor
Negotiate::Negotiate(const Negotiate& existingNegotiate)
{
    this->effect = existingNegotiate.effect;
}

bool Negotiate::validate()
{
    std::cout << "validate() called in Negotiate class" << std::endl;
    return true;
}

void Negotiate::execute()
{
    if (this->validate())
    {
        std::cout << "execute() called in Negotiate class" << std::endl;
        this->executed = true;
    }
}

// stream insertion operator overload
std::ostream& operator<<(std::ostream& output, const Negotiate& negotiate)
{   
    output << " << operator printed a Negotiate object" << std::endl;
    if (negotiate.executed)
    {
        output << negotiate.effect << std::endl;
    }
    return output;
}

//   ---   OrdersList class   ---   

// default constructor
OrdersList::OrdersList() {}

// copy constructor
OrdersList::OrdersList(const OrdersList& existingOrdersList)
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
        std::cout << " -- Order list is empty !" << std::endl;
        return nullptr;
    }
}

// stream insertion operator overload
std::ostream& operator<<(std::ostream& output, const OrdersList& orderslist)
{   
    output << " << operator printed an OrdersList object" << std::endl;
    return output;
}
