/**
 * File: TestMain.cpp
 * Date: 2024.07.05
 * Author: Nulla
 * Description: Main program of the project
 */

#include "UserModule.h"
#include "View.h"
#include <iostream>

int main() {
    UserModule user_module;
    user_module.loadUser("data/users.csv");

    string username, password;
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter the password: ";
    cin >> password;
    if (!user_module.login(username, password)) {
        cerr << "Login failed, wrong username or password." << endl;
        return 1;
    }

    bool isAdmin = user_module.isAdmin(username);


}