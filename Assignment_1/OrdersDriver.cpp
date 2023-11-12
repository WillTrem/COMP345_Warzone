
// A1 PART 3
//
// implement a group of C++ classes that implement a Warzone player orders using the following design:
// orders are created by the player during their turn and placed into the player’s list of orders

// A2 PART 4
//
// provide a group of C++ classes that implements the execution of orders following the official rules of the Warzone game

// written by Chris Anglin --- 40216346

#include "OrdersDriver.h"

void testOrderExecution()
{
    // i should put code here
}

void testOrdersLists()
{
    // make my testing output look nice
    std::cout << "\n\n ---   PART 3 : testing   --- \n"
              << std::endl;

    // create orders of every kind (including the plain Order object, why not)
    std::cout << "\n -- create orders of every kind :\n"
              << std::endl;
    Deploy deploy_test = Deploy();
    Advance advance_test = Advance();
    Bomb bomb_test = Bomb();
    Blockade blockade_test = Blockade();
    Airlift airlift_test = Airlift();
    Negotiate negotiate_test = Negotiate();

    std::cout << std::endl;

    // create an OrdersList object to hold the orders
    std::cout << " -- create an OrdersList object to hold the orders :\n"
              << std::endl;
    OrdersList orderslist_test = OrdersList();

    std::cout << std::endl;

    // place pointers to all the action objects in the list
    orderslist_test.addOrder(&deploy_test);
    orderslist_test.addOrder(&advance_test);
    orderslist_test.addOrder(&bomb_test);
    orderslist_test.addOrder(&blockade_test);
    orderslist_test.addOrder(&airlift_test);
    orderslist_test.addOrder(&negotiate_test);

    // print out the contents of the orderlist
    std::cout << "\n -- print out the contents of the orderlist :\n"
              << std::endl;
    std::cout << orderslist_test << std::endl;

    // remove blockade order and reprint the orderlist
    std::cout << " -- remove blockade order and reprint the orderlist :\n"
              << std::endl;
    orderslist_test.remove(4);
    std::cout << orderslist_test << std::endl;

    // swap deploy and bomb in the orderlist using move() and reprint it
    std::cout << " -- swap deploy and bomb in the orderlist using move() and reprint it :\n"
              << std::endl;
    orderslist_test.move(3, 1);
    std::cout << orderslist_test << std::endl;

    // execute the first order and reprint the list
    std::cout << " -- execute the first order and reprint the list :\n"
              << std::endl;
    Order *nextOrder = orderslist_test.getNextOrder();
    nextOrder->execute();
    std::cout << std::endl
              << orderslist_test << std::endl;

    std::cout << " ---   PART 3: testing done :)   ---\n\n"
              << std::endl;
}