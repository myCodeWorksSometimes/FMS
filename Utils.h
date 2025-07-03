#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

using namespace std;

namespace Utils {
    void clearScreen();
    void pause();
    string getCurrentTimestamp();
    vector<string> split(const string& s, char delimiter);
}

#endif // UTILS_H