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
#include <unordered_set>
#include <list>
#include <iostream>
#include <climits>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <limits>
#include <queue>

using namespace std;

struct ArcNode;

struct VexNode {
    int stop_id;
    string stop_name;
    ArcNode *first_in, *first_out;
    VexNode(int id, string name) :
    stop_id(id), stop_name(name),
    first_in(nullptr), first_out(nullptr) {}
};

struct ArcNode {
    int route_id;
    // index of two verticess
    int head_index, tail_index;
    // weight of the edge
    float cost, fare;
    // pointer to the next ArcNode
    ArcNode *head_link, *tail_link;
    ArcNode(int h, int t, float c, float f, int route_id) :
    head_index(h), tail_index(t), cost(c), fare(f),
    head_link(nullptr), tail_link(nullptr),
    route_id(route_id) {}
};

class RouteController {
    public:
    // The adjancey list of the graph
    unordered_map<int, VexNode*> stops_map;
    unordered_map<string, int> stops_name_to_id;
    vector<ArcNode> route_information;

    void addArc(int route_id, int start_stop_id, int end_stop_id, float cost, float fare);
    void loadRouteInformation(const string& stop_file_path, const string& route_file_path);
    void reloadRouteInformation(const string& stop_file_path, const string& route_file_path);
    void displayAllStops();
    void displayRouteById(int route_id);
    void queryShortestPathByTime(int start_stop_id, int end_stop_id);
    void queryShortestPathByCost(int start_stop_id, int end_stop_id);
    void recommendRoute(int start_stop_id, int intermediate_stop1_id, int intermediate_stop2_id, int destination_stop_id);
    void deleteStop(int stop_id);
    //TODO: Add the function to change the information of the stop
    //TODO: Add the function to delete or add the stop
};

#endif