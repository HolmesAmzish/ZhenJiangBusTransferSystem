/**
 * Program: test/RouteModuleTest.cpp
 * Date: 2024.07.07
 * Author: Nulla
 * Description: Test for RouteModule
 */

#include "../src/Controller/RouteController.h"
#include "../src/Menu.h"
#include <cstdlib>

int main() {
    RouteController controller;
    cout << "Initializing the system." << endl;
    controller.loadRouteInformation("E:/Projects/ZhenJiangBusTransferSystem/data/stops.csv",
                                    "E:/Projects/ZhenJiangBusTransferSystem/data/routes.csv");
    cout << "The admin menu will be displayed" << endl;
    while (true) {
        int option;
        cout << "1. Reload route information." << endl;
        cout << "2. Query shortest path." << endl;
        cout << "3. Exit." << endl;
        cout << "Please enter your option: ";
        cin >> option;
        switch (option) {
            case 1: {
                controller.displayAllStops();
                break;
            }
            case 2: {
                int start_stop_id, end_stop_id;
                cout << "Enter the start stop id: ";
                cin >> start_stop_id;
                cout << "Enter the end stop id: ";
                cin >> end_stop_id;
                controller.queryShortestPathByTime(start_stop_id, end_stop_id);
                break;
            }
            case 3: {
                cout << "Exiting the system." << endl;
                exit(0);
            }
            default:
                cout << "Invalid option." << endl;
                break;
        }
    }

    return 0;
}
