#ifndef MENU_H
#define MENU_H

#include "route.h"
#include "user.h"

class Menu {
public:
    void displayMenu();
    void handleUserInput(Route& route, User& user);
};

#endif // MENU_H
