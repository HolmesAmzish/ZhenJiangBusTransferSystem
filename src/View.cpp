/**
 * @brief View.cpp
 * @author Nulla
 * @date 2024-07-11
 * @description View
 */

#include "View.h"
using namespace std;

bool loginSession(UserController controller, string& username, string& password) {
    cout << "=====| 登录 |=====" << endl;
    cout << "输入用户名: ";
    cin >> username;
    cout << "密码: ";
    cin >> password;
    if (controller.login(username, password)) {
        return true;
    } else {
        system("clear");
        cout << "登录失败，错误的用户名或密码。" << endl;
    }
}

int convertNameToId(string name, RouteController& controller) {
    if (all_of(name.begin(), name.end(), ::isdigit))
        return stoi(name);
    else
        return controller.stops_name_to_id[name];
}

void queryBusRoute(RouteController& controller) {
    cout << "=====| 查询 |=====" << endl;
    cout << "输入线路ID: ";
    int route_id; cin >> route_id;
    controller.displayRouteById(route_id);
}

void findShortestPathByTime(RouteController& controller) {
    cout << "=====| 最短时间路径 |=====" << endl;
    string start_stop_name, end_stop_name;
    int start_stop_id, end_stop_id;
    cout << "输入起始站: ";
    cin >> start_stop_name;
    cout << "输入终点站: ";
    cin >> end_stop_name;
    start_stop_id = convertNameToId(start_stop_name, controller);
    end_stop_id = convertNameToId(end_stop_name, controller);
    controller.queryShortestPathByTime(start_stop_id, end_stop_id);
}

void findShortestPathByCost(RouteController& controller) {
    cout << "=====| 最小花费路径 |=====" << endl;
    string start_stop_name, end_stop_name;
    int start_stop_id, end_stop_id;
    cout << "输入起始站: ";
    cin >> start_stop_name;
    cout << "输入终点站: ";
    cin >> end_stop_name;
    start_stop_id = convertNameToId(start_stop_name, controller);
    end_stop_id = convertNameToId(end_stop_name, controller);
    controller.queryShortestPathByCost(start_stop_id, end_stop_id);
}

void checkRecommendRoute(RouteController& controller) {
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

    start_stop_id = convertNameToId(start_stop_name, controller);
    second_stop_id = convertNameToId(second_stop_name, controller);
    third_stop_id = convertNameToId(third_stop_name, controller);
    end_stop_id = convertNameToId(end_stop_name, controller);
    
    controller.recommendRoute(start_stop_id, second_stop_id, third_stop_id,end_stop_id);
}

void addStop(RouteController& controller) {
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
    controller.addStop(route_id, stop_id, stop_name, cost, fare);
}

void reinitialize(UserController& user_controller, RouteController& route_controller) {
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
}

void closeSession() {
    cout << "输入任意键以继续..." << endl;
    cin.ignore();
    cin.get();
    system("clear");
}

