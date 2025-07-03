#include "Chef.h"
#include "FileHandler.h"
#include "Utils.h"
#include <iostream>

using namespace std;

Chef::Chef(string uname) : User(uname, "Chef") {}

void Chef::showMenu() {
    int choice = 0;
    while (choice != 4) {
        Utils::clearScreen();
        cout << "\033[1;36m--- \033[1;33mChef Dashboard (" << username << ")\033[1;36m ---\033[0m\n"
             << "\033[1;34m1.\033[0m Add Recipes for Manager's Requests\n"
             << "\033[1;34m2.\033[0m Edit Recipe for an Existing Item\n"
             << "\033[1;34m3.\033[0m View All Food Items and Recipes\n"
             << "\033[1;34m4.\033[0m Logout\n"
             << "\033[1;36m-------------------------------------\033[0m\n"
             << "\033[1;37mEnter your choice:\033[0m ";

        cin >> choice;
        
        switch(choice){
            case 1: addRecipesForNewItems(); break;
            case 2: editRecipe(); break;
            case 3: viewAllFoodItems(); break;
            case 4: break;
            default: cout << "\033[1;31mInvalid choice.\033[0m\n";
        }
        if (choice != 4) Utils::pause();
    }
}

int Chef::getNextMenuId(){
    auto menu = FileHandler::readMenu();
    int max_id = 0;
    for(const auto& item : menu){
        if(item.id > max_id) max_id = item.id;
    }
    return max_id + 1;
}

void Chef::addRecipesForNewItems() {
    auto requests = FileHandler::readRequests();
    if (requests.empty()) {
        cout << "\033[1;33mNo pending requests from the manager.\033[0m\n";
        return;
    }

    auto menu = FileHandler::readMenu();
    auto recipes = FileHandler::readRecipes();
    string ingredients, steps;

    int new_id = getNextMenuId();
    for (const auto& req : requests) {
        Utils::clearScreen();
        cout << "\033[1;36mProcessing request for new item:\033[0m " << req.name << "\n";
        cout << "\033[1;33mEnter ingredients (comma-separated):\033[0m ";
        cin.ignore();
        getline(cin, ingredients);
        cout << "\033[1;33mEnter recipe steps:\033[0m ";
        getline(cin, steps);

        // int new_id = getNextMenuId();
        menu.push_back({new_id, req.name, req.price, req.initial_stock, req.category});
        recipes.push_back({new_id, ingredients, steps});
        
        FileHandler::logActivity(username, role, "Added new item '" + req.name + "' to menu.");
        cout << "\033[1;32mItem '" << req.name << "' added to the menu with ID " << new_id << ".\033[0m\n";
        Utils::pause();
        new_id++;
    }
    
    FileHandler::writeMenu(menu);
    FileHandler::writeRecipes(recipes);
    FileHandler::writeRequests({}); // Clear requests file
}

void Chef::editRecipe() {
    auto menu = FileHandler::readMenu();
    auto recipes = FileHandler::readRecipes();

    cout << "\n\033[1;36m--- Food Items ---\033[0m\n";
    for(const auto& item : menu){
        cout << "\033[1;33mID:\033[0m " << item.id << ", \033[1;33mName:\033[0m " << item.name << "\n";
    }
    cout << "\033[1;36m------------------\033[0m\n";
    cout << "\033[1;37mEnter ID of item to edit recipe for:\033[0m ";
    int item_id;
    cin >> item_id;

    bool found = false;
    for (auto& recipe : recipes) {
        if (recipe.itemId == item_id) {
            cout << "\033[1;33mCurrent ingredients:\033[0m " << recipe.ingredients << "\n";
            cout << "\033[1;33mEnter new ingredients:\033[0m ";
            cin.ignore();
            getline(cin, recipe.ingredients);

            cout << "\033[1;33mCurrent steps:\033[0m " << recipe.steps << "\n";
            cout << "\033[1;33mEnter new steps:\033[0m ";
            getline(cin, recipe.steps);
            
            FileHandler::logActivity(username, role, "Edited recipe for item ID " + to_string(item_id));
            cout << "\033[1;32mRecipe updated.\033[0m\n";
            found = true;
            break;
        }
    }
    
    if (found) {
        FileHandler::writeRecipes(recipes);
    } else {
        cout << "\033[1;31mItem ID not found or has no recipe.\033[0m\n";
    }
}

void Chef::viewAllFoodItems() {
    auto menu = FileHandler::readMenu();
    auto recipes = FileHandler::readRecipes();

    cout << "\n\033[1;36m--- Full Menu & Recipe List ---\033[0m\n";
    for (const auto& item : menu) {
        cout << "\033[1;36m---------------------------------\033[0m\n"
             << "\033[1;33mID:\033[0m " << item.id << "\n"
             << "\033[1;33mName:\033[0m " << item.name << "\n"
             << "\033[1;33mStock:\033[0m " << item.stock << "\n";
        
        bool recipe_found = false;
        for (const auto& recipe : recipes) {
            if (recipe.itemId == item.id) {
                cout << "\033[1;33mRecipe:\033[0m " << recipe.ingredients << " -> " << recipe.steps << "\n";
                recipe_found = true;
                break;
            }
        }
        if (!recipe_found) {
            cout << "\033[1;31mRecipe:\033[0m Not available.\n";
        }
    }
    cout << "\033[1;36m---------------------------------\033[0m\n";
}