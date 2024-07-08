/**
 * File: Controller/RouteController.h
 * Date: 2024.07.07
 * Author: Nulla
 */

#ifndef ROUTE_CONTROLLER_H
#define ROUTE_CONTROLLER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <list>
#include <iostream>
#include <climits>

struct ArcNode;

struct VexNode {
    int stop_id;
    std::string stop_name;
    ArcNode* first_in;
    ArcNode* first_out;
    VexNode(int id, const std::string& name) : stop_id(id), stop_name(name), first_in(nullptr), first_out(nullptr) {}
};

struct ArcNode {
    // index of two verticess
    int head_index;
    int tail_index;

    // weight of the edge
    float cost;
    float fare;

    // pointer to the next ArcNode
    ArcNode* head_link;
    ArcNode* tail_link;

    ArcNode(int h, int t, float c, float f) :
    head_index(h), tail_index(t), cost(c), fare(f),
    head_link(nullptr), tail_link(nullptr) {}
};

class RouteController {
    public:
    // The adjancey list of the graph
    std::unordered_map<int, VexNode*> stops_map;
    void loadRouteInformation(const std::string& stop_file_path, const std::string& route_file_path);
    void displayRouteInformation();
    void addArc(int route_id, int start_stop_id, int end_stop_id, float cost, float fare);
    void queryShortestPathByTime(int start_stop_id, int end_stop_id);
    void queryShortestPathByCost(int start_stop_id, int end_stop_id);

};

#endif // ROUTE_CONTROLLER_H
