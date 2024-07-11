/**
 * Program: main.cpp
 * Date: 2024.07.07
 * Author: Nulla
 * Description: Main file
 */

#include "Controller/RouteController.h"
#include "Controller/UserController.h"
#include "Menu.h"
#include "View.h"


int main() {
    system("clear");
    cout << "Zhenjiang Bus Transfer System" << endl;

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
                 * TODO: 6. Delete Route                
                 * Go Back                       
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
                        cout << "=====| 添加站点 |=====" << endl;
                        int route_id, stop_id;
                        string stop_name;
                        float cost, fare;
                        cout << "输入路线编号: ";
                        cin >> route_id;
                        cout << "输入要添加的站点ID: ";
                        cin >> stop_id;
                        cout << "输入要添加的站点名称: ";
                        cin >> stop_name;
                        cout << "输入要添加的站点花费: ";
                        cin >> cost;
                        cout << "输入要添加的站点时间: ";
                        cin >> fare;
                        route_controller.addStop(route_id, stop_id, stop_name, cost, fare);
                        closeSession();

                    } else if (option == 3) {
                        cout << "=====| 删除站点 |=====" << endl;
                        cout << "输入要删除的站点ID: ";
                        int stop_id; cin >> stop_id;
                        route_controller.deleteStop(stop_id);
                        closeSession();

                    } else if (option == 4) {
                        cout << "=====| 重新初始化 |=====" << endl;
                        string user_file_path, stop_file_path, route_file_path;
                        cout << "输入用户文件: ";
                        cin >> user_file_path;
                        user_controller.reloadUser(user_file_path);
                        cout << "输入站点文件: ";
                        cin >> stop_file_path;
                        cout << "输入路线文件: ";
                        cin >> route_file_path;
                        cout << "加载重新加载信息..." << endl;
                        route_controller.reloadRouteInformation(stop_file_path, route_file_path);
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
                cout << "错误选择，请重试。" << endl;
            }
        }
    }
}