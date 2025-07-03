#ifndef CHEF_H
#define CHEF_H

#include "User.h"

class Chef : public User {
public:
    Chef(string uname);
    void showMenu() override;
private:
    void addRecipesForNewItems();
    void editRecipe();
    void viewAllFoodItems();
    int getNextMenuId();
};

#endif // CHEF_H