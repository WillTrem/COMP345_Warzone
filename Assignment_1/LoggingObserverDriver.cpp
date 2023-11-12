#include "LoggingObserverDriver.h"
#include "CommandProcessing.h"
using namespace std;
void testLoggingObserver()
{
    // Object Init Prerequisites
    Territory newTerritoryObj;
    newTerritoryObj.occupierName = "rand";
    Player newPlayerObj("rand");
    GameState latestState(WIN);

    // Object Initialization
    CommandProcessor commandProcessorObj;
    Command commandObj("NewCommand");
    Deploy deployOrderObj(&newPlayerObj, 10, &newTerritoryObj);
    OrdersList ordersListObj;
    GameEngine gameEngineObj;

    // Observer Creation
    LogObserver concreteObserver1;
    LogObserver concreteObserver2;
    LogObserver concreteObserver3;
    LogObserver concreteObserver4;
    LogObserver concreteObserver5;

    // Attaching Observers to Subjects
    commandProcessorObj.Attach(&concreteObserver1);
    commandObj.Attach(&concreteObserver2);
    deployOrderObj.Attach(&concreteObserver3);
    ordersListObj.Attach(&concreteObserver4);
    gameEngineObj.Attach(&concreteObserver5);

    // Asserting that the Objects are of Subclass Subject and ILoggable
    // Prints Error: Message if the condition is NOT met
    static_assert(std::is_base_of<Subject, decltype(commandProcessorObj)>::value,
                  "Error:commandProcessorObj must be a subclass of Subject");
    static_assert(std::is_base_of<ILoggable, decltype(commandProcessorObj)>::value,
                  "Error:commandProcessorObj must be a subclass of ILoggable");

    static_assert(std::is_base_of<Subject, decltype(commandObj)>::value,
                  "Error:commandObj must be a subclass of Subject");
    static_assert(std::is_base_of<ILoggable, decltype(commandObj)>::value,
                  "Error:commandObj must be a subclass of ILoggable");

    static_assert(std::is_base_of<Subject, decltype(deployOrderObj)>::value,
                  "Error:deployOrderObj must be a subclass of Subject");
    static_assert(std::is_base_of<ILoggable, decltype(deployOrderObj)>::value,
                  "Error:deployOrderObj must be a subclass of ILoggable");

    static_assert(std::is_base_of<Subject, decltype(ordersListObj)>::value,
                  "Error:ordersListObj must be a subclass of Subject");
    static_assert(std::is_base_of<ILoggable, decltype(ordersListObj)>::value,
                  "Error:ordersListObj must be a subclass of ILoggable");

    static_assert(std::is_base_of<Subject, decltype(gameEngineObj)>::value,
                  "Error:gameEngineObj must be a subclass of Subject");
    static_assert(std::is_base_of<ILoggable, decltype(gameEngineObj)>::value,
                  "Error:gameEngineObj must be a subclass of ILoggable");

    // Triggering Notify() on Subjects
    commandProcessorObj.saveCommand(&commandObj);
    commandObj.saveEffect("random");
    deployOrderObj.validate();
    deployOrderObj.execute();
    ordersListObj.addOrder(&deployOrderObj);
    gameEngineObj.transition(&latestState);
}
