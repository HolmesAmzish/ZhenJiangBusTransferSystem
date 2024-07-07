/**
 * File: Controller/RouteController.cpp
 * Date: 2024.07.07
 * Author: xiangxiangking
 */

#include "RouteController.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <limits>
#include <algorithm>

using namespace std;

void RouteController::addArc(int route_id, int start_stop_id, int end_stop_id, float cost, float fare) {
    // Return error if invalid stop_id
    if (stops.find(start_stop_id) == stops.end()) {
        cerr << "Error: Start stop ID " << start_stop_id << " not found" << endl;
        return;
    }
    if (stops.find(end_stop_id) == stops.end()) {
        cerr << "Error: End stop ID " << end_stop_id << " not found" << endl;
        return;
    }

    ArcNode* arc = new ArcNode(route_id, end_stop_id, cost, fare);
    arc->head_link = stops[end_stop_id]->first_in;
    stops[end_stop_id]->first_in = arc;

    arc->tail_link = stops[start_stop_id]->first_out;
    stops[start_stop_id]->first_out = arc;
}

void RouteController::loadRouteInformation(const string& stop_file_path, const string& route_file_path) {
    // Load stops.csv
    ifstream stop_file(stop_file_path);
    if (!stop_file.is_open()) {
        cerr << "Error: Failed to open route file " << route_file_path << endl;
        return;
    }

    string line;
    bool header = true;
    while (getline(stop_file, line)) {
        if (header) {
            header = false;
            continue;
        }

        stringstream ss(line);
        string stop_id_str, stop_name;
        getline(ss, stop_id_str, ',');
        getline(ss, stop_name, ',');

        VexNode* vertex = new VexNode(stoi(stop_id_str), stop_name);
        stops_alist.push_back(vertex);
    }

    /**
     * Load 
     */
    ifstream route_file(route_file_path);
    if (!route_file.is_open()) {
        cerr << "Error: Failed to open route file " << route_file_path << endl;
        return;
    }

    string line;
    bool header = true;
    while (getline(route_file, line)) {
        if (header) {
            header = false;
            continue;
        }

        stringstream ss(line);

        string columns[5];
        for (int i = 0; i < 5; i++) {
            getline(ss, columns[i], ',');
        }

        // Convert string to specific data type
        int route_id = stoi(columns[0]);
        int start_stop_id = stoi(columns[1]);
        int end_stop_id = stoi(columns[2]);
        float cost = stof(columns[3]);
        float fare = stof(columns[4]);

        addArc(route_id, start_stop_id, end_stop_id, cost, fare);
        cout << "Adding arc: " << route_id << ", " << start_stop_id << ", " << end_stop_id << ", " << cost << ", " << fare << endl;
    }
}

//void RouteController::reloadRoute(const string& file_path) {
//    for (auto& stop : stops) {
//        delete stop.second;
//    }
//    stops.clear();
//    stop_list.clear();
//    loadRoute(file_path);
//}

//void RouteController::showRoute(int route_id) {
//    cout << "Route ID: " << route_id << endl;
//    for (auto& stop : stop_list) {
//        ArcNode* arc = stop->first_out;
//        while (arc) {
//            if (arc->head_index == route_id) {
//                cout << "Stop " << stop->stop_name << " to " << stops[arc->tail_index]->stop_name 
//                     << " - Cost: " << arc->cost << ", Fare: " << arc->fare << endl;
//            }
//            arc = arc->tail_link;
//        }
//    }
//}
//
//void RouteController::showAllStops() {
//    for (auto& stop : stops) {
//        cout << "Stop ID: " << stop.first << ", Name: " << stop.second->stop_name << endl;
//    }
//}

