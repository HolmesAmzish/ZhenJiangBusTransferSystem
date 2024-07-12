/**
 * @brief: main.cpp
 * @date: 2024.07.07
 * @author: Nulla
 * @details: Main file
 */

#include "Controller/RouteController.h"
#include "Controller/UserController.h"
#include "Menu.h"
#include "View.h"


int main() {
    system("clear");
    cout << "镇江公交车换乘系统" << endl;

    //Login Loop
    UserController user_controller;
    user_controller.loadUser("data/users.csv");
    bool have_login = false;
    string username, password;
    // Can be used next loop
    while (!have_login) {
        showLoginMenu();
        string option; cin >> option;
        // Set the option as string type for invalid input
        if (option == "1") {
            have_login = loginSession(user_controller, username, password);

        } else if (option == "2") {
            cout << "感谢使用镇江公交车换乘系统。" << endl;
            exit(0);

        } else {
            system("clear");
            cout << "错误选择，请重试。" << endl;

        }
    }

    // Main Loop
    RouteController route_controller;
    route_controller.loadRouteInformation("data/stops.csv", "data/routes.csv");
    system("clear");
    cout << "登陆成功！" << endl;
    while (true) {
        string option;
        if (user_controller.isAdmin(username)) {
            /**
             * @brief Admin menu
             * 1. Query Bus Route             
             * 2. Find Shortest Route by Time 
             * 3. Find Shortest Route by Cost 
             * 4. Check Recommended Route     
             * 5. Maintain Routes             
             * 6. Exit                   
             */
            showAdminMenu();
            cin >> option;
            if (option == "1") {
                queryBusRoute(route_controller);
                closeSession();

            } else if (option == "2") {
                findShortestPathByTime(route_controller);
                closeSession();

            } else if (option == "3") {
                findShortestPathByCost(route_controller);
                closeSession();

            } else if (option == "4") {
                checkRecommendRoute(route_controller);
                closeSession();
                
            } else if (option == "5") {
                /**
                 * @brief Manager menu
                 * 1. Display All Stop              
                 * 2. Add Stop                      
                 * 3. Delete Stop                   
                 * 4. Reload System             
                 * 5. Go Back                       
                 */
                system("clear");
                cout << "欢迎访问管理系统。" << endl;
                while (true) {
                    showManagerMenu();
                    int option; cin >> option;
                    if (option == 1) {
                        route_controller.displayAllStops();
                        closeSession();

                    } else if (option == 2) {
                        addStop(route_controller);
                        closeSession();

                    } else if (option == 3) {
                        cout << "=====| 删除站点 |=====" << endl;
                        cout << "输入要删除的站点ID: ";
                        int stop_id; cin >> stop_id;
                        route_controller.deleteStop(stop_id);
                        closeSession();

                    } else if (option == 4) {
                        reinitialize(user_controller, route_controller);
                        closeSession();

                    } else if (option == 5) {
                        system("clear");
                        break;
                    } else {
                        system("clear");
                        cout << "错误选择，请重试。" << endl;
                    }
                }
            } else if (option == "6") {
                cout << "退出中..." << endl;
                cout << "感谢使用镇江公交车换乘系统" << endl;
                exit(0);

            } else {
                system("clear");
                cout << "错误选择，请重试。" << endl;
            }
        } else {

            /**
             * @brief Visitor Menu
             * 1. Query Bus Route             
             * 2. Find Shortest Route by Time 
             * 3. Find Shortest Route by Cost 
             * 4. Check Recommended Route     
             * 5. Exit                        
             */
            showVisitorMenu();
            cin >> option;
            if (option == "1") {
                queryBusRoute(route_controller);
                closeSession();

            } else if (option == "2") {
                findShortestPathByTime(route_controller);
                closeSession();

            } else if (option == "3") {
                findShortestPathByCost(route_controller);
                closeSession();

            } else if (option == "4") {
                checkRecommendRoute(route_controller);
                closeSession();

            } else if (option == "5") {
                cout << "退出中..." << endl;
                cout << "感谢使用镇江公交车换乘系统。" << endl;
                exit(0);

            } else {
                system("clear");
                cout << "错误选择，请重试。" << endl;
            }
        }
    }
}