#include "database.h"
#include "date.h"

#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;


// void Database::Add(const Date& date, const string& event) {
//     if (EventsMapWithVector.count(date) == 0) {
//         EventsMapWithVector[date].push_back(event);
//     } else if (find(EventsMapWithVector.at(date).begin(), EventsMapWithVector.at(date).end(), event) == EventsMapWithVector.at(date).end()) {
//         EventsMapWithVector[date].push_back(event);
//     }
// }

void Database::Add(const Date& date, const string& event) {
    if (EventsMapWithVector.count(date) == 0) {
        EventsMapWithVector[date].push_back(event);
    } else if (find(EventsMapWithVector.at(date).begin(), EventsMapWithVector.at(date).end(), event) == EventsMapWithVector.at(date).end()) {
        EventsMapWithVector[date].push_back(event);
    }
    EventsMapWithSet[date].insert(event);
}

// int Database::RemoveIf(function<bool(const Date& date, const string& event)> predicate) {
//     int count = 0;
//     for (auto& item: EventsMapWithVector) {
//         for (auto it = item.second.begin(); it != item.second.end();) {
//             if (predicate(item.first, *it)) {
//                 it = item.second.erase(it);
//                 ++count;
//             } else {
//                 ++it;
//             }
//         }
//     }
//     DelEmptyValuesFromMap();
//     return count;
// }


// int Database::RemoveIf(function<bool(const Date& date, const string& event)> predicate) {
//     int count = 0;
//     for (auto& item: EventsMapWithVector) {
//         auto it = stable_partition(item.second.begin(), item.second.end(), predicate());
//         item.second.erase(it, item.second.end());
//     }
//     DelEmptyValuesFromMap();
//     return count;
// }

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

// vector<string> Database::FindIf(function<bool(const Date& date, const string& event)>predicate) const {
//     vector<string> result;
//     stringstream stream;
//     for (auto item: EventsMapWithVector) {
//         for (auto element : item.second) {
//             if (predicate(item.first, element)) {
//                 stream << item.first << " " << element;
//                 result.push_back(stream.str());
//                 stream.str("");
//             }
//         }
//     }
//     return result;
// }

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

// string Database::Last(const Date& date) const {
//     auto it = EventsMapWithVector.upper_bound(date);
//     if (it == EventsMapWithVector.begin() && it != EventsMapWithVector.end()) {
//         throw invalid_argument("No entries");
//     } else {
//         stringstream stream;
//         stream << prev(it)->first << " " << prev(it)->second.back();
//         return stream.str();
//     }
// }

string Database::Last(const Date& date) const {
    auto itS = EventsMapWithSet.upper_bound(date);
    if (itS == EventsMapWithSet.begin() && itS != EventsMapWithSet.end()) {
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

// ostream& Database::Print(ostream& out) const {
//   for (const auto& item : EventsMapWithVector) {
//     for (const auto& event : item.second) {
//       out << item.first << " " << event << endl;
//     }
//   }
//   return out;
// }

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