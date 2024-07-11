/**
 * @brief: Controller/RouteController.cpp
 * @date: 2024.07.07
 * @author: Nulla
 */

#include "RouteController.h"
using namespace std;

/**
 * @brief Add an arc to the route information
 * @details Add an arc to the route information undirectly
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

/**
 * @brief Load route information from files
 * @param stop_file_path, route_file_path
 */
void RouteController::loadRouteInformation(const string& stop_file_path, const string& route_file_path) {
    ifstream stop_file(stop_file_path);
    if (!stop_file.is_open()) {
        cerr << "错误，无法打开文件 " << stop_file_path << endl;
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
        stops_name_to_id[stop_name] = stoi(stop_id_str);
    }

    ifstream route_file(route_file_path);
    if (!route_file.is_open()) {
        cerr << "错误，无法打开文件 " << route_file_path << endl;
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

/**
 * @brief Delete the origin data and reload the file
 * @param stop_file_path, route_file_path
 */
void RouteController::reloadRouteInformation(const string& stop_file_path, const string& route_file_path) {
    // Clear stops_map
    for (auto& pair : stops_map) {
        delete pair.second;
    }
    stops_map.clear(); // Clear map

    // Clear route_information
    route_information.clear();

    loadRouteInformation(stop_file_path, route_file_path);
    displayAllStops();
    int num_of_routes = route_information.back().route_id;
    for (int i = 0; i < num_of_routes; i++) {
        displayRouteById(i);
    }
}

void RouteController::displayAllStops() {
    cout << "站点ID, " << "站点名称" << endl;
    for (auto& stop : stops_map) {
        cout <<stop.second->stop_id << " " << stop.second->stop_name << endl;
    }
}

void RouteController::displayRouteById(int route_id) {
    cout << "显示路线ID: " << route_id << endl;
    bool found = false;
    for (ArcNode arc : route_information) {
        if (arc.route_id == route_id) {
            found = true;
            cout << "路线ID: " << route_id
                 << " 从 " << stops_map[arc.tail_index]->stop_name 
                 << " (ID: " << arc.tail_index << ")"
                 << " 到 " << stops_map[arc.head_index]->stop_name
                 << " (ID: "<< arc.head_index << ")"
                 << " 时间: " << arc.cost << " 分"
                 << " 票价: " << arc.fare << " 角" << endl;
        }
    }

    if (!found) {
        cout << "没有此路线: " << route_id << endl;
    }
}

/**
 * @brief Query the shortest path by time
 * @details the shortest path by time using Dijkstra's algorithm
 */
void RouteController::queryShortestPathByTime(int start_stop_id, int end_stop_id) {
    unordered_map<int, float> dist;  // distance from start_stop_id
    unordered_map<int, int> prev;    // previous stop
    vector<ArcNode*> edges_in_path;  // vector to store the edges in the path

    // Initialize distances and previous stops
    for (const auto& stop : stops_map) {
        dist[stop.first] = std::numeric_limits<float>::max();
        prev[stop.first] = -1;
    }
    dist[start_stop_id] = 0;

    // Dijkstra's algorithm
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

    // Restore path and store edges
    vector<int> path;
    for (int at = end_stop_id; at != -1; at = prev[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());

    // Reconstruct edges_in_path based on the restored path
    for (size_t i = 1; i < path.size(); ++i) {
        VexNode* u_node = stops_map[path[i - 1]];
        ArcNode* arc = u_node->first_out;
        while (arc) {
            if (arc->tail_index == path[i]) {
                edges_in_path.push_back(arc);
                break;
            }
            arc = arc->tail_link;
        }
    }

    // Print result
    if (dist[end_stop_id] == std::numeric_limits<float>::max()) {
        cout << "没有路线从 " << start_stop_id << " 到 " << end_stop_id << endl;
    } else {
        cout << "最短时间路线从 " << start_stop_id << " 到 " << end_stop_id << "，时间花费 " << dist[end_stop_id] << " 分" << endl;

        int transfer_count = 0;
        int current_route_id = -1;

        for (size_t i = 0; i < path.size(); ++i) {
            cout << stops_map[path[i]]->stop_name << "(" << path[i] << ")";
            if (i > 0 && edges_in_path[i - 1]->route_id != current_route_id) {
                if (current_route_id != -1) {
                    cout << " [转乘]";
                    transfer_count++;
                }
                current_route_id = edges_in_path[i - 1]->route_id;
            }
            if (i < path.size() - 1) {
                cout << " -> ";
            }
        }
        cout << endl;
        cout << "转乘数: " << transfer_count << endl;
    }
}


/**
 * @brief Query the shortest path by cost
 * Find the shortest path by cost using Dijkstra's algorithm
 * @param start_stop_id
 * @param end_stop_id
 */
void RouteController::queryShortestPathByCost(int start_stop_id, int end_stop_id) {
    unordered_map<int, float> fare; // fare from start_stop_id
    unordered_map<int, int> prev;   // previous stop
    vector<ArcNode*> edges_in_path; // vector to store the edges in the path

    // Initialize fares and previous stops
    for (const auto& stop : stops_map) {
        fare[stop.first] = std::numeric_limits<float>::max();
        prev[stop.first] = -1;
    }
    fare[start_stop_id] = 0;

    // Dijkstra's algorithm
    auto cmp = [&fare](int left, int right) { return fare[left] > fare[right]; };
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
            float alt = fare[u] + arc->fare;
            if (alt < fare[v]) {
                fare[v] = alt;
                prev[v] = u;
                pq.push(v);
            }
            arc = arc->tail_link;
        }
    }

    // Restore path and store edges
    vector<int> path;
    for (int at = end_stop_id; at != -1; at = prev[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());

    // Reconstruct edges_in_path based on the restored path
    for (size_t i = 1; i < path.size(); ++i) {
        VexNode* u_node = stops_map[path[i - 1]];
        ArcNode* arc = u_node->first_out;
        while (arc) {
            if (arc->tail_index == path[i]) {
                edges_in_path.push_back(arc);
                break;
            }
            arc = arc->tail_link;
        }
    }

    // Print result
    if (fare[end_stop_id] == std::numeric_limits<float>::max()) {
        cout << "没有路线从 " << start_stop_id << " 到 " << end_stop_id << endl;
    } else {
        cout << "最短花费路线从 " << start_stop_id << " 到 " << end_stop_id << "，花费 " << fare[end_stop_id] << " 角" << endl;

        int transfer_count = 0;
        int current_route_id = -1;

        for (size_t i = 0; i < path.size(); ++i) {
            cout << stops_map[path[i]]->stop_name << "(" << path[i] << ")";
            if (i > 0 && edges_in_path[i - 1]->route_id != current_route_id) {
                if (current_route_id != -1) {
                    cout << "[转乘]";
                    transfer_count++;
                }
                current_route_id = edges_in_path[i - 1]->route_id;
            }
            if (i < path.size() - 1) {
                cout << " -> ";
            }
        }
        cout << endl;
        cout << "转乘数: " << transfer_count << endl;
    }
}

/**
 * @brief Recommend the shortest route passing through specified intermediate stops
 */
void RouteController::recommendRoute(int stop1_id, int stop2_id, int stop3_id, int stop4_id) {
    // Step 1: Find shortest path from start to intermediate_stop1
    queryShortestPathByTime(stop1_id, stop2_id);
    cout << "从" << stops_map[stop1_id]->stop_name << "到" << stops_map[stop2_id]->stop_name << "的最短路径为：" << endl;
    
    // Step 2: Find shortest path from intermediate_stop1 to intermediate_stop2
    queryShortestPathByTime(stop2_id, stop3_id);
    cout << "从" << stops_map[stop2_id]->stop_name << "到" << stops_map[stop3_id]->stop_name << "的最短路径为：" << endl;
    
    // Step 3: Find shortest path from intermediate_stop2 to destination
    queryShortestPathByTime(stop3_id, stop4_id);
    cout << "从" << stops_map[stop3_id]->stop_name << "到" << stops_map[stop4_id]->stop_name << "的最短路径为：" << endl;
}

void RouteController::deleteStop(int stop_id) {
    auto it = stops_map.find(stop_id);
    if (it != stops_map.end()) {
        VexNode* node = it->second;

        // Collect incoming and outgoing arcs
        vector<ArcNode*> incoming_arcs;
        ArcNode* arc = node->first_in;
        while (arc) {
            incoming_arcs.push_back(arc);
            arc = arc->head_link;
        }

        vector<ArcNode*> outgoing_arcs;
        arc = node->first_out;
        while (arc) {
            outgoing_arcs.push_back(arc);
            arc = arc->tail_link;
        }
        
        // Reconnect incoming and outgoing arcs
        for (ArcNode* in_arc : incoming_arcs) {
            for (ArcNode* out_arc : outgoing_arcs) {
                if (in_arc->route_id == out_arc->route_id) {
                    ArcNode* new_arc = new ArcNode(
                        in_arc->route_id, 
                        in_arc->tail_index, 
                        out_arc->head_index, 
                        in_arc->cost + out_arc->cost, 
                        in_arc->fare + out_arc->fare
                    );

                    // Update links
                    new_arc->head_link = out_arc;
                    new_arc->tail_link = in_arc;

                    if (in_arc->head_link == out_arc) {
                        in_arc->head_link = new_arc;
                    }
                    if (out_arc->tail_link == in_arc) {
                        out_arc->tail_link = new_arc;
                    }
                }
            }
        }

        // Remove all arcs involving the stop
        auto arc_it = route_information.begin();
        while (arc_it != route_information.end()) {
            ArcNode* arc = *arc_it;
            if (arc->head_index == stop_id || arc->tail_index == stop_id) {
                delete arc; // Free the memory if dynamically allocated
                arc_it = route_information.erase(arc_it); // Erase and move to the next element
            } else {
                ++arc_it;
            }
        }

        // Remove the stop from the stops_map and delete the node
        stops_map.erase(it);
        stops_name_to_id.erase(node->stop_name);
        delete node;

        cout << "站点已删除: " << stop_id << endl;
    } else {
        cerr << "错误，站点ID不存在: " << stop_id << endl;
    }
}

void RouteController::addStop(int route_id, int stop_id, const string& stop_name, float cost, float fare) {
    // Check if stop ID already exists
    if (stops_map.find(stop_id) != stops_map.end()) {
        cerr << "错误，站点ID已存在: " << stop_id << endl;
        return;
    }

    // Create a new stop
    VexNode* new_stop = new VexNode(stop_id, stop_name);

    // Add the stop to the stops_map and stops_name_to_id
    stops_map[stop_id] = new_stop;
    stops_name_to_id[stop_name] = stop_id;

    ArcNode* last_arc = nullptr;
    int max_tail_index = -1;

    for (const auto& arc : route_information) {
        if (arc.route_id == route_id && arc.tail_index > max_tail_index) {
            max_tail_index = arc.tail_index;
            last_arc = const_cast<ArcNode*>(&arc);
        }
    }

    // If a last stop is found, add an arc from the last stop to the new stop
    if (last_arc != nullptr) {
        addArc(route_id, last_arc->head_index, stop_id, cost, fare);
    } else {
        // Handle the case where the route has no stops yet
        cout << "注意：该路线目前没有站点，新站点已添加，但未连接到任何现有站点。" << endl;
    }

    cout << "站点已添加: " << stop_name << " (ID: " << stop_id << ")" << endl;
}

//void RouteController::deleteRoute(int route_id) {
//    vector<ArcNode*> arcs_to_delete;
//
//    for (auto& pair : stops_map) {
//        VexNode* node = pair.second;
//
//        // Delete outgoing arcs
//        ArcNode* prev_arc = nullptr;
//        ArcNode* arc = node->first_out;
//        while (arc) {
//            if (arc->route_id == route_id) {
//                if (prev_arc) {
//                    prev_arc->tail_link = arc->tail_link;
//                } else {
//                    node->first_out = arc->tail_link;
//                }
//                arcs_to_delete.push_back(arc);
//            }
//            prev_arc = arc;
//            arc = arc->tail_link;
//        }
//
//        // Delete incoming arcs
//        prev_arc = nullptr;
//        arc = node->first_in;
//        while (arc) {
//            if (arc->route_id == route_id) {
//                if (prev_arc) {
//                    prev_arc->head_link = arc->head_link;
//                } else {
//                    node->first_in = arc->head_link;
//                }
//                arcs_to_delete.push_back(arc);
//            }
//            prev_arc = arc;
//            arc = arc->head_link;
//        }
//    }
//
//    for (ArcNode* arc : arcs_to_delete) {
//        delete arc;
//    }
//
//    cout << "路线已删除: " << route_id << endl;
//}