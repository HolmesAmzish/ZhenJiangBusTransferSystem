/**
 * File: Model/BusRoute.h
 * Date: 2024.07.05
 * Author: Nulla
 * Description: The definition of Bus Route
 */

#ifndef BUS_ROUTE_H
#define BUS_ROUTE_H

#include <string>
#include <vector>
#include <unordered_map>
#include <list>

struct BusStop {
    int stop_id;
    
};

class BusRouteGraph {
public:
    void addNode(std::string stop_id, std::string stop_name);
    void addEdge(std::string start, std::string destination, double cost, double travel_time);
    void loadStops(std::string stops_file);
    void loadRoutes(std::string routes_file);

    Node* getNode(const std::string& stop_id);
    void displayGraph() const;

private:
    std::unordered_map<std::string, Node> nodes;
};

#endif // BUS_ROUTE_H