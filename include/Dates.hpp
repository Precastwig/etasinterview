#ifndef DATES
#define DATES

#include <iostream>
#include <string>
#include <vector>
#include <map>

class Dates {
public:
    static std::vector<std::string> get_month_strings() {
        return {
            "January",
            "February",
            "March",
            "April",
            "May",
            "June",
            "July",
            "August",
            "September",
            "October",
            "November",
            "December"
        };
    }

    static int get_days_in_month(const std::string month, bool leap_year) {
        if (m_day_month_map.count(month)) {
            int days = m_day_month_map.at(month);
            if (leap_year && month == "February") {
                days += 1;
            }
            return days;
        } else {
            std::cout << "ERROR\n";
            return 0;
        }
    }

private:
    static inline const std::map<std::string, int> m_day_month_map = {
        {"January", 31},
        {"February", 28},
        {"March", 31},
        {"April", 30},
        {"May", 31},
        {"June", 30},
        {"July", 31},
        {"August", 31},
        {"September", 30},
        {"October", 31},
        {"November", 30},
        {"December", 31},
    };
};

#endif
