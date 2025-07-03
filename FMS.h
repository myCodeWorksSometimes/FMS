#ifndef FMS_H
#define FMS_H

#include "User.h"
#include <string>

using namespace std;

class FMS {
private:
    User* currentUser;
    void showLoginScreen();
    bool attemptLogin(const string& username, const string& password);

public:
    FMS();
    ~FMS();
    void run();
};

#endif // FMS_H