#include "Utils.h"
#include <iostream>
#include <ctime>

using namespace std;

void Utils::clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void Utils::pause() {
    cout << "\nPress Enter to continue...";
    cin.ignore(10000, '\n');
    if (cin.peek() == '\n') cin.ignore();
    cin.get();
}

string Utils::getCurrentTimestamp() {
    time_t now = time(nullptr);
    char buf[80];
    struct tm timeinfo;
    #ifdef _WIN32
        localtime_s(&timeinfo, &now);
    #else
        localtime_r(&now, &timeinfo);
    #endif
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &timeinfo);
    return string(buf);
}

vector<string> Utils::split(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    string temp_s = s;
    size_t pos = 0;
    while ((pos = temp_s.find(delimiter)) != string::npos) {
        token = temp_s.substr(0, pos);
        tokens.push_back(token);
        temp_s.erase(0, pos + 1);
    }
    tokens.push_back(temp_s);
    return tokens;
}