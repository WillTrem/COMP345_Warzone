
// A1 PART 3
//
// implement a group of C++ classes that implement a Warzone player orders using the following design:
// orders are created by the player during their turn and placed into the player’s list of orders

// A2 PART 4
//
// provide a group of C++ classes that implements the execution of orders following the official rules of the Warzone game

// written by Chris Anglin --- 40216346

// TO-DO: add logic so player gets a card at end of turn if capturedTerritoryThisTurn is true
//      : make sure airlift can only be called by player with airlift card

#include <iostream>
#include <string>
#include <cstdlib>

#include "Orders.h"

//   ---   Order class   ---

// default constructor
Order::Order()
{
    std::cout << "parent class Order default constructor called" << std::endl;
}

// copy constructor
Order::Order(const Order &existingOrder)
{
    this->effect = existingOrder.effect;
    std::cout << "parent class Order copy constructor called" << std::endl;
}

// virtual destructor
Order::~Order() {}

// validate method
bool Order::validate() { return true; }

// execute method
void Order::execute()
{
    this->executed = true;
}

string Order::stringToLog() const
{
    const char *className = typeid(*this).name();
    return "Order Log: Order was executed. Type of Order: " + std::string(className) + " - " + this->effect;
}

// assignment operator
Order &Order::operator=(const Order &order)
{
    this->effect = order.effect;
    this->executed = order.executed;

    return *this;
}

// print helper method for stream insertion operator overload
void Order::print(std::ostream &output) const
{
    output << "Order" << std::endl;
}

// stream insertion operator overload
std::ostream &operator<<(std::ostream &output, const Order &order)
{
    order.print(output);
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
    std::cout << "Deploy object created using default constructor\n"
              << std::endl;
}

// copy constructor
Deploy::Deploy(const Deploy &existingDeploy)
{
    this->effect = existingDeploy.effect;
    std::cout << "Deploy object created using copy constructor" << std::endl;
}

// parameterized constructor
Deploy::Deploy(Player *p, int n, Territory *t)
{
    this->whichPlayer = p;
    this->howManyUnits = n;
    this->target = t;
}

// destructor
Deploy::~Deploy() {}

// validate method override
bool Deploy::validate()
{
    std::cout << "validate() called in a Deploy object" << std::endl;

    // if the target territory doesn't belong to player who made the Deploy order, not valid
    if (this->whichPlayer->getPlayerName() != this->target->occupierName)
    {
        return false;
    }

    // if the number of armies is more than the player has in the reinforcement pool, not valid
    if (this->howManyUnits > this->whichPlayer->getReinforcmentPool())
    {
        return false;
    }

    return true;
}

// execute method override
void Deploy::execute()
{

    if (this->validate())
    {
        // subtract units from player's reinforcement pool
        this->whichPlayer->setReinforcementPool(this->whichPlayer->getReinforcmentPool() - this->howManyUnits);

        // add units to the target territory
        this->target->setTerritoryNumberOfArmies(this->target->numOfArmies + this->howManyUnits);
        this->effect = this->whichPlayer->getPlayerName() + " deployed " + std::to_string(this->howManyUnits) + " to " + this->target->territoryName;
    }
    else
    {
        this->effect = this->whichPlayer->getPlayerName() + "'s Deploy was not valid..";
    }

    this->executed = true; // should this only happen if valid? or both so it can be removed? (double check)
    std::cout << "execute() called in a Deploy object" << std::endl;
    std::cout << this->effect << std::endl;

    Notify(*this);
}

// assignment operator
Deploy &Deploy::operator=(const Deploy &deploy)
{
    this->effect = deploy.effect;
    this->executed = deploy.executed;

    return *this;
}

// print helper method for stream insertion overload
void Deploy::print(std::ostream &output) const
{
    output << "Deploy" << std::endl;
}

// stream insertion operator overload
std::ostream &operator<<(std::ostream &output, const Deploy &deploy)
{
    deploy.print(output);
    if (deploy.executed)
    {
        output << deploy.effect << std::endl;
    }
    return output;
}

// Getters
Player *Deploy::getWhichPlayer() const
{
    return whichPlayer;
}

int Deploy::getHowManyUnits() const
{
    return howManyUnits;
}

Territory *Deploy::getTarget() const
{
    return target;
}

// Setters
void Deploy::setWhichPlayer(Player *player)
{
    whichPlayer = player;
}

