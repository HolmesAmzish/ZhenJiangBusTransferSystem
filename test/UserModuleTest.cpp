/**
 * File: UserModuleTest.cpp
 * Date: 2024.07.05
 * Author: Nulla
 * Description: The test program of user module, including User Contorller and User View.
 */

#include "../src/Controller/UserController.h"
#include "../src/View/UserView.h"
#include <iostream>
#include <cstdlib>

using namespace std;

int main() {
    UserController controller;
    UserView view;

    while (true) {
        view.displayLogin();
        int choice;
        cin >> choice;

        if (choice == 1) {
            string username, password;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;

            controller.loadUser("../data/users.csv");
            if (controller.login(username, password)) {
                if (controller.isAdmin(username)) {
                    view.displayAdminMenu();
                } else {
                    view.displayUserMenu();
                }
            } else {
                cout << "Login failed. Please try again." << endl;
            }
        } else if (choice == 2) {
            cout << "Bye." << endl;
            break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
