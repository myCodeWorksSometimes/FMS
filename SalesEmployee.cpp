#include "SalesEmployee.h"
#include "FileHandler.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>

using namespace std;

SalesEmployee::SalesEmployee(string uname) : User(uname, "Sales") {}

void SalesEmployee::showMenu() {
    int choice = 0;
    while(choice != 2){
        Utils::clearScreen();
    cout << "\033[1;36m--- \033[1;33mSales Terminal (" << username << ")\033[1;36m ---\033[0m\n"
         << "\033[1;34m1.\033[0m Take New Customer Order\n"
         << "\033[1;34m2.\033[0m Logout\n"
         << "\033[1;36m-----------------------------\033[0m\n"
         << "\033[1;37mEnter your choice:\033[0m ";

        cin >> choice;

        switch(choice){
            case 1: takeCustomerOrder(); break;
            case 2: break;
            default: cout << "\033[1;31mInvalid choice.\033[0m\n";
        }
        if (choice != 2) Utils::pause();
    }
}

void SalesEmployee::displayMenuInTable() {
    auto menu = FileHandler::readMenu();
    cout << "\033[1;36m+----+----------------------+------------+----------+\n"
         << "| ID | Item Name            | Price      | In Stock |\n"
         << "+----+----------------------+------------+----------+\033[0m\n";
    if (menu.empty()) {
        cout << "\033[1;33m| No items available in the menu.                    |\033[0m\n";
    } else {
        for (const auto& item : menu) {
            if (item.stock > 0) {
                 cout << "| " << setw(2) << left << item.id
                      << " | " << setw(20) << item.name
                      << " | " << setw(10) << fixed << setprecision(2) << item.price
                      << " | " << setw(8) << item.stock << " |\n";
            }
        }
    }
    cout << "\033[1;36m+----+----------------------+------------+----------+\033[0m\n";
}

void SalesEmployee::takeCustomerOrder() {
    auto menu = FileHandler::readMenu();
    if(menu.empty()){
        cout << "\033[1;33mMenu is currently empty. Cannot take orders.\033[0m\n";
        return;
    }

    vector<MenuItem> cart;
    vector<int> quantities;
    int item_id = -1;

    while (true) {
        Utils::clearScreen();
        cout << "\033[1;36m--- Taking New Order ---\033[0m\n";
        displayMenuInTable();
        cout << "\n\033[1;33mEnter Item ID to add to order (or 0 to finish):\033[0m ";
        cin >> item_id;

        if (item_id == 0) break;

        MenuItem* selected_item = nullptr;
        for (auto& item : menu) {
            if (item.id == item_id) {
                selected_item = &item;
                break;
            }
        }
        
        if (selected_item && selected_item->stock > 0) {
            cout << "\033[1;33mEnter quantity for '\033[1;37m" << selected_item->name << "\033[1;33m':\033[0m ";
            int quantity;
            cin >> quantity;

            if (quantity > 0 && quantity <= selected_item->stock) {
                cart.push_back(*selected_item);
                quantities.push_back(quantity);
                selected_item->stock -= quantity;
                cout << "\033[1;32mAdded " << quantity << "x " << selected_item->name << " to the order.\033[0m\n";
            } else {
                cout << "\033[1;31mInvalid quantity or not enough stock.\033[0m\n";
            }
        } else {
            cout << "\033[1;31mInvalid Item ID or item is out of stock.\033[0m\n";
        }
        Utils::pause();
    }

    if (cart.empty()) {
        cout << "\033[1;33mOrder cancelled.\033[0m\n";
        return;
    }
    
    Utils::clearScreen();
    cout << "\033[1;36m--- Generating Invoice ---\033[0m\n";
    double total_bill = 0;
    cout << "\033[1;36m+----------------------+----------+------------+----------+\n"
         << "| Item Name            | Quantity | Unit Price | Total    |\n"
        << "+----------------------+----------+------------+----------+\033[0m\n";
    for(size_t i = 0; i < cart.size(); ++i){
        double item_total = cart[i].price * quantities[i];
        total_bill += item_total;
        cout << "| " << setw(20) << left << cart[i].name
             << " | " << setw(8) << quantities[i]
             << " | " << setw(10) << fixed << setprecision(2) << cart[i].price
             << " | " << setw(8) << item_total << " |\n";
        FileHandler::logSale(cart[i].name, quantities[i], cart[i].price);
    }
    cout << "\033[1;36m+----------------------+----------+------------+----------+\n"
        << "| \033[1;33mTOTAL BILL\033[1;36m" << setw(45) << right << total_bill << " |\n"
        << "+---------------------------------------------------------+\033[0m\n";
    
    FileHandler::writeMenu(menu);
    FileHandler::logActivity(username, role, "Processed an order with total bill " + to_string(total_bill));
}