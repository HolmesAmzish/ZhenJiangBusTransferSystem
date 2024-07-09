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
    cout << "| 1. Reload the system             |" << endl;
    cout << "| 2. Manage stops                  |" << endl;
    cout << "| 3. Manage Bus Route              |" << endl;
    cout << "| 4. Query Bus Route               |" << endl;
    cout << "| 5. Logout                        |" << endl;
    cout << "+----------------------------------+" << endl;
    cout << "(Enter the option): ";
}

void showVisitorMenu() {
    cout << "+----------| User Menu |----------+" << endl;
    cout << "| 1. Find Shortest Route          |" << endl;
    cout << "| 2. Query Bus Route              |" << endl;
    cout << "| 3. Check Recommended Route      |" << endl;
    cout << "| 4. Exit                         |" << endl;
    cout << "+---------------------------------+" << endl;
    cout << "(Enter the option): ";
}