/**
 * Program: test_main.cpp
 * Date: 2024.07.07
 * Author: Nulla
 * Description: Main test file
 */

#include "../src/Controller/RouteController.h"
#include "../src/Controller/UserController.h"
#include "../src/Menu.h"

#include <cstdlib>


int main() {
    cout << "Welcome to the main test program!" << endl;
    cout << "Initializing user controller and route controller." << endl;
    UserController userController;
    RouteController routeController;
    userController.loadUser("../data/users.csv");
    routeController.loadRouteInformation("../data/stops.csv", "../data/routes.csv");
    while (true) {
        showLoginMenu();
        int option; cin >> option;
        switch (option) {
            case 1: {
                cout << "Please enter your username: ";
                string username; cin >> username;
                cout << "Please enter your password: ";
                string password; cin >> password;
                if (userController.login(username, password)) {
                    // Login as string username and password
                    system("clear");
                    cout << "Login successful!" << endl;
                    if (userController.isAdmin(username)) {
                        /**
                         * Admin
                         * TODO: Implement admin menu
                         */
                        while (true) {
                            showAdminMenu();
                            int option; cin >> option;
                            switch (option) {
                                case 1: {

                                }
                            }
                        }
                    } else {
                        /**
                         * Guest
                         */
                        while (true) {
                            showVisitorMenu();
                            int option; cin >> option;
                            switch (option) {
                                case 1: {
                                    system("clear");
                                    cout << "===| Path Query |===" << endl;
                                    cout << "Please enter your start stop id: ";
                                    int start_stop_id; cin >> start_stop_id;
                                    cout << "Please enter your end stop id: ";
                                    int end_stop_id; cin >> end_stop_id;
                                    routeController.queryShortestPathByCost(start_stop_id,end_stop_id);
                                    break;
                                }
                                case 2: {
                                    system("clear");
                                    cout << "===| Route Query |===" << endl;
                                    cout << "Please enter your route id: ";
                                    int route_id; cin >> route_id;
                                    routeController.displayRouteById(route_id);
                                    break;
                                }
                                case 3: {
                                    cout << "Exiting..." << endl;
                                    exit(0);
                                }
                                default: {
                                    cout << "Invalid option!" << endl;
                                    break;
                                }
                            }
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