#include "utils.h"

vector<string> utils::tokenize(const string &str, char delimiter) {
    vector<string> tokens;
    string token;
    if (str.length() == 0)
        return tokens;

    for (auto c: str) {
        if (c == delimiter) {
            tokens.push_back(token);
            token.clear();
        } else {
            token += c;
        }
    }
    tokens.push_back(token);

    return tokens;
}

void utils::report(const string &msg) {
    // output to current time
    time_t t = time(nullptr);
    struct tm *now = localtime(&t);
    date d;
    file << "[time " << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << "], " << "[date " << d << "] ---> " << msg << endl;
}

utils::utils() {
    file.open("report.txt", ios::app);
}
