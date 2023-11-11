#include "CommandProcessing.h"
#include "CommandProcessing.h"
#include "Orders.h"
#include "GameEngine.h"

void testLoggingObserver()
{
    // Create instances of classes
    CommandProcessor commandProcessor;
    Command command("A random command");
    Deploy deployOrder;
    OrdersList orderList;
    GameEngine gameEngine;

    // Check if instances are subclasses of Subject
    static_assert(std::is_base_of<Subject, CommandProcessor>::value);
    static_assert(std::is_base_of<Subject, Command>::value);
    static_assert(std::is_base_of<Subject, Deploy>::value);
    static_assert(std::is_base_of<Subject, OrdersList>::value);
    static_assert(std::is_base_of<Subject, GameEngine>::value);

    // Check if instances are subclasses of ILoggable
    static_assert(std::is_base_of<ILoggable, CommandProcessor>::value);
    static_assert(std::is_base_of<ILoggable, Command>::value);
    static_assert(std::is_base_of<ILoggable, Deploy>::value);
    static_assert(std::is_base_of<ILoggable, OrdersList>::value);
    static_assert(std::is_base_of<ILoggable, GameEngine>::value);
}