void Deploy::setHowManyUnits(int units)
{
    howManyUnits = units;
}

void Deploy::setTarget(Territory *territory)
{
    target = territory;
}

//   ---   Advance class   ---

// default constructor
Advance::Advance()
{
    std::cout << "Advance object created using default constructor\n"
              << std::endl;
}

// copy constructor
Advance::Advance(const Advance &existingAdvance)
{
    this->effect = existingAdvance.effect;
    std::cout << "Advance object created using copy constructor" << std::endl;
}

// parameterized constructor
Advance::Advance(Player *p, int n, Territory *s, Territory *t)
{
    this->whichPlayer = p;
    this->howManyUnits = n;
    this->source = s;
    this->target = t;
}

// destructor
Advance::~Advance() {}

// validate method override
bool Advance::validate()
{
    std::cout << "validate() called in an Advance object" << std::endl;

    // not valid if source doesn't belong to player
    if (this->source->occupierName != this->whichPlayer->getPlayerName())
    {
        return false;
    }

    // not valid if number of units is more than available at source
    if (this->howManyUnits > this->source->numOfArmies)
    {
        return false;
    }

    // not valid if target not adjacent to source
    if (this->source->isAdjacent(this->target) == false)
    {
        return false;
    }

    return true;
}

// execute method override   [!!! finish implementing this]
void Advance::execute()
{
    if (this->validate())
    {
        // if target is friendly move units to defend
        if (this->source->occupierName == this->target->occupierName)
        {
            this->source->setTerritoryNumberOfArmies(this->source->numOfArmies - this->howManyUnits);
            this->target->setTerritoryNumberOfArmies(this->target->numOfArmies + this->howManyUnits);
            this->effect = this->whichPlayer->getPlayerName() + " advanced " + std::to_string(this->howManyUnits) + " units from " + this->source->territoryName + " to " + this->target->territoryName;
        }
        // otherwise attack
        else
        {
            int attackerCount = this->howManyUnits;
            int defenderCount = this->target->numOfArmies;

            // attacker goes first
            for (int i = 0; i < attackerCount; i++)
            {
                if ((rand() % 11) >= 4) // 60% success rate
                {
                    defenderCount--;
                }
            }

            // then defender strikes back
            for (int i = 0; i < defenderCount; i++)
            {
                if ((rand() % 11) >= 3) // 70% success rate
                {
                    attackerCount--;
                }
            }

            // if attacker wins, take the territory and move the remaining attackers over
            if (defenderCount <= 0 && attackerCount > 0)
            {
                this->target->setOccupierName(this->source->occupierName);
                this->target->setTerritoryNumberOfArmies(attackerCount);
                this->source->setTerritoryNumberOfArmies(this->source->numOfArmies - this->howManyUnits);
                this->effect = this->whichPlayer->getPlayerName() + " captured " + this->target->territoryName;
                this->whichPlayer->setCapturedTerritoryThisTurn(true); // this Player has captured a territory now and gets a card
            }
            // otherwise just update the unit counts on the territories
            else
            {
                if (defenderCount < 0)
                {
                    defenderCount = 0;
                }
                if (attackerCount < 0)
                {
                    attackerCount = 0;
                }

                this->target->setTerritoryNumberOfArmies(defenderCount);
                this->source->setTerritoryNumberOfArmies(this->source->numOfArmies - (howManyUnits - attackerCount));
                this->effect = this->whichPlayer->getPlayerName() + "'s attack on " + this->target->territoryName + " was unsuccesful";
            }
        }
    }
    else
    {
        this->effect = this->whichPlayer->getPlayerName() + "'s Advance was not valid..";
    }

    this->executed = true; // should this only happen if valid? or both so it can be removed? (double check)
    std::cout << "execute() called in an Advance object" << std::endl;
    std::cout << this->effect << std::endl;
}

// assignment operator
Advance &Advance::operator=(const Advance &advance)
{
    this->effect = advance.effect;
    this->executed = advance.executed;

    return *this;
}

// print helper method for stream insertion overload
void Advance::print(std::ostream &output) const
{
    output << "Advance" << std::endl;
}

// stream insertion operator overload
std::ostream &operator<<(std::ostream &output, const Advance &advance)
{
    advance.print(output);
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
    std::cout << "Bomb object created using default constructor\n"
              << std::endl;
}

