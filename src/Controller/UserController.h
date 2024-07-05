/**
 * File: UserController.cpp
 * Date: 2024.07.05
 * Author: Nulla
 * Description: Head file of User Module
 */

#ifndef USER_MODULE_H
#define USER_MODULE_H

#include "../Model/User.h"
#include <vector>
#include <unordered_map>

using namespace std;

class UserController {
    private:
    unordered_map<string, User> users;

    public:
    void loadUser(string file_path);
    bool login(string username, string password);
    bool isAdmin(string username);
};

#endif