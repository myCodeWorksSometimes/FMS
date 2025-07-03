#ifndef MANAGER_H
#define MANAGER_H

#include "User.h"

class Manager : public User {
public:
    Manager(string uname);
    void showMenu() override;
private:
    void orderNewFoodItem();
    void increaseStock();
    void viewSalesReport();
};

#endif // MANAGER_Hs