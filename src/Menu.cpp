/**
 * File: Menu.cpp
 * Date: 2024.07.06
 * Author: Nulla
 */

#include <iostream>
using namespace std;
void showLoginMenu() {
    cout << "+----------| Login Menu |----------+" << endl;
    cout << "| 1. Login                         |" << endl;
    cout << "| 2. Quit                          |" << endl;
    cout << "+----------------------------------+" << endl;
    cout << "(Enter the number): ";
}

void showAdminMenu() {
    cout << "+----------| Admin Menu |----------+" << endl;
    cout << "| 1. Initialize System             |" << endl;
    cout << "| 2. Manage Bus Stop               |" << endl;
    cout << "| 3. Manage Bus Route              |" << endl;
    cout << "| 4. Query Bus Route               |" << endl;
    cout << "| 5. Logout                        |" << endl;
    cout << "+----------------------------------+" << endl;
    cout << "(Enter the number): ";
}

void showVisitorMenu() {
    cout << "+----------| User Menu |----------+" << endl;
    cout << "| 1. Query Bus Route              |" << endl;
    cout << "| 2. Check recommended Route      |" << endl;
    cout << "| 3. Logout                       |" << endl;
    cout << "+---------------------------------+" << endl;
    cout << "(Enter the number): ";
}