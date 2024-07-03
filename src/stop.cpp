#include "stop.h"

Stop::Stop(int id, const std::string& name) : id(id), name(name) {}

int Stop::getId() const {
    return id;
}

const std::string& Stop::getName() const {
    return name;
}

const std::vector<std::pair<Stop*, int>>& Stop::getNeighbors() const {
    return neighbors;
}

void Stop::addNeighbor(Stop* neighbor, int distance) {
    neighbors.push_back(std::make_pair(neighbor, distance));
}
