#ifndef USER_H
#define USER_H

#include <string>

class User {
public:
    User(int id, const std::string& name);
    int getId() const;
    const std::string& getName() const;

private:
    int id;
    std::string name;
};

#endif // USER_H
