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
        if (user_controller.isAdmin(username)) {
            /**
             * Admin
             */
            showAdminMenu();
            cin >> option;
            if (option == "1") {
                cout << "===| Query |===" << endl;
                cout << "Enter Route ID: ";
                int route_id; cin >> route_id;
                route_controller.displayRouteById(route_id);
                closeSession();

            } else if (option == "2") {
                cout << "===| Shortest Path by Time |===" << endl;
                int start_stop_id, end_stop_id;
                cout << "Enter Start Stop ID: ";
                cin >> start_stop_id;
                cout << "Enter End Stop ID: ";
                cin >> end_stop_id;
                route_controller.queryShortestPathByTime(start_stop_id, end_stop_id);
                closeSession();

            } else if (option == "3") {
                cout << "===| Shortest Path by Cost |===" << endl;
                int start_stop_id, end_stop_id;
                cout << "Enter Start Stop ID: ";
                cin >> start_stop_id;
                cout << "Enter End Stop ID: ";
                cin >> end_stop_id;
                route_controller.queryShortestPathByCost(start_stop_id, end_stop_id);
                closeSession();

            } else if (option == "4") {
                //TODO: Check Recommended Route

            } else if (option == "5") {
                cout << "Welcome to route manage system" << endl;
                while (true) {
                    showManagerMenu();
                    int option; cin >> option;
                    if (option == 1) {
                        //TODO: Display All stops
                    } else if (option == 2) {
                        //TODO: Add Stop
                    } else if (option == 3) {
                        //TODO: Delete Stop
                    } else if (option == 4) {
                        //TODO: Reload System
                    } else if (option == 5) {
                        //TODO: Add Route
                    } else if (option == 6) {
                        //TODO: Delete Route
                    } else if (option == 7) {
                        break;
                    } else {
                        cout << "Invalid option, please try again." << endl;
                    }
                }
            } else if (option == "6") {
                cout << "Loging out..." << endl;
                cout << "Thank you for using the system." << endl;
                exit(0);

            } else {
                cout << "Invalid option, please try again." << endl;
            }
        } else {
            /**
             * Visitor
             */
            showVisitorMenu();
            cin >> option;
            if (option == "1") {
                cout << "===| Query |===" << endl;
                cout << "Enter Route ID: ";
                int route_id; cin >> route_id;
                route_controller.displayRouteById(route_id);
                closeSession();

            } else if (option == "2") {
                cout << "===| Shortest Path by Time |===" << endl;
                int start_stop_id, end_stop_id;
                cout << "Enter Start Stop ID: ";
                cin >> start_stop_id;
                cout << "Enter End Stop ID: ";
                cin >> end_stop_id;
                route_controller.queryShortestPathByTime(start_stop_id, end_stop_id);
                closeSession();

            } else if (option == "3") {
                cout << "===| Shortest Path by Cost |===" << endl;
                int start_stop_id, end_stop_id;
                cout << "Enter Start Stop ID: ";
                cin >> start_stop_id;
                cout << "Enter End Stop ID: ";
                cin >> end_stop_id;
                route_controller.queryShortestPathByCost(start_stop_id, end_stop_id);
                closeSession();

            } else if (option == "4") {
                //TODO: Check Recommended Route

            } else if (option == "5") {
                cout << "Loging out..." << endl;
                cout << "Thank you for using the system." << endl;
                exit(0);

            } else {
                cout << "Invalid option, please try again." << endl;
            }
        }
    }
}