// copy constructor
Bomb::Bomb(const Bomb &existingBomb)
{
    this->effect = existingBomb.effect;
    std::cout << "Bomb object created using copy constructor" << std::endl;
}

// parameterized constructor
Bomb::Bomb(Player *p, Territory *t)
{
    this->whichPlayer = p;
    this->target = t;
}

// destructor
Bomb::~Bomb() {}

// validate method override
bool Bomb::validate()
{
    std::cout << "validate() called in a Bomb object\n"
              << std::endl;

    // check target belongs to other player
    if (this->whichPlayer->getPlayerName() == this->target->occupierName)
    {
        return false;
    }

    return true;
}

// execute method override
void Bomb::execute()
{
    if (this->validate())
    {
        this->target->setTerritoryNumberOfArmies(this->target->numOfArmies / 2); // halve the target's army count
        this->effect = this->whichPlayer->getPlayerName() + " bombed " + this->target->territoryName;
    }
    else
    {
        this->effect = this->whichPlayer->getPlayerName() + "'s bomb failed..";
    }

    std::cout << "execute() called in a Bomb object" << std::endl;
    this->executed = true;
    std::cout << this->effect << std::endl;
}

// assignment operator
Bomb &Bomb::operator=(const Bomb &bomb)
{
    this->effect = bomb.effect;
    this->executed = bomb.executed;

    return *this;
}

// print helper method for stream insertion overload
void Bomb::print(std::ostream &output) const
{
    output << "Bomb" << std::endl;
}

// stream insertion operator overload
std::ostream &operator<<(std::ostream &output, const Bomb &bomb)
{
    bomb.print(output);
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
    std::cout << "Blockade object created using default constructor\n"
              << std::endl;
}

// copy constructor
Blockade::Blockade(const Blockade &existingBlockade)
{
    this->effect = existingBlockade.effect;
    std::cout << "Blockade object created using copy constructor" << std::endl;
}

// destructor
Blockade::~Blockade() {}

// validate method override
bool Blockade::validate()
{
    std::cout << "validate() called in a Blockade object" << std::endl;
    return true;
}

// execute method override
void Blockade::execute()
{
    if (this->validate())
    {
        std::cout << "execute() called in a Blockade object" << std::endl;
        this->executed = true;
    }
}

// assignment operator
Blockade &Blockade::operator=(const Blockade &blockade)
{
    this->effect = blockade.effect;
    this->executed = blockade.executed;

    return *this;
}

// print helper method for stream insertion overload
void Blockade::print(std::ostream &output) const
{
    output << "Blockade" << std::endl;
}

// stream insertion operator overload
std::ostream &operator<<(std::ostream &output, const Blockade &blockade)
{
    blockade.print(output);
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
    std::cout << "Airlift object created using default constructor\n"
              << std::endl;
}

// copy constructor
Airlift::Airlift(const Airlift &existingAirlift)
{
    this->effect = existingAirlift.effect;
    std::cout << "Airlift object created using copy constructor" << std::endl;
}

// parameterized constructor
Airlift::Airlift(Player *p, int n, Territory *s, Territory *t)
{
    this->whichPlayer = p;
    this->howManyUnits = n;
    this->source = s;
    this->target = t;
}

// destructor
Airlift::~Airlift() {}

// validate method override
bool Airlift::validate()
{
    std::cout << "validate() called in an Airlift object" << std::endl;

    // check source and target belong to the player
    if (!(this->source->occupierName == this->target->occupierName && this->source->occupierName == this->whichPlayer->getPlayerName()))
    {
        return false;
    }

    // check source has enough units available to move
    if (this->howManyUnits > this->source->numOfArmies)
    {
        return false;
    }

    return true;
}

// execute method override
void Airlift::execute()
{
    if (this->validate())
    {
        this->source->setTerritoryNumberOfArmies(this->source->numOfArmies - this->howManyUnits);
        this->target->setTerritoryNumberOfArmies(this->target->numOfArmies + this->howManyUnits);
        this->effect = this->whichPlayer->getPlayerName() + " airlifted " + std::to_string(this->howManyUnits) + " from " + this->source->territoryName + " to " + this->target->territoryName;
    }
    else
    {
        this->effect = this->whichPlayer->getPlayerName() + "'s airlift not valid..";
    }

    std::cout << "execute() called in an Airlift object" << std::endl;
    this->executed = true;
    std::cout << this->effect << std::endl;
}

