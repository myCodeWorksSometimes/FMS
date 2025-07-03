#ifndef SALESEMPLOYEE_H
#define SALESEMPLOYEE_H

#include "User.h"

class SalesEmployee : public User {
public:
    SalesEmployee(string uname);
    void showMenu() override;
private:
    void takeCustomerOrder();
    void displayMenuInTable();
};

#endif // SALESEMPLOYEE_H