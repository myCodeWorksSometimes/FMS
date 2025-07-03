#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include <string>

using namespace std;

struct UserCredentials {
    string username;
    string password;
    string role;
};

struct MenuItem {
    int id;
    string name;
    double price;
    int stock;
    string category;
};

struct Recipe {
    int itemId;
    string ingredients;
    string steps;
};

struct ManagerRequest {
    string name;
    double price;
    int initial_stock;
    string category;
};

#endif // DATASTRUCTURES_H