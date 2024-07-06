#ifndef USER_VIEW_H
#define USER_VIEW_H

#include "../Controller/UserController.h"

class UserView {
    private:
    UserController& controller;

    public:
    UserView(UserController& controller);
    void showLogin();
};

#endif