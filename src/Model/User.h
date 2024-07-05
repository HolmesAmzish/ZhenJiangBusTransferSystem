/**
 * File: User.h
 * Date: 2024.07.05
 * Author: Nulla
 * Description: model of user.
 */

#ifndef USER_H
#define USER_H

#include <string>

class User {
public:
    std::string username;
    std::string password;
    bool isAdmin;
};

#endif
