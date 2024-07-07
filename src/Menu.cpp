/**
 * File: Menu.cpp
 * Date: 2024.07.06
 * Author: Nulla
 */

#include "Menu.h"
#include <iostream>

Menu::Menu(UserController& userController)
    : userController(userController) {}

void Menu::show() {
    showWelcomeMessage();

    while (true) {
        showLoginMenu();

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                // Handle login
                handleLoginChoice(choice);
                break;
            case 2:
                std::cout << "Exiting the system." << std::endl;
                return;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    }
}

void Menu::showWelcomeMessage() {
    std::cout << "Welcome to Zhenjiang Bus Transfer System!" << std::endl;
}

void Menu::showLoginMenu() {
    std::cout << "+-----| Login Menu |-----+" << std::endl;
    std::cout << "| 1. Login               |" << std::endl;
    std::cout << "| 2. Quit                |" << std::endl;
    std::cout << "+------------------------+" << std::endl;
    std::cout << "(Enter the number): ";
}

void Menu::showAdminMenu() {
    std::cout << "+-----| Admin Menu |-----+" << std::endl;
    std::cout << "| 1. Initialize System   |" << std::endl;
    std::cout << "| 2. Manage Bus Stop     |" << std::endl;
    std::cout << "| 3. Manage Bus Route    |" << std::endl;
    std::cout << "| 4. Query Bus Route     |" << std::endl;
    std::cout << "| 5. Logout              |" << std::endl;
    std::cout << "+------------------------+" << std::endl;
    std::cout << "(Enter the number): ";
}

void Menu::showVisitorMenu() {
    std::cout << "+-----| User Menu |-----+" << std::endl;
    std::cout << "| 1. Query Bus Route    |" << std::endl;
    std::cout << "| 2. Logout             |" << std::endl;
    std::cout << "+-----------------------+" << std::endl;
    std::cout << "(Enter the number): ";
}

void Menu::handleLoginChoice(int choice) {
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    if (userController.login(username, password)) {
        if (userController.isAdmin(username)) {
            showAdminMenu();
            // Handle admin menu choices
            int adminChoice;
            std::cin >> adminChoice;
            handleAdminChoice(adminChoice);
        } else {
            showVisitorMenu();
            // Handle visitor menu choices
            int visitorChoice;
            std::cin >> visitorChoice;
            handleVisitorChoice(visitorChoice);
        }
    } else {
        std::cout << "Login failed. Please try again." << std::endl;
    }
}

void Menu::handleAdminChoice(int choice) {
    // Handle admin menu choices
    switch (choice) {
        case 1:
            // Initialize system
            break;
        case 2:
            // Manage bus stop
            break;
        case 3:
            // Manage bus route
            break;
        case 4:
            // Query bus route
            break;
        case 5:
            std::cout << "Logging out." << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
    }
}

void Menu::handleVisitorChoice(int choice) {
    // Handle visitor menu choices
    switch (choice) {
        case 1:
            // Query bus route
            break;
        case 2:
            std::cout << "Logging out." << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
    }
}
