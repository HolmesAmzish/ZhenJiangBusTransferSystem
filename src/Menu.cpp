/**
 * @brief: Menu.cpp
 * @date: 2024.07.06
 * @author: Nulla
 */

#include "Menu.h"
#include <iostream>
using namespace std;
void showLoginMenu() {
    cout << "+-----------| 登录页面 |------------+" << endl;
    cout << "| 1. 登录                           |" << endl;
    cout << "| 2. 退出                           |" << endl;
    cout << "+-----------------------------------+" << endl;
    cout << "输入选择: ";
}

void showAdminMenu() {
    cout << "+----------| 管理员页面  |----------+" << endl;
    cout << "| 1. 查询公交车路线                 |" << endl;
    cout << "| 2. 寻找最小花费路线               |" << endl;
    cout << "| 3. 寻找最短时间路线               |" << endl;
    cout << "| 4. 查询推荐旅游路线               |" << endl;
    cout << "| 5. 维护路线                       |" << endl;
    cout << "| 6. 退出                           |" << endl;
    cout << "+-----------------------------------+" << endl;
    cout << "输入选择: ";
}

void showManagerMenu() {
    cout << "+------------| 维护页面 |-----------+" << endl;
    cout << "| 1. 显示所有站点                   |" << endl;
    cout << "| 2. 添加站点                       |" << endl;
    cout << "| 3. 删除站点                       |" << endl;
    cout << "| 4. 重新初始化系统                 |" << endl;
    cout << "| 5. 返回                           |" << endl;
    cout << "+-----------------------------------+" << endl;
    cout << "输入选择: ";
}

void showVisitorMenu() {
    cout << "+-----------| 访客页面 |------------+" << endl;
    cout << "| 1. 查询公交车路线                 |" << endl;
    cout << "| 2. 寻找最小花费路线               |" << endl;
    cout << "| 3. 寻找最短时间路线               |" << endl;
    cout << "| 4. 查询推荐旅游路线               |" << endl;
    cout << "| 5. 退出                           |" << endl;
    cout << "+-----------------------------------+" << endl;
    cout << "输入选择: ";
}