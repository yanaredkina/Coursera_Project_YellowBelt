#include "database.h"
#include "date.h"

#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;


void Database::Add(const Date& date, const string& event) {
    if (Events.count(date) == 0) {
        Events[date].push_back(event);
    } else if (find(Events.at(date).begin(), Events.at(date).end(), event) == Events.at(date).end()) {
        Events[date].push_back(event);
    }
}

int Database::RemoveIf(function<bool(const Date& date, const string& event)> predicate) {
    int count = 0;
    for (auto& item: Events) {
        for (auto it = item.second.begin(); it != item.second.end();) {
            if (predicate(item.first, *it)) {
                it = item.second.erase(it);
                ++count;
            } else {
                ++it;
            }
        }
    }
    DelEmptyValuesFromMap();
    return count;
}

vector<string> Database::FindIf(function<bool(const Date& date, const string& event)>predicate) const {
    vector<string> result;
    stringstream stream;
    for (auto item: Events) {
        for (auto element : item.second) {
            if (predicate(item.first, element)) {
                stream << item.first << " " << element;
                result.push_back(stream.str());
                stream.str("");
            }
        }
    }
    return result;
}

string Database::Last(const Date& date) const {
    auto it = Events.upper_bound(date);
    if (it == Events.begin() && it != Events.end()) {
        throw invalid_argument("No entries");
    } else {
        stringstream stream;
        stream << prev(it)->first << " " << prev(it)->second.back();
        return stream.str();
    }
}

      
ostream& Database::Print(ostream& out) const {
  for (const auto& item : Events) {
    for (const auto& event : item.second) {
      out << item.first << " " << event << endl;
    }
  }
  return out;
}

void Database::DelEmptyValuesFromMap() {
    for (auto it = Events.begin(); it != Events.end(); ) {
        if(it->second.empty())
            it = Events.erase(it);
        else
            ++it;
    }
}