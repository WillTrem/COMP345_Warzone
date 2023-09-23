
// PART 3
//
// implement a group of C++ classes that implement a Warzone player orders using the following design:
// orders are created by the player during their turn and placed into the player’s list of orders

// written by Chris Anglin --- 40216346 

#ifndef ORDERS_H
#define ORDERS_H

#include <iostream>
#include <queue>

//   ---   Order class    ---   [each ORDER type (below) inherits from this class and overrides execute() and validate()]

class Order
{
    private:
    // effect of the Order
    std::string effect = "effect attribute in the Order class";

    public:
    // default constructor
    Order();

    // copy constructor
    Order(Order& existingOrder);

    // pure virtual method to execute order (only implemented in subclasses)
    virtual void execute() = 0;

    // pure virtual method to validate order (only implemented in subclasses)
    virtual bool validate() = 0;
    
    //stream insertion operator
    
};

// order types:

//   ---   Deploy class   ---

class Deploy : public Order
{   
    private:
    // effect of Deploy
    std::string effect = "effect attribute in Deploy order class";

    public:
    // default constructor
    Deploy();

    // copy constructor
    Deploy(Deploy& existingDeploy);

    void execute() override;
    bool validate() override;
};

//   ---   Advance class   --- 

class Advance : public Order
{
    private:
    // effect of Advance
    std::string effect = "effect attribute in Advance order class";

    public:
    // default constructor
    Advance();

    // copy constructor
    Advance(Advance& existingAdvance);

    void execute() override;
    bool validate() override;
};

//   ---   Bomb class   --- 

class Bomb : public Order
{
    private:
    // effect of Bomb
    std::string effect = "effect attribute in Bomb order class";

    public:
    // default constructor
    Bomb();

    // copy constructor
    Bomb(Bomb& existingBomb);
    
    void execute() override;
    bool validate() override;
};

//   ---   Blockade class   --- 

class Blockade : public Order
{
    private:
    // effect of Blockade
    std::string effect = "effect attribute in Blockade order class";

    public:
    // default constructor
    Blockade();

    // copy constructor
    Blockade(Blockade& existingBlockade);
    
    void execute() override;
    bool validate() override;
};

//   ---   Airlift class  --- 

class Airlift : public Order
{
    private:
    // effect of Airlift
    std::string effect = "effect attribute in Airlift order class";

    public:
    // default constructor
    Airlift();

    // copy constructor
    Airlift(Airlift& existingAirlift);
    
    void execute() override;
    bool validate() override;
};

//   ---   Negotiate class  --- 

class Negotiate : public Order
{
    private:
    /// effect of Negotiate
    std::string effect = "effect attribute in Negotiate order class";

    public:
    // default constructor
    Negotiate();

    // copy constructor
    Negotiate(Negotiate& existingNegotiate);
    
    void execute() override;
    bool validate() override;
};

// end of order types!


//   ---   OrdersList class   ---   [a class to create and manage a list of orders]

class OrdersList
{
    private:
    
    // a list of pointers to Order objects
    std::queue<Order*> ordersList;

    public:
    
    // default constructor
    OrdersList();

    // copy constructor
    OrdersList(OrdersList& existingOrdersList);
    
    // add an order to the list
    void addOrder(Order* order);
    
    // get next order on the list
    Order* getNextOrder();
    
    // delete an order from the list
    void remove();
    
    // move around an order in the list
    void move();
};

#endif
