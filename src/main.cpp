#include "main.h"
#include <iostream>
#include <fstream>
#include <sstream>

void loadRoutes(Route& route, const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Failed to open " << fileName << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream stream(line);
        std::string field;
        int id, startId, endId, distance;
        std::string routeName, start, end;

        std::getline(stream, field, ','); id = std::stoi(field);
        std::getline(stream, field, ','); routeName = field;
        std::getline(stream, field, ','); start = field;
        std::getline(stream, field, ','); end = field;
        std::getline(stream, field, ','); distance = std::stoi(field);

        route.addStop(startId, start);
        route.addStop(endId, end);
        route.addConnection(startId, endId, distance);
    }
}

void loadUsers(User& user, const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Failed to open " << fileName << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream stream(line);
        std::string field;
        int id;
        std::string name;

        std::getline(stream, field, ','); id = std::stoi(field);
        std::getline(stream, field, ','); name = field;

        user = User(id, name);
    }
}

int main() {
    Route route;
    User user(0, "default"); // 默认用户信息

    loadRoutes(route, "data/routes.csv");
    loadUsers(user, "data/users.csv");

    Menu menu;
    menu.handleUserInput(route, user);

    return 0;
}
