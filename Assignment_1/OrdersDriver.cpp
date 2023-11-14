
// A1 PART 3
//
// implement a group of C++ classes that implement a Warzone player orders using the following design:
// orders are created by the player during their turn and placed into the player’s list of orders

// A2 PART 4
//
// provide a group of C++ classes that implements the execution of orders following the official rules of the Warzone game

// written by Chris Anglin --- 40216346

#include "OrdersDriver.h"
class TestWorld{

    public:
    Player* p1;
    Player* p2;
    Territory* t1;
    Territory* t2;
    Territory* t3;
    std::vector<Territory*> t1_neighbours;
    std::vector<Territory*> t2_neighbours;

    // 'simulation' game state for testing the Order types
    TestWorld(Player& a, Player& b, Territory& c, Territory& d, Territory& e)
    {   
        // make test players and set them up
        p1 = &a;
        p2 = &b;
        p1->setReinforcementPool(2);
        // make test territories
        t1 = &c;
        t2 = &d;
        t3 = &e;
        // give territories armies
        t1->setTerritoryNumberOfArmies(6);
        t2->setTerritoryNumberOfArmies(2);
        t3->setTerritoryNumberOfArmies(2);
        // set territory names
        t1->setTerritoryName("territory1");
        t2->setTerritoryName("territory2");
        t3->setTerritoryName("territory3");
        // set up neighbours (t1 and t2 are neighbours)
        t1_neighbours = {t2};
        t2_neighbours = {t1};
        t1->setNeighboringTerritories(t1_neighbours);
        t2->setNeighboringTerritories(t2_neighbours);
        // set up territory ownership
        t1->setOccupierName(p1->getPlayerName());
        t2->setOccupierName(p2->getPlayerName());
        p1->addOwnedTerritory(t1);
        p2->addOwnedTerritory(t2);
    }
};

// implementation of A2's testing function
void testOrderExecution()
{   
    // create players and territories
    Player play1 = Player();
    Player play2 = Player();
    Territory territory1 = Territory();
    Territory territory2 = Territory();
    Territory territory3 = Territory();

    // demo Deploy
    std::cout << " \n\n***** DEPLOY *****:\n";
    TestWorld world = TestWorld(play1, play2, territory1, territory2, territory3);

    Deploy deploy_invalid1 = Deploy(world.p1, 4, world.t1); // too many armies
    Deploy deploy_invalid2 = Deploy(world.p1, 2, world.t2); // don't own territory
    Deploy deploy_valid = Deploy(world.p1, 2, world.t1);
    deploy_invalid1.execute();
    deploy_invalid2.execute();
    deploy_valid.execute();

    // demo Advance
    std::cout << " \n\n***** ADVANCE *****:\n";
    world = TestWorld(play1, play2, territory1, territory2, territory3);
    
    Advance advance_invalid1 = Advance(world.p1, 7, world.t1, world.t2); // too many armies
    Advance advance_invalid2 = Advance(world.p1, 4, world.t1, world.t3); // target belongs to no one
    Advance advance_valid = Advance(world.p1, 6, world.t1, world.t2);
    advance_invalid1.execute();
    advance_invalid2.execute();
    advance_valid.execute();

    // demo Bomb
    std::cout << " \n\n***** BOMB *****:\n";
    world = TestWorld(play1, play2, territory1, territory2, territory3);

    Bomb bomb_invalid1 = Bomb(world.p1, world.t3); // enemy doesn't own territory
    Bomb bomb_valid = Bomb(world.p1, world.t2);
    bomb_invalid1.execute();
    bomb_valid.execute();

    // demo Blockade
    std::cout << " \n\n***** BLOCKADE *****:\n";
    world = TestWorld(play1, play2, territory1, territory2, territory3);

    Blockade blockade_invalid = Blockade(world.p1, world.t2); // not owned by self
    Blockade blockade_valid = Blockade(world.p1, world.t1);
    blockade_invalid.execute();
    blockade_valid.execute();

    // demo Airlift
    std::cout << " \n\n***** Airlift *****:\n";
    world = TestWorld(play1, play2, territory1, territory2, territory3);

    Airlift airlift_invalid = Airlift(world.p1, 3, world.t1, world.t2); // self doesn't own target
    airlift_invalid.execute();
    Advance advance = Advance(world.p1, 5, world.t1, world.t2); // capture t2 and try again
    advance.execute();
    Airlift airlift_valid = Airlift(world.p1, 1, world.t1, world.t2); 
    airlift_valid.execute();

    // demo Negotiate
    std::cout << " \n\n***** Negotiate *****:\n";
    world = TestWorld(play1, play2, territory1, territory2, territory3);

    Negotiate negotiate_valid = Negotiate(world.p1, world.t2);
    Advance advance_ = Advance(world.p1, 4, world.t1, world.t2); // should be blocked from attacking now!
    negotiate_valid.execute();
    advance_.execute();

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