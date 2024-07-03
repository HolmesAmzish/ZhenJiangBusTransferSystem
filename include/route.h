#ifndef ROUTE_H
#define ROUTE_H

#include <vector>
#include <unordered_map>
#include "stop.h"

class Route {
public:
    Route();
    void addStop(int id, const std::string& name);
    void addConnection(int startId, int endId, int distance);
    Stop* getStop(int id);
    std::vector<Stop*> getStops() const;
    std::vector<Stop*> findShortestPath(int startId, int endId);

private:
    std::unordered_map<int, Stop> stops;
};

#endif // ROUTE_H
