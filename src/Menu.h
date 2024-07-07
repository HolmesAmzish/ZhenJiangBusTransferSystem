/**
 * File: Menu.h
 * Date: 2024.07.06
 * Author: Nulla
 * Description:
 */

#ifndef MENU_H
#define MENU_H

#include "Controller/RouteController.h"
#include "Controller/UserController.h"

class Menu {
public:
    Menu(UserController& userController);

    void show();
private:
    void showWelcomeMessage();
    void showLoginMenu();
    void showAdminMenu();
    void showVisitorMenu();

    void handleLoginChoice(int choice);
    void handleAdminChoice(int choice);
    void handleVisitorChoice(int choice);

    UserController& userController;
};

#endif // MENU_H
