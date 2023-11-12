#include "CommandProcessing.h"
#include "Orders.h"
#include "GameEngine.h"
#include "Cards.h"
#include "LogObserver.h"
#include "LoggingObserverDriver.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cctype>
#include <algorithm>
#include <map>
#include "MapDriver.h"
#include "Map.h"
void testLoggingObserver()
{
    // LogObserver concreteObserverObj;

    // Create instances of classes
    // CommandProcessor commandProcessorObj;
    // Command commandObject("your_cmd_name");
    // Since Order is an abstract class, we can only use a class derived from the Order class
    // Deploy deployOrder;
    // OrdersList orderList;
    GameEngine gameEngine;

    // Check if instances are subclasses of Subject
    // static_assert(std::is_base_of<Subject, CommandProcessor>::value);
    // static_assert(std::is_base_of<Subject, Command>::value);
    // static_assert(std::is_base_of<Subject, Deploy>::value);
    // static_assert(std::is_base_of<Subject, OrdersList>::value);
    // static_assert(std::is_base_of<Subject, GameEngine>::value);

    // Check if instances are subclasses of ILoggable
    // static_assert(std::is_base_of<ILoggable, CommandProcessor>::value);
    // static_assert(std::is_base_of<ILoggable, Command>::value);
    // static_assert(std::is_base_of<ILoggable, Deploy>::value);
    // static_assert(std::is_base_of<ILoggable, OrdersList>::value);
    // static_assert(std::is_base_of<ILoggable, GameEngine>::value);

    // commandProcessor.saveCommand(command);
    // commandObj.saveEffect("hello");
}
int main()
{
    testLoggingObserver();
    return 0;
}