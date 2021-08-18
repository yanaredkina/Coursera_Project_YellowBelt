#include "date.h"

#include <iomanip>
#include <sstream>
#include <vector>

using namespace std;

Date::Date() : Year(0), Month(0), Day(0) {
}

Date::Date(int year, int month, int day) {
    Year = year;
    if (month < 1 || month > 12) {
        throw runtime_error("Month value is invalid");
    }
    Month = month;
    if (day < 1 || day > 31) {
        throw runtime_error("Day value is invalid");
    }
    Day = day;
}

int Date::GetYear() const {
    return Year;
};
int Date::GetMonth() const {
    return Month;
};
int Date::GetDay() const {
    return Day;
}

ostream& operator<<(ostream& stream, const Date& date) {
  stream << setw(4) << setfill('0') << date.GetYear() <<
      "-" << setw(2) << setfill('0') << date.GetMonth() <<
      "-" << setw(2) << setfill('0') << date.GetDay();
  return stream;
}


bool operator<(const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth() == rhs.GetMonth()) {
            return lhs.GetDay() < rhs.GetDay();
        } else {
            return lhs.GetMonth() < rhs.GetMonth();
        }
    } else {
        return lhs.GetYear() < rhs.GetYear();
    }
}

bool operator<=(const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth() == rhs.GetMonth()) {
            return lhs.GetDay() <= rhs.GetDay();
        } else {
            return lhs.GetMonth() <= rhs.GetMonth();
        }
    } else {
        return lhs.GetYear() <= rhs.GetYear();
    }
}

bool operator>(const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth() == rhs.GetMonth()) {
            return lhs.GetDay() > rhs.GetDay();
        } else {
            return lhs.GetMonth() > rhs.GetMonth();
        }
    } else {
        return lhs.GetYear() > rhs.GetYear();
    }
}

bool operator>=(const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth() == rhs.GetMonth()) {
            return lhs.GetDay() >= rhs.GetDay();
        } else {
            return lhs.GetMonth() >= rhs.GetMonth();
        }
    } else {
        return lhs.GetYear() >= rhs.GetYear();
    }
}

bool operator==(const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth() == rhs.GetMonth()) {
            return lhs.GetDay() == rhs.GetDay();
        } else {
            return lhs.GetMonth() == rhs.GetMonth();
        }
    } else {
        return lhs.GetYear() == rhs.GetYear();
    }
}

bool operator!=(const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth() == rhs.GetMonth()) {
            return lhs.GetDay() != rhs.GetDay();
        } else {
            return lhs.GetMonth() != rhs.GetMonth();
        }
    } else {
        return lhs.GetYear() != rhs.GetYear();
    }
}

// bool dateComparator(const Date& lhs, const Date& rhs, string op) {
//     if (op == "<") {
//         return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} <
//             vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
//     } else if (op == "<=") {
//         return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} <=
//             vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
//     } else if (op == ">") {
//         return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} >
//             vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
//     } else if (op == ">=") {
//         return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} >=
//             vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
//     } else if (op == "==") {
//         return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} ==
//             vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
//     } else {
//         return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} !=
//             vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
//     }
// }

Date ParseDate(istream& date_stream) {
    while (!isdigit(date_stream.peek())) {
        date_stream.ignore(1);
    }
    bool ok = true;

    int year;
    ok = ok && (date_stream >> year);
    ok = ok && (date_stream.peek() == '-');
    date_stream.ignore(1);

    int month;
    ok = ok && (date_stream >> month);
    ok = ok && (date_stream.peek() == '-');
    date_stream.ignore(1);

    int day;
    ok = ok && (date_stream >> day);
    ok = ok && (date_stream.peek() == ' ' || date_stream.eof());

    if (!ok) {
        string errorInput;
        date_stream >> errorInput;
        throw runtime_error("Wrong date format: " + errorInput);
    }
    return {year, month, day};
}