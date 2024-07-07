/**
 * File: Controller/UserController.cpp
 * Date: 2024.07.05
 * Author: Nulla
 * Description: Head file of User Module
 */

#ifndef USER_CONTROLLER_H
#define USER_CONTROLLER_H

#include "../Model/User.h"
#include <unordered_map>
#include <string>

class UserController {
public:
    std::unordered_map<std::string, User> users;

    void loadUser(std::string file_path);
    void reloadUser(std::string file_path);
    bool login(std::string username, std::string password);
    bool isAdmin(std::string username);
};

#endif
