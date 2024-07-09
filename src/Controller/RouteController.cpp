/**
 * File: Controller/RouteController.cpp
 * Date: 2024.07.07
 * Author: xiangxiangking
 */

#include "RouteController.h"

/**
 * @brief Add an arc to the route information
 * @param route_id
 * @param start_stop_id
 * @param end_stop_id
 * @param cost
 * @param fare
 * TODO: Make code more readable
 */

void RouteController::addArc(int route_id, int start_stop_id, int end_stop_id, float cost, float fare) {
    ArcNode* arc1 = new ArcNode(start_stop_id, end_stop_id, cost, fare, route_id);
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
    ArcNode* arc2 = new ArcNode(end_stop_id, start_stop_id, cost, fare, route_id);
    route_information.push_back(*arc2);
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

void RouteController::reloadRouteInformation(const string& stop_file_path, const string& route_file_path) {
    for (auto& stop : stops_map)
        delete stop.second;
        route_information.clear();
        stops_map.clear();
    
    loadRouteInformation(stop_file_path, route_file_path);
    displayAllStops();
    int num_of_routes = route_information.back().route_id;
    for (int i = 0; i < num_of_routes; i++) {
        displayRouteById(i);
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
    for (ArcNode arc : route_information) {
        if (arc.route_id == route_id) {
            found = true;
            cout << "Route ID: " << route_id
                 << " From " << stops_map[arc.tail_index]->stop_name 
                 << " (ID: " << arc.tail_index << ")"
                 << " to " << stops_map[arc.head_index]->stop_name
                 << " (ID: "<< arc.head_index << ")"
                 << " with cost: " << arc.cost
                 << " Fare: " << arc.fare << endl;
        }
    }

    if (!found) {
        cout << "No route found with ID: " << route_id << endl;
    }
}

/**
 * @brief Query the shortest path by time
 * Find the shortest path by time using Dijkstra's algorithm
 * @param start_stop_id
 * @param end_stop_id
 * TODO: Add transfer count
 */
void RouteController::queryShortestPathByTime(int start_stop_id, int end_stop_id) {
    unordered_map<int, float> dist; // distance from start_stop_id
    unordered_map<int, int> prev; // previous stop
    unordered_map<int, int> route_id_at_stop; // route_id used to reach each stop

    // initialize distances and previous stops
    for (const auto& stop : stops_map) {
        dist[stop.first] = std::numeric_limits<float>::max();
        prev[stop.first] = -1;
        route_id_at_stop[stop.first] = -1;
    }
    dist[start_stop_id] = 0;

    // dijkstra's algorithm
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
                route_id_at_stop[v] = arc->route_id;
                pq.push(v);
            }
            arc = arc->tail_link;
        }
    }

    // print result
    if (dist[end_stop_id] == numeric_limits<float>::max()) {
        cout << "No path found from " << start_stop_id << " to " << end_stop_id << endl;
    } else {
        cout << "Shortest time path from " << start_stop_id << " to " << end_stop_id << " with cost " << dist[end_stop_id] << endl;

        vector<int> path;
        for (int at = end_stop_id; at != -1; at = prev[at]) {
            path.push_back(at);
        }
        reverse(path.begin(), path.end());

        // Calculate transfer count
        int transfer_count = 0;
        for (size_t i = 1; i < path.size(); ++i) {
            if (route_id_at_stop[path[i]] != route_id_at_stop[path[i - 1]]) {
                transfer_count++;
            }
        }

        // Print path and transfer count
        for (int stop : path) {
            cout << stop << " ";
            if (stop != path.back()) {
                cout << "-> ";
            }
        }
        cout << endl;
        cout << "Total transfers: " << transfer_count << endl;
    }
}

/**
 * @brief Query the shortest path by cost
 * Find the shortest path by time using Dijkstra's algorithm
 * It is the same of previous one
 * @param start_stop_id
 * @param end_stop_id
 * TODO: Add transfer count, Make code readable
 */
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

/**
 * @brief Delete a stop
 * @param stop_id
 */
void RouteController::deleteStop(int stop_id) {
    if (stops_map.find(stop_id) == stops_map.end()) {
        cout << "Stop ID " << stop_id << " not found." << endl;
        return;
    }

    VexNode* stop = stops_map[stop_id];
    unordered_map<int, vector<ArcNode*>> out_arcs_by_route;
    unordered_map<int, vector<ArcNode*>> in_arcs_by_route;

    // Collect all outgoing and incoming arcs grouped by route_id
    ArcNode* arc = stop->first_out;
    while (arc) {
        out_arcs_by_route[arc->route_id].push_back(arc);
        arc = arc->tail_link;
    }

    arc = stop->first_in;
    while (arc) {
        in_arcs_by_route[arc->route_id].push_back(arc);
        arc = arc->head_link;
    }

    // Reconnect arcs for each route_id
    for (const auto& pair : out_arcs_by_route) {
        int route_id = pair.first;
        auto& out_arcs = pair.second;

        if (in_arcs_by_route.find(route_id) != in_arcs_by_route.end()) {
            auto& in_arcs = in_arcs_by_route[route_id];
            for (ArcNode* in_arc : in_arcs) {
                for (ArcNode* out_arc : out_arcs) {
                    ArcNode* new_arc = new ArcNode(in_arc->tail_index, out_arc->head_index, in_arc->cost + out_arc->cost, in_arc->fare + out_arc->fare, route_id);
                    if (stops_map.find(in_arc->tail_index) != stops_map.end()) {
                        VexNode* tail_stop = stops_map[in_arc->tail_index];
                        new_arc->tail_link = tail_stop->first_out;
                        tail_stop->first_out = new_arc;
                    }
                    if (stops_map.find(out_arc->head_index) != stops_map.end()) {
                        VexNode* head_stop = stops_map[out_arc->head_index];
                        new_arc->head_link = head_stop->first_in;
                        head_stop->first_in = new_arc;
                    }
                    route_information.push_back(*new_arc);
                }
            }
        }
    }

    // Remove arcs related to stop_id
    for (auto& pair : stops_map) {
        VexNode* node = pair.second;

        // Remove outgoing arcs
        ArcNode* prev_arc = nullptr;
        arc = node->first_out;
        while (arc) {
            if (arc->head_index == stop_id) {
                if (prev_arc) {
                    prev_arc->tail_link = arc->tail_link;
                } else {
                    node->first_out = arc->tail_link;
                }
                delete arc;
                arc = (prev_arc) ? prev_arc->tail_link : node->first_out;
            } else {
                prev_arc = arc;
                arc = arc->tail_link;
            }
        }

        // Remove incoming arcs
        prev_arc = nullptr;
        arc = node->first_in;
        while (arc) {
            if (arc->tail_index == stop_id) {
                if (prev_arc) {
                    prev_arc->head_link = arc->head_link;
                } else {
                    node->first_in = arc->head_link;
                }
                delete arc;
                arc = (prev_arc) ? prev_arc->head_link : node->first_in;
            } else {
                prev_arc = arc;
                arc = arc->head_link;
            }
        }
    }

    // Remove the stop from stops_map
    stops_map.erase(stop_id);
    delete stop;
    cout << "Stop ID " << stop_id << " deleted successfully." << endl;
}
