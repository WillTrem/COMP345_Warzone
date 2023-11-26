#pragma once

#include "GameEngine.h"
#include <string>

#ifndef GAME_ENGINE_DRIVER_H
#define GAME_ENGINE_DRIVER_H

// Sample actions
void start();
void loadMap();
void validateMap();
void addPlayer();
void assignCountries();
void issueOrder();
void endIssueOrders();
void executeOrder();
void endExecuteOrders();
void win();
void end();

// Testing functions
void testGameEngine();

void testStartupPhase();

void testMainGameLoop();

#endif // GAME_ENGINE_DRIVER_H