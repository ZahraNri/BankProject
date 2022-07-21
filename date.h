#ifndef DATE_H
#define DATE_H

#include <ctime>
#include <iostream>
using namespace std;

class date {
private:
    int day;
    int month;
    int year;

public:

    date(const string& d);
    date();
    date(int day, int month, int year);

    int getDay();
    void setDay(int d);
    int getMonth();
    void setMonth(int m);
    int getYear();
    void setYear(int y);
    string tostring() const;

    friend ostream &operator<<(ostream &os, const date &date);

};


#endif //DATE_H
