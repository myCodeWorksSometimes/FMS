#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "DataStructures.h"
#include <vector>
#include <string>

using namespace std;

class FileHandler {
public:
    static vector<UserCredentials> readCredentials();
    static void writeCredentials(const vector<UserCredentials>& users);

    static vector<MenuItem> readMenu();
    static void writeMenu(const vector<MenuItem>& menu);
    
    static vector<Recipe> readRecipes();
    static void writeRecipes(const vector<Recipe>& recipes);
    
    static vector<ManagerRequest> readRequests();
    static void writeRequests(const vector<ManagerRequest>& requests);

    static void logSale(const string& itemName, int quantity, double price);
    static void logActivity(const string& user, const string& role, const string& activity);
    static vector<string> readActivityLog();
    static vector<string> readSalesLog();
};

#endif // FILEHANDLER_H