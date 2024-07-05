/**
 * File: BusRoute.h
 * Date: 2024.07.05
 * Author: Nulla
 * Description: The definition of Bus Route
 */

#ifndef BUS_ROUTE_H
#define BUS_ROUTE_H

#include <string>
#include <vector>

class BusRoute {
public:
    std::string route_id;
    std::vector<std::string> stops;
    double fare;
    double travel_time;
};

#endif
