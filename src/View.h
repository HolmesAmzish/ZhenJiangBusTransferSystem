/**
 * File: Menu.h
 * Date: 2024.07.07
 * Author: Nulla
 */

#ifndef VIEW_H
#define VIEW_H

#include "Controller/UserController.h"
#include "Controller/RouteController.h"
#include <iostream>
#include <string>
#include <algorithm>

bool loginSession(UserController userController, string& username, string& password);
int convertNameToId(string name, RouteController& controller);
void queryBusRoute(RouteController& controller);
void findShortestPathByTime(RouteController& controller);
void findShortestPathByCost(RouteController& controller);
void checkRecommendRoute(RouteController& controller);
void closeSession();

#endif // MENU_H
