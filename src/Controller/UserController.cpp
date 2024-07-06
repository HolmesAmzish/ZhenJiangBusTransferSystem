/**
 * File: Controller/UserController.cpp
 * Date: 2024.07.05
 * Author: Nulla
 * Description: Source file of User Module
 */

#include "UserController.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

void UserController::loadUser(string file_path) {
    ifstream file(file_path);
    if (!file.is_open()) {
        cerr << "Can't open file: " << file_path << endl;
        return;
    }

    string line;
    bool header = true;
    while (getline(file, line)) {
        // Skip header line
        if (header) {
            header = false;
            continue;
        }

        stringstream ss(line);
        string username, password, is_admin_str;
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, is_admin_str, ',');

        bool is_admin = (is_admin_str == "true");
        User user = {username, password, is_admin};
        users[username] = user;
    }
    file.close();
}

bool UserController::login(string username, string password) {
    auto it = users.find(username);
    if (it != users.end() && password == it->second.password) {
        return true;
    }
    return false;
}

bool UserController::isAdmin(string username) {
    auto it = users.find(username);
    if (it != users.end()) {
        return it->second.isAdmin;
    }
    return false;
}
