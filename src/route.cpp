#include "route.h"
#include <queue>
#include <limits>
#include <algorithm>

Route::Route() {}

void Route::addStop(int id, const std::string& name) {
    stops.emplace(id, Stop(id, name));
}

void Route::addConnection(int startId, int endId, int distance) {
    Stop* startStop = getStop(startId);
    Stop* endStop = getStop(endId);
    if (startStop && endStop) {
        startStop->addNeighbor(endStop, distance);
    }
}

Stop* Route::getStop(int id) {
    auto it = stops.find(id);
    if (it != stops.end()) {
        return &(it->second);
    }
    return nullptr;
}

std::vector<Stop*> Route::getStops() const {
    std::vector<Stop*> stopList;
    for (const auto& pair : stops) {
        stopList.push_back(const_cast<Stop*>(&pair.second));
    }
    return stopList;
}

std::vector<Stop*> Route::findShortestPath(int startId, int endId) {
    Stop* startStop = getStop(startId);
    Stop* endStop = getStop(endId);

    if (!startStop || !endStop) {
        return {};
    }

    std::unordered_map<Stop*, int> distances;
    std::unordered_map<Stop*, Stop*> previous;
    std::priority_queue<std::pair<int, Stop*>, std::vector<std::pair<int, Stop*>>, std::greater<>> queue;

    for (auto stop : getStops()) {
        distances[stop] = std::numeric_limits<int>::max();
        previous[stop] = nullptr;
    }

    distances[startStop] = 0;
    queue.push(std::make_pair(0, startStop));

    while (!queue.empty()) {
        Stop* currentStop = queue.top().second;
        queue.pop();

        if (currentStop == endStop) break;

        for (const auto& neighbor : currentStop->getNeighbors()) {
            int alt = distances[currentStop] + neighbor.second;
            if (alt < distances[neighbor.first]) {
                distances[neighbor.first] = alt;
                previous[neighbor.first] = currentStop;
                queue.push(std::make_pair(alt, neighbor.first));
            }
        }
    }

    std::vector<Stop*> path;
    for (Stop* at = endStop; at != nullptr; at = previous[at]) {
        path.push_back(at);
    }
    std::reverse(path.begin(), path.end());

    return path;
}
