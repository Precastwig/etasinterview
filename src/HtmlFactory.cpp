#include "../include/HtmlFactory.hpp"
#include "../include/Dates.hpp"
#include <cmath>
#include <iostream>
#include <string>

void HtmlFactory::write_html_preamble(std::ofstream& file_stream) {
    if (!file_stream.is_open()) {
        std::cout << "File stream not open!";
        return;
    }
    file_stream << "<!DOCTYPE html><html><head><link rel=\"stylesheet\" href=\"calendar.css\"></head><body>\n";
}

void HtmlFactory::write_html_postamble(std::ofstream& file_stream) {
    if (!file_stream.is_open()) {
        std::cout << "File stream not open!";
        return;
    }
    file_stream << "</body></html>\n";
}

void HtmlFactory::write_year(const int& year_value, std::ofstream& file_stream) {
    if (!file_stream.is_open()) {
        std::cout << "File stream not open!";
        return;
    }

    file_stream << "<div class=\"year\">\n";
    file_stream << "<div class=\"yearname\">\n" << std::to_string(year_value) << "</div>\n";

    unsigned int week_number = 0;

    int padding_value = calculate_starting_padding(year_value - 1);

    for (std::string& month_string : Dates::get_month_strings()) {
        padding_value = write_month(
            month_string, 
            padding_value, 
            year_value % 4 == 0, 
            week_number, 
            file_stream
        );
    }

    file_stream << "</div>\n";// end year
}

unsigned int HtmlFactory::write_month(
    const std::string& month_string, 
    int day_padding, 
    const bool& leap_year, 
    unsigned int& current_week_number, 
    std::ofstream& file_stream
) {
    file_stream << "<div class=\"month\">\n";
    file_stream << "<div class=\"monthname\">\n" << month_string << "</div>\n";

    // Write titles
    for (unsigned int i = 0 ; i < 8; ++i) {
        write_day(month_title_strings[i], file_stream);
    }

    unsigned int column = 0;

    // Write padding
    while (day_padding > 0) {
        if (column == 0) {
            write_week_number(current_week_number, file_stream);
        } else {
            write_day("", file_stream);
            day_padding--;
        }
        increment_column_int(column);
    }

    // Write the days
    unsigned int month_days = Dates::get_days_in_month(month_string, leap_year);
    unsigned int day = 1;
    while (day <= month_days) {
        if (column == 0) {
            write_week_number(current_week_number, file_stream);
        } else {
            write_day(std::to_string(day), file_stream);
            day++;
        }
        increment_column_int(column);
    }

    // Write ending padding
    if (column != 0) {
        unsigned int padding_to_write = 8 - column;
        for (; padding_to_write > 0; padding_to_write--) {
            write_day("", file_stream);
        }
    }

    file_stream << "</div>\n";// end month

    if ( column > 0) {
        current_week_number--;  
        return column - 1;
    }
    return column;
}

void HtmlFactory::write_day(std::string inner_value, std::ofstream& file_stream) {
    file_stream << "<div class=\"day\">\n" << inner_value << "</div>\n";
}

void HtmlFactory::write_week_number(unsigned int& week_number, std::ofstream& file_stream) {
    write_day(std::to_string(week_number), file_stream);
    week_number++;
}

void HtmlFactory::increment_column_int(unsigned int& column_int) {
    if (column_int == 7) {
        column_int = 0;
    } else {
        column_int++;
    }
}

unsigned int HtmlFactory::calculate_starting_padding(const unsigned int& year) {
    int century = std::floor(year / 100.0);
    int y = (year % 100);
    int day = (int)(30 - (2 * century) + y + std::floor(y / 4) + std::floor(century / 4)) % 7;  
    // This formula will return the days integers in a non
    // monday focussed sequence
    // The following translates it into 0=monday, 1=tuesday and so on
    if (day < 0) {
        // Occasionally it can return negative values, convert these to positive first
        day = 7 + day;
    }
    day -= 2;
    if (day < 0) {
        day += 7;
    }
    return day;
}
