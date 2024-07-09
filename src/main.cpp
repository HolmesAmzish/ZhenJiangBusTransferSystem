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
             * @brief Admin menu
             * 1. Query Bus Route             
             * 2. Find Shortest Route by Time 
             * 3. Find Shortest Route by Cost 
             * TODO: 4. Check Recommended Route     
             * 5. Maintain Routes             
             * 6. Exit                   
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
                string start_stop_name, end_stop_name;
                int start_stop_id, end_stop_id;
                cout << "Enter Start Stop ID or name: ";
                cin >> start_stop_name;
                cout << "Enter End Stop ID or name: ";
                cin >> end_stop_name;

                // Convert string to int
                if (all_of(start_stop_name.begin(), start_stop_name.end(), ::isdigit)) start_stop_id = stoi(start_stop_name);
                else start_stop_id = route_controller.stops_name_to_id[start_stop_name];
                if (all_of(end_stop_name.begin(), end_stop_name.end(), ::isdigit)) end_stop_id = stoi(end_stop_name);
                else end_stop_id = route_controller.stops_name_to_id[end_stop_name];
                
                route_controller.queryShortestPathByTime(start_stop_id, end_stop_id);
                closeSession();

            } else if (option == "3") {
                cout << "===| Shortest Path by Cost |===" << endl;
                string start_stop_name, end_stop_name;
                int start_stop_id, end_stop_id;
                cout << "Enter Start Stop ID or name: ";
                cin >> start_stop_name;
                cout << "Enter End Stop ID or name: ";
                cin >> end_stop_name;

                // Convert string to int
                if (all_of(start_stop_name.begin(), start_stop_name.end(), ::isdigit)) start_stop_id = stoi(start_stop_name);
                else start_stop_id = route_controller.stops_name_to_id[start_stop_name];
                if (all_of(end_stop_name.begin(), end_stop_name.end(), ::isdigit)) end_stop_id = stoi(end_stop_name);
                else end_stop_id = route_controller.stops_name_to_id[end_stop_name];
                
                route_controller.queryShortestPathByCost(start_stop_id, end_stop_id);
                closeSession();

            } else if (option == "4") {
                //TODO: Check Recommended Route

            } else if (option == "5") {
                /**
                 * @brief Manager menu
                 * 1. Display All Stop              
                 * TODO: 2. Add Stop                      
                 * TODO: 3. Delete Stop                   
                 * 4. Reload System                 
                 * TODO: 5. Add Route                   
                 * TODO: 6. Delete Route                
                 * Go Back                       
                 */
                system("clear");
                cout << "Welcome to route manage system" << endl;
                while (true) {
                    showManagerMenu();
                    int option; cin >> option;
                    if (option == 1) {
                        route_controller.displayAllStops();
                        closeSession();

                    } else if (option == 2) {

                    } else if (option == 3) {
                        cout << "===| Deleting Stop |===" << endl;
                        cout << "Enter Stop ID: ";
                        int stop_id; cin >> stop_id;
                        route_controller.deleteStop(stop_id);
                        closeSession();

                    } else if (option == 4) {
                        cout << "===| Reloading |===" << endl;
                        string user_file_path, stop_file_path, route_file_path;
                        cout << "Enter User File Path: ";
                        cin >> user_file_path;
                        user_controller.reloadUser(user_file_path);
                        cout << "Enter Stop File Path: ";
                        cin >> stop_file_path;
                        cout << "Enter Route File Path: ";
                        cin >> route_file_path;
                        cout << "Showing reloaded information..." << endl;
                        route_controller.reloadRouteInformation(stop_file_path, route_file_path);
                        closeSession();

                    } else if (option == 5) {

                    } else if (option == 6) {

                    } else if (option == 7) {
                        system("clear");
                        break;
                    } else {
                        system("clear");
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
             * @brief Visitor Menu
             * 1. Query Bus Route             
             * 2. Find Shortest Route by Time 
             * 3. Find Shortest Route by Cost 
             * TODO: 4. Check Recommended Route     
             * 5. Exit                        
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
                string start_stop_name, end_stop_name;
                int start_stop_id, end_stop_id;
                cout << "Enter Start Stop ID or name: ";
                cin >> start_stop_name;
                cout << "Enter End Stop ID or name: ";
                cin >> end_stop_name;

                // Convert string to int
                if (all_of(start_stop_name.begin(), start_stop_name.end(), ::isdigit)) start_stop_id = stoi(start_stop_name);
                else start_stop_id = route_controller.stops_name_to_id[start_stop_name];
                if (all_of(end_stop_name.begin(), end_stop_name.end(), ::isdigit)) end_stop_id = stoi(end_stop_name);
                else end_stop_id = route_controller.stops_name_to_id[end_stop_name];
                
                route_controller.queryShortestPathByTime(start_stop_id, end_stop_id);
                closeSession();

            } else if (option == "3") {
                cout << "===| Shortest Path by Cost |===" << endl;
                string start_stop_name, end_stop_name;
                int start_stop_id, end_stop_id;
                cout << "Enter Start Stop ID or name: ";
                cin >> start_stop_name;
                cout << "Enter End Stop ID or name: ";
                cin >> end_stop_name;

                // Convert string to int
                if (all_of(start_stop_name.begin(), start_stop_name.end(), ::isdigit)) start_stop_id = stoi(start_stop_name);
                else start_stop_id = route_controller.stops_name_to_id[start_stop_name];
                if (all_of(end_stop_name.begin(), end_stop_name.end(), ::isdigit)) end_stop_id = stoi(end_stop_name);
                else end_stop_id = route_controller.stops_name_to_id[end_stop_name];
                
                route_controller.queryShortestPathByCost(start_stop_id, end_stop_id);
                closeSession();

            } else if (option == "4") {

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