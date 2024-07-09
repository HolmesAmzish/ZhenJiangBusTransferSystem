/**
 * File: Menu.cpp
 * Date: 2024.07.06
 * Author: Nulla
 */

#include "Menu.h"
#include <iostream>
using namespace std;
void showLoginMenu() {
    cout << "+----------| Login Menu |----------+" << endl;
    cout << "| 1. Login                         |" << endl;
    cout << "| 2. Exit                          |" << endl;
    cout << "+----------------------------------+" << endl;
    cout << "(Enter the option): ";
}

void showAdminMenu() {
    cout << "+----------| Admin Menu |----------+" << endl;
    cout << "| 1. Query Bus Route               |" << endl;
    cout << "| 2. Find Shortest Route by Time   |" << endl;
    cout << "| 3. Find Shortest Route by Cost   |" << endl;
    cout << "| 4. Check Recommended Route       |" << endl;
    cout << "| 5. Maintain Routes               |" << endl;
    cout << "| 6. Exit                          |" << endl;
    cout << "+----------------------------------+" << endl;
    cout << "(Enter the option): ";
}

void showManagerMenu() {
    cout << "+----------| Manage Menu |---------+" << endl;
    cout << "| 1. Display All Stop              |" << endl;
    cout << "| 2. Add Stop                      |" << endl;
    cout << "| 3. Delete Stop                   |" << endl;
    cout << "| 4. Reload System                 |" << endl;
    //cout << "| 5. Add Route                     |" << endl;
    //cout << "| 6. Delete Route                  |" << endl;
    cout << "| 5. Go Back                       |" << endl;
    cout << "+----------------------------------+" << endl;
    cout << "(Enter the option): ";
}

void showVisitorMenu() {
    cout << "+----------| Guest Menu |----------+" << endl;
    cout << "| 1. Query Bus Route               |" << endl;
    cout << "| 2. Find Shortest Route by Time   |" << endl;
    cout << "| 3. Find Shortest Route by Cost   |" << endl;
    cout << "| 4. Check Recommended Route       |" << endl;
    cout << "| 5. Exit                          |" << endl;
    cout << "+----------------------------------+" << endl;
    cout << "(Enter the option): ";
}

void closeSession() {
    cout << "Press any key to continue..." << endl;
    cin.ignore();
    cin.get();
    system("clear");
}