/**
 * Program: main.cpp
 * Date: 2024.07.07
 * Author: Nulla
 * Description: Main file
 */

#include "Controller/RouteController.h"
#include "Controller/UserController.h"
#include "Menu.h"

int main() {
    system("clear");
    cout << "Zhenjiang Bus Transfer System" << endl;

    /**
     * Login loop
     */
    UserController user_controller;
    user_controller.loadUser("data/users.csv");
    bool have_login = false;
    string username, password; // Can be used next loop
    while (!have_login) {
        showLoginMenu();
        string option; cin >> option; // Set the option as char type for invalid input
        if (option == "1") {
            cout << "=====| 登录 |=====" << endl;
            cout << "输入用户名: ";
            cin >> username;
            cout << "密码: ";
            cin >> password;
            if (user_controller.login(username, password)) {
                have_login = true;
                break;
            } else {
                system("clear");
                cout << "登录失败，错误的用户名或密码。" << endl;
            }
        } else if (option == "2") {
            cout << "感谢使用镇江公交车换乘系统。" << endl;
            exit(0);
        } else {
            system("clear");
            cout << "错误选择，请重试。" << endl;
        }
    }

    /**
     * Main loop
     */
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
             * TODO: 4. Check Recommended Route     
             * 5. Maintain Routes             
             * 6. Exit                   
             */
            showAdminMenu();
            cin >> option;
            if (option == "1") {
                cout << "=====| 查询 |=====" << endl;
                cout << "输入路线ID: ";
                int route_id; cin >> route_id;
                route_controller.displayRouteById(route_id);
                closeSession();

            } else if (option == "2") {
                cout << "=====| 最短时间路径 |=====" << endl;
                string start_stop_name, end_stop_name;
                int start_stop_id, end_stop_id;
                cout << "输入起始站: ";
                cin >> start_stop_name;
                cout << "输入终点站: ";
                cin >> end_stop_name;

                // Convert string to int
                if (all_of(start_stop_name.begin(), start_stop_name.end(), ::isdigit)) start_stop_id = stoi(start_stop_name);
                else start_stop_id = route_controller.stops_name_to_id[start_stop_name];
                if (all_of(end_stop_name.begin(), end_stop_name.end(), ::isdigit)) end_stop_id = stoi(end_stop_name);
                else end_stop_id = route_controller.stops_name_to_id[end_stop_name];
                
                route_controller.queryShortestPathByTime(start_stop_id, end_stop_id);
                closeSession();

            } else if (option == "3") {
                cout << "=====| 最短花费路径 |=====" << endl;
                string start_stop_name, end_stop_name;
                int start_stop_id, end_stop_id;
                cout << "输入起始站: ";
                cin >> start_stop_name;
                cout << "输入起始站: ";
                cin >> end_stop_name;

                // Convert string to int
                if (all_of(start_stop_name.begin(), start_stop_name.end(), ::isdigit)) start_stop_id = stoi(start_stop_name);
                else start_stop_id = route_controller.stops_name_to_id[start_stop_name];
                if (all_of(end_stop_name.begin(), end_stop_name.end(), ::isdigit)) end_stop_id = stoi(end_stop_name);
                else end_stop_id = route_controller.stops_name_to_id[end_stop_name];
                
                route_controller.queryShortestPathByCost(start_stop_id, end_stop_id);
                closeSession();

            } else if (option == "4") {
                cout << "=====| 推荐路线 |=====" << endl;
                string start_stop_name, second_stop_name ,third_stop_name, end_stop_name;
                int start_stop_id, second_stop_id, third_stop_id, end_stop_id;
                cout << "输入起始站: ";
                cin >> start_stop_name;
                cout << "输入第二站: ";
                cin >> second_stop_name;
                cout << "输入第三站: ";
                cin >> third_stop_name;
                cout << "输入终点站: ";
                cin >> end_stop_name;

                // Convert string to int
                if (all_of(start_stop_name.begin(), start_stop_name.end(), ::isdigit)) start_stop_id = stoi(start_stop_name);
                else start_stop_id = route_controller.stops_name_to_id[start_stop_name];
                if (all_of(second_stop_name.begin(), second_stop_name.end(), ::isdigit)) second_stop_id = stoi(second_stop_name);
                else second_stop_id = route_controller.stops_name_to_id[second_stop_name];
                if (all_of(third_stop_name.begin(), third_stop_name.end(), ::isdigit)) third_stop_id = stoi(third_stop_name);
                else third_stop_id = route_controller.stops_name_to_id[third_stop_name];
                if (all_of(end_stop_name.begin(), end_stop_name.end(), ::isdigit)) end_stop_id = stoi(end_stop_name);
                else end_stop_id = route_controller.stops_name_to_id[end_stop_name];
                
                route_controller.recommendRoute(start_stop_id, second_stop_id, third_stop_id,end_stop_id);
                closeSession();
                
            } else if (option == "5") {
                /**
                 * @brief Manager menu
                 * 1. Display All Stop              
                 * TODO: 2. Add Stop                      
                 * TODO: 3. Delete Stop                   
                 * 4. Reload System                 
                 * TODO: 5. Add Route                   
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

                    //} else if (option == 5) {

                    //} else if (option == 6) {

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
             * TODO: 4. Check Recommended Route     
             * 5. Exit                        
             */
            showVisitorMenu();
            cin >> option;
            if (option == "1") {
                cout << "=====| 查询 |=====" << endl;
                cout << "输入线路ID: ";
                int route_id; cin >> route_id;
                route_controller.displayRouteById(route_id);
                closeSession();

            } else if (option == "2") {
                cout << "=====| 最短时间路线 |=====" << endl;
                string start_stop_name, end_stop_name;
                int start_stop_id, end_stop_id;
                cout << "输入起始站: ";
                cin >> start_stop_name;
                cout << "输入终点站: ";
                cin >> end_stop_name;

                // Convert string to int
                if (all_of(start_stop_name.begin(), start_stop_name.end(), ::isdigit)) start_stop_id = stoi(start_stop_name);
                else start_stop_id = route_controller.stops_name_to_id[start_stop_name];
                if (all_of(end_stop_name.begin(), end_stop_name.end(), ::isdigit)) end_stop_id = stoi(end_stop_name);
                else end_stop_id = route_controller.stops_name_to_id[end_stop_name];
                
                route_controller.queryShortestPathByTime(start_stop_id, end_stop_id);
                closeSession();

            } else if (option == "3") {
                cout << "=====| 最小花费路线 |=====" << endl;
                string start_stop_name, end_stop_name;
                int start_stop_id, end_stop_id;
                cout << "输入起始站: ";
                cin >> start_stop_name;
                cout << "输入终点站: ";
                cin >> end_stop_name;

                // Convert string to int
                if (all_of(start_stop_name.begin(), start_stop_name.end(), ::isdigit)) start_stop_id = stoi(start_stop_name);
                else start_stop_id = route_controller.stops_name_to_id[start_stop_name];
                if (all_of(end_stop_name.begin(), end_stop_name.end(), ::isdigit)) end_stop_id = stoi(end_stop_name);
                else end_stop_id = route_controller.stops_name_to_id[end_stop_name];
                
                route_controller.queryShortestPathByCost(start_stop_id, end_stop_id);
                closeSession();

            } else if (option == "4") {
                cout << "=====| 推荐路线 |=====" << endl;
                string start_stop_name, second_stop_name ,third_stop_name, end_stop_name;
                int start_stop_id, second_stop_id, third_stop_id, end_stop_id;
                cout << "输入起始站: ";
                cin >> start_stop_name;
                cout << "输入第二站: ";
                cin >> second_stop_name;
                cout << "输入第三站: ";
                cin >> third_stop_name;
                cout << "输入终点站: ";
                cin >> end_stop_name;

                // Convert string to int
                if (all_of(start_stop_name.begin(), start_stop_name.end(), ::isdigit)) start_stop_id = stoi(start_stop_name);
                else start_stop_id = route_controller.stops_name_to_id[start_stop_name];
                if (all_of(second_stop_name.begin(), second_stop_name.end(), ::isdigit)) second_stop_id = stoi(second_stop_name);
                else second_stop_id = route_controller.stops_name_to_id[second_stop_name];
                if (all_of(third_stop_name.begin(), third_stop_name.end(), ::isdigit)) third_stop_id = stoi(third_stop_name);
                else third_stop_id = route_controller.stops_name_to_id[third_stop_name];
                if (all_of(end_stop_name.begin(), end_stop_name.end(), ::isdigit)) end_stop_id = stoi(end_stop_name);
                else end_stop_id = route_controller.stops_name_to_id[end_stop_name];
                
                route_controller.recommendRoute(start_stop_id, second_stop_id, third_stop_id,end_stop_id);
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