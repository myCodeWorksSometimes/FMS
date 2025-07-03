#include "FileHandler.h"
#include "Utils.h"
#include <fstream>

using namespace std;

const string DATA_FOLDER        = "data/";
const string CREDENTIALS_FILE   = DATA_FOLDER + "credentials.txt";
const string MENU_FILE          = DATA_FOLDER + "menu.txt";
const string RECIPES_FILE       = DATA_FOLDER + "recipes.txt";
const string REQUESTS_FILE      = DATA_FOLDER + "requests.txt";
const string SALES_LOG_FILE     = DATA_FOLDER + "sales.txt";
const string ACTIVITY_LOG_FILE  = DATA_FOLDER + "activity_log.txt";

vector<UserCredentials> FileHandler::readCredentials() {
    vector<UserCredentials> users;
    ifstream file(CREDENTIALS_FILE);
    string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            if (line.empty()) continue;
            vector<string> parts = Utils::split(line, ',');
            if (parts.size() == 3) users.push_back({parts[0], parts[1], parts[2]});
        }
        file.close();
    }
    return users;
}

void FileHandler::writeCredentials(const vector<UserCredentials>& users) {
    ofstream file(CREDENTIALS_FILE, ios::trunc);
    if (file.is_open()) {
        for (const auto& user : users) {
            file << user.username << "," << user.password << "," << user.role << endl;
        }
        file.close();
    }
}

vector<MenuItem> FileHandler::readMenu() {
    vector<MenuItem> menu;
    ifstream file(MENU_FILE);
    string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            if (line.empty()) continue;
            vector<string> parts = Utils::split(line, '|');
            if (parts.size() == 5) {
                menu.push_back({stoi(parts[0]), parts[1], stod(parts[2]), stoi(parts[3]), parts[4]});
            }
        }
        file.close();
    }
    return menu;
}

void FileHandler::writeMenu(const vector<MenuItem>& menu) {
    ofstream file(MENU_FILE, ios::trunc);
    if (file.is_open()) {
        for (const auto& item : menu) {
            file << item.id << "|" << item.name << "|" << item.price << "|" << item.stock << "|" << item.category << endl;
        }
        file.close();
    }
}

vector<Recipe> FileHandler::readRecipes() {
    vector<Recipe> recipes;
    ifstream file(RECIPES_FILE);
    string line;
    if(file.is_open()){
        while(getline(file, line)){
            if(line.empty()) continue;
            vector<string> parts = Utils::split(line, '|');
            if(parts.size() == 3) recipes.push_back({stoi(parts[0]), parts[1], parts[2]});
        }
        file.close();
    }
    return recipes;
}

void FileHandler::writeRecipes(const vector<Recipe>& recipes){
    ofstream file(RECIPES_FILE, ios::trunc);
    if(file.is_open()){
        for(const auto& recipe : recipes){
            file << recipe.itemId << "|" << recipe.ingredients << "|" << recipe.steps << endl;
        }
        file.close();
    }
}

vector<ManagerRequest> FileHandler::readRequests(){
    vector<ManagerRequest> requests;
    ifstream file(REQUESTS_FILE);
    string line;
    if(file.is_open()){
        while(getline(file, line)){
            if(line.empty()) continue;
            vector<string> parts = Utils::split(line, '|');
            if(parts.size() == 4) requests.push_back({parts[0], stod(parts[1]), stoi(parts[2]), parts[3]});
        }
        file.close();
    }
    return requests;
}

void FileHandler::writeRequests(const vector<ManagerRequest>& requests){
    ofstream file(REQUESTS_FILE, ios::trunc);
    if(file.is_open()){
        for(const auto& req : requests){
            file << req.name << "|" << req.price << "|" << req.initial_stock << "|" << req.category << endl;
        }
        file.close();
    }
}

void FileHandler::logSale(const string& itemName, int quantity, double price) {
    ofstream file(SALES_LOG_FILE, ios::app);
    if (file.is_open()) {
        file << Utils::getCurrentTimestamp() << "|" << itemName << "|" << quantity << "|" << (price * quantity) << endl;
        file.close();
    }
}

void FileHandler::logActivity(const string& user, const string& role, const string& activity) {
    ofstream file(ACTIVITY_LOG_FILE, ios::app);
    if (file.is_open()) {
        file << Utils::getCurrentTimestamp() << " [" << role << ": " << user << "] - " << activity << endl;
        file.close();
    }
}

vector<string> FileHandler::readActivityLog() {
    vector<string> logs;
    ifstream file(ACTIVITY_LOG_FILE);
    string line;
    if (file.is_open()) {
        while(getline(file, line)) logs.push_back(line);
        file.close();
    }
    return logs;
}

vector<string> FileHandler::readSalesLog() {
    vector<string> logs;
    ifstream file(SALES_LOG_FILE);
    string line;
    if(file.is_open()){
        while(getline(file, line)) logs.push_back(line);
        file.close();
    }
    return logs;
}