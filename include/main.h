#ifndef MAIN_H
#define MAIN_H

#include "route.h"
#include "user.h"
#include "menu.h"

void loadRoutes(Route& route, const std::string& fileName);
void loadUsers(User& user, const std::string& fileName);

#endif // MAIN_H
