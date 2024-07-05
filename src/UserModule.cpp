/**
 * File: UserModule.cpp
 * Date: 2024.07.05
 * Author: Nulla
 * Description: Source file of User Module
 */

#include "UserModule.h"
#include <fstream>
#include <sstream>


void UserModule::loadUser(string file_path) {
    ifstream file(file_path);
    if (!file.is_open()) {
        cerr << "Can't open file: " << file_path << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string username, password, is_admin_str;
        bool is_admin;

        if (!(iss >> username >> password >> is_admin_str)) {
            cerr << "File format error: " << line << endl;
            continue;
        }

        is_admin = (is_admin_str == "true");
        User user = {username, password, is_admin};
        users[username] = user;
    }
    file.close();
}

bool UserModule::login(string username, string password) {
    auto it = users.find(username);
    if (it != users.end() && password == it->second.password) {
        return true;
    }
    return false;
}

bool UserModule::isAdmin(string username) {
    auto it = users.find(username);
    if (it != users.end()) {
        return it->second.isAdmin;
    }
    return false;
}