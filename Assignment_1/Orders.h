
// PART 3
//
// implement a group of C++ classes that implement a Warzone player orders using the following design:
// orders are created by the player during their turn and placed into the player’s list of orders

// written by Chris Anglin --- 40216346   :)

#ifndef ORDERS_H
#define ORDERS_H

#include <iostream>
#include <vector>

// an abstract ORDER class --- each ORDER type (below) inherits from this class and overrides execute() and validate()
class Order
{
    public:
    // virtual method to execute order
    virtual void execute();
    // virtual method to validate order
    virtual void validate();
    
    // *** add stream insertion operator ***
};

// ORDER types:

// DEPLOY
class Deploy : public Order
{
    public:
    Deploy();
    void execute() override;
    void validate() override;
};

// ADVANCE
class Advance : public Order
{
    public:
    Advance();
    void execute() override;
    void validate() override;
};

// BOMB
class Bomb : public Order
{
    public:
    Bomb();
    void execute() override;
    void validate() override;
};

// BLOCKADE
class Blockade : public Order
{
    public:
    Blockade();
    void execute() override;
    void validate() override;
};

// AIRLIFT
class Airlift : public Order
{
    public:
    Airlift();
    void execute() override;
    void validate() override;
};

// NEGOTIATE
class Negotiate : public Order
{
    public:
    Negotiate();
    void execute() override;
    void validate() override;
};

// end of ORDER types!


// a class to create and manage a list of ORDERS
class OrdersList
{
    private:
    // a list of pointers to Order objects
    std::vector(Order*) ordersList;

    public:
	//constructor
    OrdersList();
	// method to add an order to the list
	void addOrder(Order* order);
	// get first order on the list
	Order* getNextOrder();
    // delete an order from the list
    void remove();
    // move around an order in the list
    void move();
    
};

#endif
