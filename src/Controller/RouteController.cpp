/**
 * File: Controller/RouteController.cpp
 * Date: 2024.07.07
 * Author: xiangxiangking
 */

#include "RouteController.h"

void RouteController::addArc(int route_id, int start_stop_id, int end_stop_id, float cost, float fare) {
    ArcNode* arc1 = new ArcNode(route_id, end_stop_id, cost, fare);
    if (stops_map.find(start_stop_id) != stops_map.end()) {
        VexNode* start_stop = stops_map[start_stop_id];
        arc1->tail_link = start_stop->first_out;
        start_stop->first_out = arc1;
    }

    if (stops_map.find(end_stop_id) != stops_map.end()) {
        VexNode* end_stop = stops_map[end_stop_id];
        arc1->head_link = end_stop->first_in;
        end_stop->first_in = arc1;
    }

    // making it undirected
    ArcNode* arc2 = new ArcNode(route_id, start_stop_id, cost, fare);
    if (stops_map.find(end_stop_id) != stops_map.end()) {
        VexNode* end_stop = stops_map[end_stop_id];
        arc2->tail_link = end_stop->first_out;
        end_stop->first_out = arc2;
    }

    if (stops_map.find(start_stop_id) != stops_map.end()) {
        VexNode* start_stop = stops_map[start_stop_id];
        arc2->head_link = start_stop->first_in;
        start_stop->first_in = arc2;
    }
}
void RouteController::loadRouteInformation(const string& stop_file_path, const string& route_file_path) {
    ifstream stop_file(stop_file_path);
    if (!stop_file.is_open()) {
        cerr << "Error: Failed to open stop file " << stop_file_path << endl;
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
        string stop_id_str, route_id, stop_name;
        getline(ss, stop_id_str, ',');
        getline(ss, stop_name, ',');

        VexNode* vertex = new VexNode(stoi(stop_id_str), stop_name);
        stops_map[vertex->stop_id] = vertex;
    }

    ifstream route_file(route_file_path);
    if (!route_file.is_open()) {
        cerr << "Error: Failed to open route file " << route_file_path << endl;
        return;
    }

    header = true;
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

        int route_id = stoi(columns[0]);
        int start_stop_id = stoi(columns[1]);
        int end_stop_id = stoi(columns[2]);
        float cost = stof(columns[3]);
        float fare = stof(columns[4]);

        addArc(route_id, start_stop_id, end_stop_id, cost, fare);
    }
}
void RouteController::displayAllStops() {
    cout << "stop_id,\t" << "stop_name" << endl;
    for (auto& stop : stops_map) {
        cout <<stop.second->stop_id << "\t\t" << stop.second->stop_name << endl;
    }
}
void RouteController::displayRouteById(int route_id) {
    cout << "Displaying route with ID: " << route_id << endl;
    bool found = false;

    // Find the starting stop
    for (const auto& stop_pair : stops_map) {
        VexNode* stop = stop_pair.second;
        ArcNode* arc = stop->first_out;

        while (arc) {
            if (arc->head_index == route_id) {
                found = true;
                int current_stop_id = stop->stop_id;
                cout << "From stop " << stop->stop_name 
                     << "\t(ID: " << current_stop_id << ") ";

                // Continue through the route
                while (arc && arc->head_index == route_id) {
                    int next_stop_id = arc->tail_index;
                    cout << "to stop " << stops_map[next_stop_id]->stop_name 
                         << "\t(ID: " << next_stop_id << ") "
                         << "with cost: " << arc->cost 
                         << " and fare: " << arc->fare << endl;

                    current_stop_id = next_stop_id;
                    arc = stops_map[current_stop_id]->first_out;
                }
                break;
            }
            arc = arc->tail_link;
        }
        if (found) break;
    }

    if (!found) {
        cout << "No route found with ID: " << route_id << endl;
    }
}


void RouteController::queryShortestPathByTime(int start_stop_id, int end_stop_id) {
    unordered_map<int, float> dist;
    unordered_map<int, int> prev;

    for (const auto& stop : stops_map) {
        dist[stop.first] = std::numeric_limits<float>::max();
        prev[stop.first] = -1;
    }
    dist[start_stop_id] = 0;

    auto cmp = [&dist](int left, int right) { return dist[left] > dist[right]; };
    std::priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);
    pq.push(start_stop_id);

    while (!pq.empty()) {
        int u = pq.top();
        pq.pop();

        if (u == end_stop_id) break;

        VexNode* u_node = stops_map[u];
        ArcNode* arc = u_node->first_out;
        while (arc) {
            int v = arc->tail_index;
            float alt = dist[u] + arc->cost;
            if (alt < dist[v]) {
                dist[v] = alt;
                prev[v] = u;
                pq.push(v);
            }
            arc = arc->tail_link;
        }
    }

    if (dist[end_stop_id] == numeric_limits<float>::max()) {
        cout << "No path found from " << start_stop_id << " to " << end_stop_id << endl;
    } else {
        cout << "Shortest time path from " << start_stop_id << " to " << end_stop_id << " with cost " << dist[end_stop_id] << endl;
        vector<int> path;
        for (int at = end_stop_id; at != -1; at = prev[at]) {
            path.push_back(at);
        }
        reverse(path.begin(), path.end());
        for (int stop : path) {
            cout << stop << " ";
            if (stop != path.back()) {
                cout << "-> ";
            }
        }
        cout << endl;
    }
}
void RouteController::queryShortestPathByCost(int start_stop_id, int end_stop_id) {
    unordered_map<int, float> fare;
    unordered_map<int, int> prev;

    for (const auto& stop : stops_map) {
        fare[stop.first] = numeric_limits<float>::max();
        prev[stop.first] = -1;
    }
    fare[start_stop_id] = 0;

    auto cmp = [&fare](int left, int right) { return fare[left] > fare[right]; };
    priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);
    pq.push(start_stop_id);

    while (!pq.empty()) {
        int u = pq.top();
        pq.pop();

        if (u == end_stop_id) break;

        VexNode* u_node = stops_map[u];
        ArcNode* arc = u_node->first_out;
        while (arc) {
            int v = arc->tail_index;
            float alt = fare[u] + arc->fare;
            if (alt < fare[v]) {
                fare[v] = alt;
                prev[v] = u;
                pq.push(v);
            }
            arc = arc->tail_link;
        }
    }

    if (fare[end_stop_id] == numeric_limits<float>::max()) {
        cout << "No path found from " << start_stop_id << " to " << end_stop_id << endl;
    } else {
        cout << "Shortest cost path from " << start_stop_id << " to " << end_stop_id << " with fare " << fare[end_stop_id] << endl;
        vector<int> path;
        for (int at = end_stop_id; at != -1; at = prev[at]) {
            path.push_back(at);
        }
        reverse(path.begin(), path.end());
        for (int stop : path) {
            cout << stop << " ";
            if (stop != path.back()) {
                cout << "-> ";
            }
        }
        cout << endl;
    }
}