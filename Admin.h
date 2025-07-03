#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"

class Admin : public User {
public:
    Admin(string uname);
    void showMenu() override;
private:
    void addEmployee();
    void removeEmployee();
    void viewAllEmployees();
    void viewActivityLogs();
};

#endif // ADMIN_H