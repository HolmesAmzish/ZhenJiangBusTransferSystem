/**
 * File: UserModuleTest.cpp
 * Date: 2024.07.05
 * Author: Nulla
 * Description: The test program of user module, including User Contorller and User View.
 */

#include "../src/Controller/UserController.h"
#include "../src/View/UserView.h"
#include <iostream>

using namespace std;

int main() {
    UserController controller;
    UserView view;

    controller.loadUser("E:/Projects/ZhenJiangBusTransferSystem/data/users.csv");

    cout << "User loaded: " << endl;
    for (auto user : controller.users) {
        cout << user.first << ' ' << user.second.password << endl;
    }
    cout << endl;

    while (true) {
        view.displayLogin(controller);
    }

    return 0;
}
