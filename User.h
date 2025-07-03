#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

class User {
protected:
    string username;
    string role;

public:
    User(string uname, string urole);
    virtual ~User() = default;
    virtual void showMenu() = 0;
    string getUsername() const;
    string getRole() const;
};

#endif // USER_H