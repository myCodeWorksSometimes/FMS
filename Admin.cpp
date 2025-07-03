#include "Admin.h"
#include "FileHandler.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>

using namespace std;

Admin::Admin(string uname) : User(uname, "Admin") {}

void Admin::showMenu() {
    int choice = 0;
    while (choice != 5) {
        Utils::clearScreen();

        cout << "\033[1;36m--- \033[1;33mAdmin Dashboard (" << username << ")\033[1;36m ---\033[0m\n"
             << "\033[1;34m1.\033[0m Add Employee\n"
             << "\033[1;34m2.\033[0m Remove Employee\n"
             << "\033[1;34m3.\033[0m View All Employees\n"
             << "\033[1;34m4.\033[0m View System Activity Logs\n"
             << "\033[1;34m5.\033[0m Logout\n"
             << "\033[1;36m---------------------------------\033[0m\n"
             << "\033[1;37mEnter your choice:\033[0m ";

        cin >> choice;

        switch (choice) {
            case 1: addEmployee(); break;
            case 2: removeEmployee(); break;
            case 3: viewAllEmployees(); break;
            case 4: viewActivityLogs(); break;
            case 5: break;
            default: cout << "\033[1;31mInvalid choice. Please try again.\n\033[0m ";
        }
        if (choice != 5) Utils::pause();
    }
}

void Admin::addEmployee() {
    auto users = FileHandler::readCredentials();
    string new_user, new_pass, new_role;
    cout << "\033[1;33mEnter new employee username:\033[0m "; cin >> new_user;

    for (const auto& user : users) {
        if (user.username == new_user) {
            cout << "\033[1;31mUsername already exists.\033[0m\n";
            return;
        }
    }
    
    cout << "\033[1;33mEnter password:\033[0m "; cin >> new_pass;
    cout << "\033[1;33mEnter role (Manager, Chef, Sales):\033[0m  "; cin >> new_role;

    if (new_role != "Manager" && new_role != "Chef" && new_role != "Sales") {
        cout << "\033[1;31mInvalid role specified.\033[0m\n";
        return;
    }

    users.push_back({new_user, new_pass, new_role});
    FileHandler::writeCredentials(users);
    FileHandler::logActivity(username, role, "Added employee: " + new_user + " (" + new_role + ")");
    cout << "\033[1;32mEmployee added successfully!\033[0m\n";
}

void Admin::removeEmployee() {
    auto users = FileHandler::readCredentials();
    string user_to_remove;
    cout << "\033[1;33mEnter username of employee to remove:\033[0m "; cin >> user_to_remove;

    if (user_to_remove == "admin" || user_to_remove == this->username) {
        cout << "\033[1;31mCannot remove the main admin or yourself.\033[0m\n";
        return;
    }

    vector<UserCredentials> updated_users;
    bool found = false;
    for (const auto& user : users) {
        if (user.username == user_to_remove && user.role != "Admin") {
            found = true;
        } else {
            updated_users.push_back(user);
        }
    }

    if (found) {
        FileHandler::writeCredentials(updated_users);
        FileHandler::logActivity(username, role, "Removed employee: " + user_to_remove);
        cout << "\033[1;32mEmployee removed successfully.\033[0m\n";
    } else {
        cout << "\033[1;31mEmployee not found or is an Admin.\033[0m\n";
    }
}

void Admin::viewAllEmployees() {
    auto users = FileHandler::readCredentials();
    cout << "\n\033[1;36m--- Current Employee Records ---\n"
         << "--------------------------------\033[0m\n";
    for (const auto& user : users) {
        cout << "\033[1;33mUsername:\033[0m " << setw(15) << left << user.username
             << "\033[1;33mRole:\033[0m " << user.role << "\n";
    }
    cout << "\033[1;36m--------------------------------\033[0m\n";
}

void Admin::viewActivityLogs() {
    auto logs = FileHandler::readActivityLog();
    cout << "\n\033[1;36m--- System Activity Log ---\n"
         << "---------------------------\033[0m\n";
    if (logs.empty()) {
        cout << "\033[1;33mLog file is empty.\033[0m\n";
    } else {
        for (const auto& log_entry : logs) {
            cout << "\033[1;37m" << log_entry << "\033[0m\n";
        }
    }
    cout << "\033[1;36m---------------------------\033[0m\n";
}