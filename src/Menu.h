/**
 * File: Menu.h
 * Date: 2024.07.06
 * Author: Nulla
 * Description:
 */

#ifndef MENU_H
#define MENU_H

#include "Controller/BusController.h"
#include "Controller/UserController.h"

class Menu {
public:
    Menu(UserController& userController, BusController& busController);

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
    BusController& busController;
};

#endif // MENU_H
