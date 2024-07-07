/**
 * Program: test/RouteModuleTest.cpp
 * Date: 2024.07.07
 * Author: Nulla
 * Description: Test for RouteModule
 */

#include "../src/Controller/RouteController.h"
#include "../src/Menu.cpp"
#include <iostream>
#include <cstdlib>

using namespace std;

int main() {
    RouteController controller;
    controller.loadRouteInformation("E:/Projects/ZhenJiangBusTransferSystem/data/routes.csv");

    // Show admin menu if defined and implemented
    showAdminMenu();  // Make sure showAdminMenu() is implemented and called correctly

    // Wait for user input before exiting
    cout << "Press enter to exit...";
    cin.get();

    return 0;
}
