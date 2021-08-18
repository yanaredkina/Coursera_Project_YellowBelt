#pragma once
#include "date.h"

#include <map>
#include <vector>
#include <string>
#include <functional>

using namespace std;

class Database {
private:
    map<Date,vector<string>> Events;
public:
    void Add(const Date& date, const string& event);
    int RemoveIf(function<bool(const Date& date, const string& event)>predicate);
    vector<string> FindIf(function<bool(const Date& date, const string& event)>predicate) const;
    string Last(const Date& date) const;
    ostream& Print(ostream& out) const;
    void DelEmptyValuesFromMap();
};
