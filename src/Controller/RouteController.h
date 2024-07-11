/**
 * @brief: Controller/RouteController.h
 * @date: 2024.07.07
 * @author: Nulla
 */

#ifndef ROUTE_CONTROLLER_H
#define ROUTE_CONTROLLER_H

#include <bits/stdc++.h>
using namespace std;

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
    int head_index, tail_index;
    float cost, fare;
    ArcNode *head_link, *tail_link;
    ArcNode(int h, int t, float c, float f, int route_id) :
    head_index(h), tail_index(t), cost(c), fare(f),
    head_link(nullptr), tail_link(nullptr),
    route_id(route_id) {}
};

class RouteController {
    public:
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
    void addStop(int route_id, int stop_id, const string& stop_name, float cost, float fare);
    //void deleteRoute(int route_id);
};

#endif