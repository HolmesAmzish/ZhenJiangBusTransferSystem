/**
 * File: UserView.cpp
 * Date: 2024.07.05
 * Author: Nulla
 * Description: Source file of User view
 */

#include "UserView.h"
#include <iostream>
#include <cstdlib>

using namespace std;

// Display login screen
void UserView::displayLogin() {

    cout << "+-----| Login Menu |-----+" << endl;
    cout << "| 1. Login               |" << endl;
    cout << "| 2. Quit                |" << endl;
    cout << "+------------------------+" << endl;
    cout << "(Enter the number): ";
}

// Display admin menu
void UserView::displayAdminMenu() {
    cout << "+-----| Admin Menu |-----+" << endl;
    cout << "| 1. Initialize System   |" << endl;
    cout << "| 2. Manage Bus Stop     |" << endl;
    cout << "| 3. Manage Bus Route    |" << endl;
    cout << "| 4. Query Bus Route     |" << endl;
    cout << "| 5. Logout              |" << endl;
    cout << "+------------------------+" << endl;
    cout << "(Enter the number): ";
}

// Display user menu
void UserView::displayUserMenu() {
    cout << "+-----| User Menu |-----+" << endl;
    cout << "| 1. Query Bus Route    |" << endl;
    cout << "| 2. Logout             |" << endl;
    cout << "+-----------------------+" << endl;
    cout << "(Enter the number): ";
}
