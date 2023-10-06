
// PART 3
//
// implement a group of C++ classes that implement a Warzone player orders using the following design:
// orders are created by the player during their turn and placed into the player’s list of orders

// written by Chris Anglin --- 40216346 

#include "Orders.h"
#include "OrdersDriver.h"

void testOrdersLists()
{
    // create orders of every kind (including the plain Order object, why not)
    Order order_test = Order();
    Deploy deploy_test = Deploy();
    Advance advance_test = Advance();
    Bomb bomb_test = Bomb();
    Blockade blockade_test = Blockade();
    Airlift airlift_test = Airlift();
    Negotiate negotiate_test = Negotiate();

    // create an OrdersList object
    OrdersList ordersList_test = OrdersList();

    // place pointers to all the action objects in the list
    ordersList_test.addOrder(&order_test);
    ordersList_test.addOrder(&deploy_test);
    ordersList_test.addOrder(&advance_test);
    ordersList_test.addOrder(&bomb_test);
    ordersList_test.addOrder(&blockade_test);
    ordersList_test.addOrder(&airlift_test);
    ordersList_test.addOrder(&negotiate_test);

    std::cout << "all good" << std::endl;
}