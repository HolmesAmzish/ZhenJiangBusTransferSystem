/**
 * File: UserView.cpp
 * Date: 2024.07.05
 * Author: Nulla
 * Description: Source file of User view
 */

#include "UserView.h"
#include <iostream>

UserView::UserView(UserController& userController):controller(userController) {}

void UserView::showLogin() {
    std::cout << "=== Login ===" << std::endl;
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    if (controller.login(username, password)) {
        std::cout << "Login successful!" << std::endl;
        // Optionally, you can redirect to another menu or perform additional actions here
    } else {
        std::cout << "Login failed. Please try again." << std::endl;
    }
}
