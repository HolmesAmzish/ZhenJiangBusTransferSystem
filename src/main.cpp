/**
 * Program: main.cpp
 * Date: 2024.07.07
 * Author: Nulla
 * Description: Main file
 */

#include "Controller/RouteController.h"
#include "Controller/UserController.h"
#include "Menu.h"

int main() {
    system("clear");
    cout << "Zhenjiang Bus Transfer System" << endl;

    /**
     * Login loop
     */
    UserController user_controller;
    user_controller.loadUser("data/users.csv");
    bool have_login = false;
    string username, password; // Can be used next loop
    while (!have_login) {
        showLoginMenu();
        string option; cin >> option; // Set the option as char type for invalid input
        if (option == "1") {
            cout << "===| Login |===" << endl;
            cout << "Enter Username: ";
            cin >> username;
            cout << "Password: ";
            cin >> password;
            if (user_controller.login(username, password)) {
                have_login = true;
                break;
            } else {
                system("clear");
                cout << "Login failed, incorrect username or password." << endl;
            }
        } else if (option == "2") {
            cout << "Thanks for using the program." << endl;
            exit(0);
        } else {
            system("clear");
            cout << "Invalid option, please try again." << endl;
        }
    }

    /**
     * Main loop
     */
    RouteController route_controller;
    route_controller.loadRouteInformation("data/stops.csv", "data/routes.csv");
    system("clear");
    cout << "Login successful!" << endl;
    while (true) {
        string option;
        if (!user_controller.isAdmin(username)) {
            showVisitorMenu();
            cin >> option;
            if (option == "1") {

            }
        }
    }
}