#include "menu.h"
#include <iostream>

void Menu::displayMenu() {
    std::cout << "1. Find shortest path\n";
    std::cout << "2. View user information\n";
    std::cout << "3. Exit\n";
}

void Menu::handleUserInput(Route& route, User& user) {
    int choice;
    while (true) {
        displayMenu();
        std::cin >> choice;

        if (choice == 1) {
            int startId, endId;
            std::cout << "Enter start stop ID: ";
            std::cin >> startId;
            std::cout << "Enter end stop ID: ";
            std::cin >> endId;

            auto path = route.findShortestPath(startId, endId);
            if (path.empty()) {
                std::cout << "Invalid stop IDs or no path found." << std::endl;
            } else {
                std::cout << "Shortest path: ";
                for (auto stop : path) {
                    std::cout << stop->getName() << " ";
                }
                std::cout << std::endl;
            }
        } else if (choice == 2) {
            std::cout << "User ID: " << user.getId() << "\n";
            std::cout << "User Name: " << user.getName() << "\n";
        } else if (choice == 3) {
            break;
        } else {
            std::cout << "Invalid choice. Try again.\n";
        }
    }
}
