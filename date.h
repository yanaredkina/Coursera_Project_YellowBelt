#pragma once

#include <iostream>

using namespace std;

class Date {
private:
    int Year;
    int Month;
    int Day;
public:
    Date();
    Date(int year, int month, int day);
    
    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;
    
};

ostream& operator<<(ostream& stream, const Date& date);
bool operator<(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);
bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);

//bool dateComparator(const Date& lhs, const Date& rhs, string op);
Date ParseDate(istream& date_stream);