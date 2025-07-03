#include "Manager.h"
#include "FileHandler.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>

using namespace std;

Manager::Manager(string uname) : User(uname, "Manager") {}

void Manager::showMenu() {
    int choice = 0;
    while (choice != 4) {
        Utils::clearScreen();
        cout << "\033[1;36m--- \033[1;33mManager Dashboard (" << username << ")\033[1;36m ---\033[0m\n"
             << "\033[1;34m1.\033[0m Order New Food Item for Menu\n"
             << "\033[1;34m2.\033[0m Increase Stock of Existing Item\n"
             << "\033[1;34m3.\033[0m View Sales Report\n"
             << "\033[1;34m4.\033[0m Logout\n"
             << "\033[1;36m-----------------------------------\033[0m\n"
             << "\033[1;37mEnter your choice:\033[0m ";

        cin >> choice;

        switch (choice) {
            case 1: orderNewFoodItem(); break;
            case 2: increaseStock(); break;
            case 3: viewSalesReport(); break;
            case 4: break;
            default: cout << "\033[1;31mInvalid choice.\033[0m\n";
        }
        if (choice != 4) Utils::pause();
    }
}

void Manager::orderNewFoodItem() {
    string name, category;
    double price;
    int quantity;

    cout << "\033[1;33mEnter new item name:\033[0m ";
    cin.ignore();
    getline(cin, name);
    cout << "\033[1;33mEnter price:\033[0m ";
    cin >> price;
    cout << "\033[1;33mEnter initial quantity:\033[0m ";
    cin >> quantity;
    cout << "\033[1;33mEnter category (e.g., Meal, Drink, Dessert):\033[0m ";
    cin >> category;

    while (category != "Meal" && category != "Drink" && category != "Dessert")
    {
        cout << "\033[1;31mInvalid category entered.\033[0m "
            << "\033[1;33mEnter either Meal, Drink or Dessert (case sensitive):\033[0m ";
        cin >> category;
    }    

    auto requests = FileHandler::readRequests();
    requests.push_back({name, price, quantity, category});
    FileHandler::writeRequests(requests);
    FileHandler::logActivity(username, role, "Requested new item: " + name);
    cout << "\033[1;32mRequest sent to Chef.\033[0m\n";
}

void Manager::increaseStock() {
    auto menu = FileHandler::readMenu();
    if (menu.empty()) {
        cout << "\033[1;33mMenu is empty. No items to restock.\033[0m\n";
        return;
    }

    cout << "\n\033[1;36m--- Current Menu Stock ---\033[0m\n";
    for(const auto& item : menu){
        cout << "\033[1;33mID:\033[0m " << item.id
             << ", \033[1;33mName:\033[0m " << item.name
             << ", \033[1;33mCurrent Stock:\033[0m " << item.stock << "\n";
    }
    cout << "\033[1;36m--------------------------\033[0m\n";

    int item_id, quantity;
    cout << "\033[1;33mEnter Item ID to restock:\033[0m ";
    cin >> item_id;
    
    bool found = false;
    for (auto& item : menu) {
        if (item.id == item_id) {
            cout << "\033[1;33mEnter quantity to add:\033[0m ";
            cin >> quantity;
            if (quantity > 0) {
                item.stock += quantity;
                FileHandler::logActivity(username, role, "Increased stock for item ID " + to_string(item.id) + " by " + to_string(quantity));
                cout << "\033[1;32mStock updated successfully.\033[0m\n";
            } else {
                cout << "\033[1;31mInvalid quantity.\033[0m\n";
            }
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "\033[1;31mItem ID not found.\033[0m\n";
    } else {
        FileHandler::writeMenu(menu);
    }
}

void Manager::viewSalesReport() {
    auto menu = FileHandler::readMenu();
    cout << "\n\033[1;36m--- Current Menu Stock ---\033[0m\n";
    for(const auto& item : menu){
        cout << "\033[1;33mID:\033[0m " << item.id
             << ", \033[1;33mName:\033[0m " << item.name
             << ", \033[1;33mCurrent Stock:\033[0m " << item.stock << "\n";
    }
    cout << "\033[1;36m--------------------------\033[0m\n";

    auto sales = FileHandler::readSalesLog();
    cout << "\n\033[1;36m--- Overall Sales Report ---\033[0m\n";
    if (sales.empty()) {
        cout << "\033[1;33mNo sales have been recorded yet.\033[0m\n";
        return;
    }

    double total_revenue = 0;
    int total_items_sold = 0;
    
    for(const auto& sale : sales) {
        auto parts = Utils::split(sale, '|');
        if(parts.size() == 4) {
            total_items_sold += stoi(parts[2]);
            total_revenue += stod(parts[3]);
        }
    }
    cout << "\033[1;33mTotal Items Sold:\033[0m " << total_items_sold << "\n";
    cout << "\033[1;33mTotal Revenue:\033[0m PKR " << fixed << setprecision(2) << total_revenue << "\n";
    cout << "\033[1;36m----------------------------\033[0m\n";
}