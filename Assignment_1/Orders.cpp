
// PART 3
//
// implement a group of C++ classes that implement a Warzone player orders using the following design:
// orders are created by the player during their turn and placed into the player’s list of orders

// written by Chris Anglin --- 40216346 

#include "Orders.h"
#include <iostream>

//   ---   Order class   ---   

// default constructor
Order::Order()
{
    // prints when every subclass constructor is called, makes testing too messy :)
    //std::cout << "parent class Order default constructor called" << std:: endl;
}

// copy constructor
Order::Order(const Order& existingOrder)
{
    this->effect = existingOrder.effect;
    
    // prints when every subclass constructor is called, makes testing too messy :)
    //std::cout << "parent class Order copy constructor called" << std:: endl;
}

// validate method
bool Order::validate() {return true;}

// execute method
void Order::execute() {this->executed = true;}

// assignment operator
Order& Order::operator=(const Order& order)
{
    this->effect = order.effect;
    this->executed = order.executed;

    return *this;
}

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
Deploy::Deploy() 
{
    std::cout << "Deploy object created using default constructor" << std:: endl;
}

// copy constructor
Deploy::Deploy(const Deploy& existingDeploy)
{
    this->effect = existingDeploy.effect;
    std::cout << "Deploy object created using copy constructor" << std:: endl;
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

// assignment operator
Deploy& Deploy::operator=(const Deploy& deploy)
{
    this->effect = deploy.effect;
    this->executed = deploy.executed;

    return *this;
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
Advance::Advance()
{
    std::cout << "Advance object created using default constructor" << std:: endl;
}

// copy constructor
Advance::Advance(const Advance& existingAdvance)
{
    this->effect = existingAdvance.effect;
    std::cout << "Advance object created using copy constructor" << std:: endl;
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

// assignment operator
Advance& Advance::operator=(const Advance& advance)
{
    this->effect = advance.effect;
    this->executed = advance.executed;

    return *this;
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
Bomb::Bomb()
{
    std::cout << "Bomb object created using default constructor" << std:: endl;
}

// copy constructor
Bomb::Bomb(const Bomb& existingBomb)
{
    this->effect = existingBomb.effect;
    std::cout << "Bomb object created using copy constructor" << std:: endl;
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

// assignment operator
Bomb& Bomb::operator=(const Bomb& bomb)
{
    this->effect = bomb.effect;
    this->executed = bomb.executed;

    return *this;
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
Blockade::Blockade()
{
    std::cout << "Blockade object created using default constructor" << std:: endl;
}

// copy constructor
Blockade::Blockade(const Blockade& existingBlockade)
{
    this->effect = existingBlockade.effect;
    std::cout << "Blockade object created using copy constructor" << std:: endl;
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

// assignment operator
Blockade& Blockade::operator=(const Blockade& blockade)
{
    this->effect = blockade.effect;
    this->executed = blockade.executed;

    return *this;
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
Airlift::Airlift()
{
    std::cout << "Airlift object created using default constructor" << std:: endl;
}

// copy constructor
Airlift::Airlift(const Airlift& existingAirlift)
{
    this->effect = existingAirlift.effect;
    std::cout << "Airlift object created using copy constructor" << std:: endl;
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

// assignment operator
Airlift& Airlift::operator=(const Airlift& airlift)
{
    this->effect = airlift.effect;
    this->executed = airlift.executed;

    return *this;
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
Negotiate::Negotiate()
{
    std::cout << "Negotiate object created using default constructor" << std:: endl;
}

// copy constructor
Negotiate::Negotiate(const Negotiate& existingNegotiate)
{
    this->effect = existingNegotiate.effect;
    std::cout << "Negotiate object created using copy constructor" << std:: endl;
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

// assignment operator
Negotiate& Negotiate::operator=(const Negotiate& negotiate)
{
    this->effect = negotiate.effect;
    this->executed = negotiate.executed;

    return *this;
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
OrdersList::OrdersList()
{
    std::cout << "OrdersList object created using default constructor" << std:: endl;
}

// copy constructor
OrdersList::OrdersList(const OrdersList& existingOrdersList)
{
    this->ordersList = existingOrdersList.ordersList;
    std::cout << "OrdersList object created using copy constructor" << std:: endl;
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

// move

// remove

// assignment operator
OrdersList& OrdersList::operator=(const OrdersList& orderslist)
{
    this->ordersList = orderslist.ordersList;
    
    return *this;
}

// stream insertion operator overload
std::ostream& operator<<(std::ostream& output, const OrdersList& orderslist)
{   
    // creates a temporary copy of orderlist and traverse it to print it out
    std::queue<Order*> temp = orderslist.ordersList;
    int i = 1;
    while(!temp.empty())
    {   
        std::cout << std::to_string(i) + ": ";
        std::cout << temp.front() << std::endl;
        temp.pop();
        i++;
    }
    std::cout << std::endl;

    return output;
}
