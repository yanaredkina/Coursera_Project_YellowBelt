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

// int Database::RemoveIf(function<bool(const Date& date, const string& event)> predicate) {
//     int count = 0;
//     for (auto& item: EventsMapWithSet) {
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

int Database::RemoveIf(function<bool(const Date& date, const string& event)> predicate) {
    int count = 0;
    for (auto itM = EventsMapWithVector.begin(); itM != EventsMapWithVector.end();) {
        Date date = itM->first;
        auto iterForErase = stable_partition(itM->second.begin(), itM->second.end(), [date, predicate](string event) 
            {return !predicate(date, event);});
        itM->second.erase(iterForErase, itM->second.end());
        
        if (itM->second.empty()) {
            itM = EventsMapWithVector.erase(itM);
        } else {
            ++itM;
        }
        
        for (auto itS = EventsMapWithSet.at(date).begin(); itS != EventsMapWithSet.at(date).end();) {
            if (predicate(date, *itS)) {
                itS = EventsMapWithSet.at(date).erase(itS);
                ++count;
            } else {
                ++itS;
            }
        }

        if (EventsMapWithSet.at(date).empty()) {
            EventsMapWithSet.erase(date);
        }
        
    }
    return count;
}


// vector<string> Database::FindIf(function<bool(const Date& date, const string& event)>predicate) const {
//     vector<string> result;
//     stringstream stream;
//     for (auto item: EventsMapWithSet) {
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
    for (auto item: EventsMapWithVector) {
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
//     auto itS = EventsMapWithSet.upper_bound(date);
//     if (itS == EventsMapWithSet.begin()) {
//         throw invalid_argument("No entries");
//     } else {
//         Date lastDate = prev(itS)->first;
//         auto itV = EventsMapWithVector.at(lastDate).end();
//         while (EventsMapWithSet.at(lastDate).count(*prev(itV)) == 0) {
//             itV--;
//         }
//         stringstream stream;
//         stream << lastDate << " " << *prev(itV);
//         return stream.str();
//     }
// }

string Database::Last(const Date& date) const {
    auto itV = EventsMapWithVector.upper_bound(date);
    if (itV == EventsMapWithVector.begin()) {
        throw invalid_argument("No entries");
    } else {
        stringstream stream;
        stream << prev(itV)->first << " " << prev(itV)->second.back();
        return stream.str();
    }
}


// ostream& Database::Print(ostream& out) const {
//   for (const auto& item : EventsMapWithVector) {
//     for (const auto& event : item.second) {
//         if (EventsMapWithSet.count(item.first) > 0 && EventsMapWithSet.at(item.first).count(event) > 0) {
//             out << item.first << " " << event << endl;
//         }
//     }
//   }
//   return out;
// }

ostream& Database::Print(ostream& out) const {
  for (const auto& item : EventsMapWithVector) {
    for (const auto& event : item.second) {
        out << item.first << " " << event << endl;
        }
    }
  return out;
}

// void Database::DelEmptyValuesFromMap(){
//     for (auto it = EventsMapWithVector.begin(); it != EventsMapWithVector.end(); ) {
//         if(it->second.empty())
//             it = EventsMapWithVector.erase(it);
//         else
//             ++it;
//     }
// }