
// PART 3
//
// implement a group of C++ classes that implement a Warzone player orders using the following design:
// orders are created by the player during their turn and placed into the player’s list of orders

// written by Chris Anglin --- 40216346 

#include "Orders.h"
#include "OrdersDriver.h"

void testOrdersLists()
{
    // make my testing output look nice
    std::cout << "\n\n ---   PART 3: testing   --- \n" << std::endl;

    // create orders of every kind (including the plain Order object, why not)
    std::cout << "// create orders of every kind:" << std::endl;
    Order order_test = Order();
    Deploy deploy_test = Deploy();
    Advance advance_test = Advance();
    Bomb bomb_test = Bomb();
    Blockade blockade_test = Blockade();
    Airlift airlift_test = Airlift();
    Negotiate negotiate_test = Negotiate();

    std::cout << std::endl;

    // create an OrdersList object to hold the orders
    std::cout << "// create an OrdersList object to hold the orders:" << std::endl;
    OrdersList ordersList_test = OrdersList();

    std::cout << std::endl;

    // place pointers to all the action objects in the list
    ordersList_test.addOrder(&order_test);
    ordersList_test.addOrder(&deploy_test);
    ordersList_test.addOrder(&advance_test);
    ordersList_test.addOrder(&bomb_test);
    ordersList_test.addOrder(&blockade_test);
    ordersList_test.addOrder(&airlift_test);
    ordersList_test.addOrder(&negotiate_test);

    std::cout << " ---   PART 3: testing done :)   ---\n\n" << std::endl;
}