#include "User.h"

using namespace std;

User::User(string uname, string urole) : username(uname), role(urole) {}

string User::getUsername() const {
    return username;
}

string User::getRole() const {
    return role;
}