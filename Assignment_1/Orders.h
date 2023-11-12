
// A1 PART 3
//
// implement a group of C++ classes that implement a Warzone player orders using the following design:
// orders are created by the player during their turn and placed into the player’s list of orders

// A2 PART 4
//
// provide a group of C++ classes that implements the execution of orders following the official rules of the Warzone game

// written by Chris Anglin --- 40216346 

#ifndef ORDERS_H
#define ORDERS_H

#include <iostream>
#include <deque>
#include "Player.h"

//   ---   Order class    ---   [each ORDER type (below) inherits from this class and overrides execute() and validate()]

class Order
{
    private:
    // effect of the Order
    std::string effect = "effect attribute printed from Order object";

    // boolean set true if action object has been executed
    bool executed = false;

    public:
    // default constructor
    Order();

    // copy constructor
    Order(const Order& existingOrder);

    // virtual destructor
    virtual ~Order();

    // pure virtual method to execute order
    virtual void execute() = 0;

    // pure virtual method to validate order
    virtual bool validate() = 0;

    // assignment operator
    Order& operator=(const Order& order);

    // print helper method for stream insertion overload
    virtual void print(std::ostream& output) const;
    
    // stream insertion operator
    friend std::ostream& operator<<(std::ostream& output, const Order& order);
};

// order types:

//   ---   Deploy class   ---

class Deploy : public Order
{   
    private:
    // effect of Deploy
    std::string effect = "effect attribute printed from Deploy object";

    // boolean set true if action object has been executed
    bool executed = false;

    // attributes i need as parameters for Deploy's validate() and execute() methods:
    Player* whichPlayer;
    int howManyUnits;
    Territory* target;

    public:
    // default constructor
    Deploy();

    // copy constructor
    Deploy(const Deploy& existingDeploy);

    // parametered constructor
    Deploy(Player* p, int n, Territory* t);

    // default destructor
    ~Deploy();

    // execute method override
    void execute() override;

    // validate method override
    bool validate() override;

    // assignment operator
    Deploy& operator=(const Deploy& deploy);

    // print helper method for stream insertion overload
    void print(std::ostream& output) const override;

    // stream insertion operator
    friend std::ostream& operator<<(std::ostream& output, const Deploy& deploy);
};

//   ---   Advance class   --- 

class Advance : public Order
{
    private:
    // effect of Advance
    std::string effect = "effect attribute printed from Advance object";

    // boolean set true if action object has been executed
    bool executed = false;

    public:
    // default constructor
    Advance();

    // copy constructor
    Advance(const Advance& existingAdvance);

    // default destructor
    ~Advance();

    // execute method override
    void execute() override;

    // validate method override
    bool validate() override;

    // assignment operator
    Advance& operator=(const Advance& advance);

    // print helper method for stream insertion overload
    void print(std::ostream& output) const override;

    // stream insertion operator
    friend std::ostream& operator<<(std::ostream& output, const Advance& advance);
};

//   ---   Bomb class   --- 

class Bomb : public Order
{
    private:
    // effect of Bomb
    std::string effect = "effect attribute printed from Bomb object";

    // boolean set true if action object has been executed
    bool executed = false;

    public:
    // default constructor
    Bomb();

    // copy constructor
    Bomb(const Bomb& existingBomb);

    // default destructor
    ~Bomb();
    
    // execute method override
    void execute() override;

    // validate method override
    bool validate() override;

    // assignment operator
    Bomb& operator=(const Bomb& bomb);

    // print helper method for stream insertion overload
    void print(std::ostream& output) const override;

    // stream insertion operator
    friend std::ostream& operator<<(std::ostream& output, const Bomb& bomb);
};

//   ---   Blockade class   --- 

class Blockade : public Order
{
    private:
    // effect of Blockade
    std::string effect = "effect attribute printed from Blockade object";

    // boolean set true if action object has been executed
    bool executed = false;

    public:
    // default constructor
    Blockade();

    // copy constructor
    Blockade(const Blockade& existingBlockade);

    // default destructor
    ~Blockade();
    
    // execute method override
    virtual void execute() override;

    // validate method override
    virtual bool validate() override;
    
    // assignment operator
    Blockade& operator=(const Blockade& blockade);

    // print helper method for stream insertion overload
    void print(std::ostream& output) const override;

    // stream insertion operator
    friend std::ostream& operator<<(std::ostream& output, const Blockade& blockade);
};

//   ---   Airlift class  --- 

class Airlift : public Order
{
    private:
    // effect of Airlift
    std::string effect = "effect attribute printed from Airlift object";

    // boolean set true if action object has been executed
    bool executed = false;

    public:
    // default constructor
    Airlift();

    // copy constructor
    Airlift(const Airlift& existingAirlift);

    // default destructor
    ~Airlift();
    
    // execute method override
    void execute() override;

    // validate method override
    bool validate() override;
    
    // assignment operator
    Airlift& operator=(const Airlift& airlift);

    // print helper method for stream insertion overload
    void print(std::ostream& output) const override;

    // stream insertion operator
    friend std::ostream& operator<<(std::ostream& output, const Airlift& airlift);
};

//   ---   Negotiate class  --- 

class Negotiate : public Order
{
    private:
    /// effect of Negotiate
    std::string effect = "effect attribute printed from Negotiate object";

    // boolean set true if action object has been executed
    bool executed = false;

    public:
    // default constructor
    Negotiate();

    // copy constructor
    Negotiate(const Negotiate& existingNegotiate);

    // default destructor
    ~Negotiate();
    
    // execute method override
    void execute() override;

    // validate method override
    bool validate() override;

    // assignment operator
    Negotiate& operator=(const Negotiate& negotiate);

    // print helper method for stream insertion overload
    void print(std::ostream& output) const override;

    // stream insertion operator
    friend std::ostream& operator<<(std::ostream& output, const Negotiate& negotiate);
};

// end of order types!


//   ---   OrdersList class   ---   [a class to create and manage a list of orders]

class OrdersList
{
    private:
    
    // a list of pointers to Order objects
    std::deque<Order*> ordersList;

    public:
    
    // default constructor
    OrdersList();

    // copy constructor
    OrdersList(const OrdersList& existingOrdersList);

    // destructor
    ~OrdersList();
    
    // add an order to the list
    void addOrder(Order* order);
    
    // get next order on the list
    Order* getNextOrder();
    
    // delete an order from the list (use menu number)
    void remove(int num);
    
    // move around an order in the list (use menu numbers)
    void move(int a, int b);

    // assignment operator
    OrdersList& operator=(const OrdersList& ordersList);

    //stream insertion operator
    friend std::ostream& operator<<(std::ostream& output, const OrdersList& ordersList);
};

#endif
