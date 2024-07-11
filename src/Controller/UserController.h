/**
 * @brief: Controller/UserController.cpp
 * @date: 2024.07.05
 * @author: Nulla
 * @details: Head file of User Module
 */

#ifndef USER_CONTROLLER_H
#define USER_CONTROLLER_H

#include <bits/stdc++.h>

using namespace std;

struct User {
    string username;
    string password;
    bool isAdmin;
};

class UserController {
public:
    unordered_map<string, User> users;

    void loadUser(string file_path);
    void reloadUser(string file_path);
    bool login(string username, string password);
    bool isAdmin(string username);
};

#endif
