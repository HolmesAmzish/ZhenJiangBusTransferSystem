/**
 * File: Controller/UserController.cpp
 * Date: 2024.07.05
 * Author: Nulla
 * Description: Source file of User Module
 */

#include "UserController.h"

void UserController::loadUser(string file_path) {
    ifstream file(file_path);
    if (!file.is_open()) {
        cerr << "错误，无法打开文件 " << file_path << endl;
        return;
    }

    string line;
    bool header = true;
    while (getline(file, line)) {
        // Skip header line
        if (header) {
            header = false;
            continue;
        }

        stringstream ss(line);
        string username, password, is_admin_str;
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, is_admin_str, ',');

        bool is_admin = (is_admin_str == "true");
        User user = {username, password, is_admin};
        users[username] = user;
    }
    file.close();
}

void UserController::reloadUser(string file_path) {
    users.clear();
    cout << "正在从文件中读取信息，文件路径 " << file_path << endl;
    loadUser(file_path);
    for (auto it = users.begin(); it != users.end(); it++) {
        cout << "用户名: " << it->first 
        << ", 密码: " << it->second.password 
        << ", 管理员: " << it->second.isAdmin << endl;
    }
    cout << "用户信息已重新载入。" << endl;
}

bool UserController::login(string username, string password) {
    auto it = users.find(username);
    if (it != users.end() && password == it->second.password) {
        return true;
    }
    return false;
}

bool UserController::isAdmin(string username) {
    auto it = users.find(username);
    if (it != users.end()) {
        return it->second.isAdmin;
    }
    return false;
}
