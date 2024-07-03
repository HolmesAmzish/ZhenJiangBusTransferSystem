#ifndef STOP_H
#define STOP_H

#include <string>
#include <vector>
#include <utility>

class Stop {
public:
    Stop(int id, const std::string& name);
    int getId() const;
    const std::string& getName() const;
    const std::vector<std::pair<Stop*, int>>& getNeighbors() const;
    void addNeighbor(Stop* neighbor, int distance);

private:
    int id;
    std::string name;
    std::vector<std::pair<Stop*, int>> neighbors;
};

#endif // STOP_H
