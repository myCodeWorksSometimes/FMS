#include "FMS.h"
#include "FileHandler.h"
#include "Utils.h"
#include "Admin.h"
#include "Manager.h"
#include "Chef.h"
#include "SalesEmployee.h"
#include <iostream>

using namespace std;

FMS::FMS() : currentUser(nullptr) {}

FMS::~FMS() {
    delete currentUser;
}

void FMS::run() {
    while (true) {
        if (!currentUser) {
            showLoginScreen();
        }
        if (currentUser) {
            currentUser->showMenu();
            cout << "Logging out " << currentUser->getUsername() << "...\n";
            FileHandler::logActivity(currentUser->getUsername(), currentUser->getRole(), "Logged out");
            delete currentUser;
            currentUser = nullptr;
            Utils::pause();
        } else {
            break;
        }
    }
    cout << "Exiting Food Management System. Goodbye!\n";
}

void FMS::showLoginScreen() {
    while (true) {
        Utils::clearScreen();
        cout << "\033[1;36m"
             << "========================================\n"
             << "  Welcome to the Food Management System \033[1;36m\n"
             << "========================================\n\033[0m"
             << "\033[1;37mPlease log in.\033[0m\n\n";
        
        cout << "\033[1;32mUsername:\033[0m ";
        string username;
        cin >> username;
        cin.ignore();
        
        cout << "\033[1;32mPassword:\033[0m ";
        string password;
        cin >> password;
        cin.ignore();

        if (attemptLogin(username, password)) {
            FileHandler::logActivity(currentUser->getUsername(), currentUser->getRole(), "Logged in successfully");
            break;
        } else {
            cout << "\n\033[1;31mInvalid username or password.\033[0m\n"
                 << "\033[1;34m1.\033[0m Try again\n"
                 << "\033[1;34m2.\033[0m Exit\n"
                 << "\033[1;36mChoose an option:\033[0m ";

            int choice;
            cin >> choice;
            if (choice == 2) {
                currentUser = nullptr;
                break;
            }
        }
    }
}

bool FMS::attemptLogin(const string& username, const string& password) {
    auto users = FileHandler::readCredentials();
    for (const auto& user : users) {
        if (user.username == username && user.password == password) {
            if (user.role == "Admin" || user.role == "Admin\r") currentUser = new Admin(username);
            else if (user.role == "Manager" || user.role == "Manager\r") currentUser = new Manager(username);
            else if (user.role == "Chef" || user.role == "Chef\r") currentUser = new Chef(username);
            else if (user.role == "Sales" || user.role == "Sales\r") currentUser = new SalesEmployee(username);
            else return false;
            return true;
        }
    }
    return false;
}