//void RouteController::queryShortestPathByTime(int start_stop_id, int end_stop_id) {
//    unordered_map<int, float> dist;
//    unordered_map<int, int> prev;
//    for (const auto& stop : stops) {
//        dist[stop.first] = numeric_limits<float>::max();
//        prev[stop.first] = -1;
//    }
//    dist[start_stop_id] = 0;
//
//    auto cmp = [&dist](int left, int right) { return dist[left] > dist[right]; };
//    priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);
//    pq.push(start_stop_id);
//
//    while (!pq.empty()) {
//        int u = pq.top();
//        pq.pop();
//
//        if (u == end_stop_id) break;
//
//        VexNode* u_node = stops[u];
//        ArcNode* arc = u_node->first_out;
//        while (arc) {
//            int v = arc->tail_index;
//            float alt = dist[u] + arc->cost;
//            if (alt < dist[v]) {
//                dist[v] = alt;
//                prev[v] = u;
//                pq.push(v);
//            }
//            arc = arc->tail_link;
//        }
//    }
//
//    if (dist[end_stop_id] == numeric_limits<float>::max()) {
//        cout << "No path found from " << start_stop_id << " to " << end_stop_id << endl;
//    } else {
//        cout << "Shortest time path from " << start_stop_id << " to " << end_stop_id << " with cost " << dist[end_stop_id] << endl;
//        vector<int> path;
//        for (int at = end_stop_id; at != -1; at = prev[at]) {
//            path.push_back(at);
//        }
//        reverse(path.begin(), path.end());
//        for (int stop : path) {
//            cout << stop << " ";
//        }
//        cout << endl;
//    }
//}

//void RouteController::queryShortestPathByCost(int start_stop_id, int end_stop_id) {
//    unordered_map<int, float> fare;
//    unordered_map<int, int> prev;
//    for (const auto& stop : stops) {
//        fare[stop.first] = numeric_limits<float>::max();
//        prev[stop.first] = -1;
//    }
//    fare[start_stop_id] = 0;
//
//    auto cmp = [&fare](int left, int right) { return fare[left] > fare[right]; };
//    priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);
//    pq.push(start_stop_id);
//
//    while (!pq.empty()) {
//        int u = pq.top();
//        pq.pop();
//
//        if (u == end_stop_id) break;
//
//        VexNode* u_node = stops[u];
//        ArcNode* arc = u_node->first_out;
//        while (arc) {
//            int v = arc->tail_index;
//            float alt = fare[u] + arc->fare;
//            if (alt < fare[v]) {
//                fare[v] = alt;
//                prev[v] = u;
//                pq.push(v);
//            }
//            arc = arc->tail_link;
//        }
//    }
//
//    if (fare[end_stop_id] == numeric_limits<float>::max()) {
//        cout << "No path found from " << start_stop_id << " to " << end_stop_id << endl;
//    } else {
//        cout << "Shortest cost path from " << start_stop_id << " to " << end_stop_id << " with fare " << fare[end_stop_id] << endl;
//        vector<int> path;
//        for (int at = end_stop_id; at != -1; at = prev[at]) {
//            path.push_back(at);
//        }
//        reverse(path.begin(), path.end());
//        for (int stop : path) {
//            cout << stop << " ";
//        }
//        cout << endl;
//    }
//}

//void RouteController::deleteNode(int stop_id) {
//    if (stops.find(stop_id) == stops.end()) return;
//    
//    VexNode* stop = stops[stop_id];
//
//    // Remove all arcs related to this stop
//    ArcNode* arc = stop->first_in;
//    while (arc) {
//        ArcNode* temp = arc;
//        arc = arc->head_link;
//        delete temp;
//    }
//    arc = stop->first_out;
//    while (arc) {
//        ArcNode* temp = arc;
//        arc = arc->tail_link;
//        delete temp;
//    }
//
//    stops.erase(stop_id);
//    delete stop;
//}
//
//void RouteController::addNode(int stop_id, const string& stop_name) {
//    if (stops.find(stop_id) == stops.end()) {
//        VexNode* new_stop = new VexNode(stop_id, stop_name);
//        stops[stop_id] = new_stop;
//        stop_list.push_back(new_stop);
//    }
//}