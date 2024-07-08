/**
 * Program: test_main.cpp
 * Date: 2024.07.07
 * Author: Nulla
 * Description: Main test file
 */

#include "../src/Controller/RouteController.h"
#include "../src/Controller/UserController.h"
#include "../src/Menu.h"

#include <iostream>
#include <cstdlib>

using namespace std;

int main() {
    cout << "Welcome to the main test program!" << endl;
    cout << "Initializing user controller and route controller." << endl;
    UserController userController;
    RouteController routeController;
    userController.loadUser("../data/users.csv");
    routeController.loadRouteInformation("../data/stops.csv", "../data/routes.csv");
    while (true) {
        showLoginMenu();
        int option;
        switch (option) {
            case 1: {
                cout << "Please enter your username: ";
                string username; cin >> username;
                cout << "Please enter your password: ";
                string password; cin >> password;
                if (userController.login(username, password)) {
                    system("clear");
                    cout << "Login successful!" << endl;
                    if (userController.isAdmin(username)) {
                        while (true) {
                            showAdminMenu();
                        }
                    } else {
                        while (true) {
                            showVisitorMenu();
                        }
                    }
                } else {
                    system("clear");
                    cout << "Login failed! Username or password incorrect." << endl;
                    break;
                }
            }
            case 2: {
                cout << "Exiting the program!" << endl;
                exit(0);
            }
        }
    }
}