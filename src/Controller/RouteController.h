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
    int stop_index;
    std::string stop_name;
    ArcNode* first_in;
    ArcNode* first_out;
    VexNode(int i, const std::string& name) : stop_index(i), stop_name(name), first_in(nullptr), first_out(nullptr) {}
};

struct ArcNode {
    // index of two vertices
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
private:
    // The adjancey list of the graph
    std::unordered_map<int, VexNode*> stops;
    std::vector<VexNode*> stop_list;

public:
    ~RouteController();
    void loadRoute(const std::string& file_path);
    void reloadRoute(const std::string& file_path);
    void showRoute(int route_id);
    void showAllStops();
    void queryShortestPath(int start_stop_id, int end_stop_id);
    void queryCheapestPath(int start_stop_id, int end_stop_id);
    void deleteNode(int stop_id);
    void addNode(int stop_id, const std::string& stop_name);
    void addArc(int route_id, int start_stop_id, int end_stop_id, float cost, float fare);
};

#endif // ROUTE_CONTROLLER_H
