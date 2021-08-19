#include "database.h"
#include "date.h"

#include <iostream>
#include <algorithm>
#include <sstream>
#include <utility>

using namespace std;


void Database::Add(const Date& date, const string& event) {
    auto flag = EventsMapWithSet[date].insert(event);
    if (flag.second) {
        EventsMapWithVector[date].push_back(event);
    }
}

int Database::RemoveIf(function<bool(const Date& date, const string& event)> predicate) {
    int count = 0;
    for (auto& item: EventsMapWithSet) {
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
    for (auto item: EventsMapWithSet) {
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
    auto itS = EventsMapWithSet.upper_bound(date);
    if (itS == EventsMapWithSet.begin()) {
        throw invalid_argument("No entries");
    } else {
        Date lastDate = prev(itS)->first;
        auto itV = EventsMapWithVector.at(lastDate).end();
        while (EventsMapWithSet.at(lastDate).count(*prev(itV)) == 0) {
            itV--;
        }
        stringstream stream;
        stream << lastDate << " " << *prev(itV);
        return stream.str();
    }
}


ostream& Database::Print(ostream& out) const {
  for (const auto& item : EventsMapWithVector) {
    for (const auto& event : item.second) {
        if (EventsMapWithSet.count(item.first) > 0 && EventsMapWithSet.at(item.first).count(event) > 0) {
            out << item.first << " " << event << endl;
        }
    }
  }
  return out;
}

void Database::DelEmptyValuesFromMap(){
    for (auto it = EventsMapWithSet.begin(); it != EventsMapWithSet.end(); ) {
        if(it->second.empty())
            it = EventsMapWithSet.erase(it);
        else
            ++it;
    }
}