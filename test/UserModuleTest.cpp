/**
 * File: UserModuleTest.cpp
 * Date: 2024.07.05
 * Author: Nulla
 * Description: The test program of user module, including User Contorller and User View.
 */

#include "../src/Controller/RouteController.h"
#include "../src/Controller/UserController.h"
#include "../src/Menu.h"

#include <iostream>
#include <cstdlib>
using namespace std;

int main() {
    int option = 0;
    while (option != 2) {
        showLoginMenu();
        UserController user_controller;
        int option = 0;
        cout << "Press 2 to reload the user file" << endl;
        std::cin >> option;
        switch (option) {
            case 1: {
                // Initial the user controller
                user_controller.loadUser("E:/Projects/ZhenJiangBusTransferSystem/data/users.csv");

                // Login view
                cout << "=====| Login |=====" << endl;
                string username, password;
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;
                if (user_controller.login(username, password) == true) {
                    cout << "Login successful" << endl;
                    if (user_controller.isAdmin(username)) {
                        cout << "Identy: Admin" << endl;
                    } else {
                        cout << "Identy: Guest" << endl;
                    }
                    cout << "Logout..." << endl;
                    cin.ignore();
                    cin.get();
                    system("clear");
                } else {
                    cout << "Login failed" << endl;
                }
            }
            case 2:
                
                break;
            default:
                cout << "Invalid option" << endl;
                break;
        }
   }
  
    system("pause");
    return 0;
}