// assignment operator
Airlift &Airlift::operator=(const Airlift &airlift)
{
    this->effect = airlift.effect;
    this->executed = airlift.executed;

    return *this;
}

// print helper method for stream insertion overload
void Airlift::print(std::ostream &output) const
{
    output << "Airlift" << std::endl;
}

// stream insertion operator overload
std::ostream &operator<<(std::ostream &output, const Airlift &airlift)
{
    airlift.print(output);
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
    std::cout << "Negotiate object created using default constructor\n"
              << std::endl;
}

// copy constructor
Negotiate::Negotiate(const Negotiate &existingNegotiate)
{
    this->effect = existingNegotiate.effect;
    std::cout << "Negotiate object created using copy constructor" << std::endl;
}

// destructor
Negotiate::~Negotiate() {}

// validate method override
bool Negotiate::validate()
{
    std::cout << "validate() called in a Negotiate object" << std::endl;
    return true;
}

// execute method override
void Negotiate::execute()
{
    if (this->validate())
    {
        std::cout << "execute() called in a Negotiate object" << std::endl;
        this->executed = true;
    }
}

// assignment operator
Negotiate &Negotiate::operator=(const Negotiate &negotiate)
{
    this->effect = negotiate.effect;
    this->executed = negotiate.executed;

    return *this;
}

// print helper method for stream insertion overload
void Negotiate::print(std::ostream &output) const
{
    output << "Negotiate" << std::endl;
}

// stream insertion operator overload
std::ostream &operator<<(std::ostream &output, const Negotiate &negotiate)
{
    negotiate.print(output);
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
    std::cout << "OrdersList object created using default constructor" << std::endl;
}

// copy constructor
OrdersList::OrdersList(const OrdersList &existingOrdersList)
{
    this->ordersList = existingOrdersList.ordersList;
    std::cout << "OrdersList object created using copy constructor" << std::endl;
}

OrdersList::~OrdersList()
{
    // change all the pointers to nullptr
    for (Order *order : ordersList)
    {
        order = nullptr;
    }
}

// add an order to the list
void OrdersList::addOrder(Order *order)
{
    this->ordersList.push_back(order);
    Notify(*this);
}

// get next order on the list
Order *OrdersList::getNextOrder()
{
    std::cout << "getNextOrder() was called\n"
              << std::endl;

    // if list not empty, pop and return next order
    if (!ordersList.empty())
    {
        Order *nextOrderPtr = ordersList.front();
        ordersList.pop_front();
        return nextOrderPtr;
    }
    else
    { // if list is empty, print a message
        std::cout << " -- Order list is empty !" << std::endl;
        return nullptr;
    }
}

// remove an order from the list [takes an int, which is a menu number]
void OrdersList::remove(int num)
{
    // index is one less than menu numbering
    num--;

    this->ordersList.erase(this->ordersList.begin() + num);

    std::cout << "an order was removed\n"
              << std::endl;
}

// swap two orders in the list [takes two ints, which are menu numbers]
void OrdersList::move(int a, int b)
{
    // index is one less than menu numbering
    a--;
    b--;

    Order *temp = this->ordersList[a];

    this->ordersList[a] = this->ordersList[b];
    this->ordersList[b] = temp;

    std::cout << "orders were swapped\n"
              << std::endl;
}

string OrdersList::stringToLog() const
{
    Order *latestOrder = ordersList.back();
    const char *className = typeid(*latestOrder).name();
    if (!this->ordersList.empty())
    {
        // Get the last order in the list
        return "Orders List Log: An Order was successfully added. Order Type: " + std::string(className);
    }
    else
    {
        return "Orders List Log: No orders in the list.";
    }
}

// assignment operator
OrdersList &OrdersList::operator=(const OrdersList &orderslist)
{
    this->ordersList = orderslist.ordersList;

    return *this;
}

// stream insertion operator overload
std::ostream &operator<<(std::ostream &output, const OrdersList &orderslist)
{
    // creates a temporary copy of orderlist and traverse it to print it out
    std::deque<Order *> temp = orderslist.ordersList;
    int i = 1;
    while (!temp.empty())
    {
        Order *tempObj = temp.front();
        std::cout << std::to_string(i) + ": ";
        std::cout << *tempObj << std::endl;
        temp.pop_front();
        i++;
    }

    return output;
}
