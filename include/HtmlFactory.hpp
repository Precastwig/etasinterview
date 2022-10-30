#ifndef HTMLFACTORY
#define HTMLFACTORY

#include <fstream>
#include <vector>

class HtmlFactory {
public:
    // Writes the HTML headers and css linking tags
    static void write_html_preamble(std::ofstream& file_stream);
    // Writes the HTML closing tags
    static void write_html_postamble(std::ofstream& file_stream);

    // Writes the given year to the given file stream
    static void write_year(const int& year_value, std::ofstream& file_stream);

private:
    // Writes the month given in the string
    // Starts the month with the given day_padding
    // Appends the current_week_number to the start of each week,
    // Additionally will increment the current_week_number as more are added
    // Returns the padding required for writing the next month ie. what day the written month finished on
    static unsigned int write_month(
        const std::string& month_string, 
        int day_padding, 
        const bool& leap_year, 
        unsigned int& current_week_number, 
        std::ofstream& file_stream
    );
    // Writes the given string into a day div container
    static void write_day(std::string inner_value, std::ofstream& file_stream);
    // Calculates the padding needed for the first week of a given year
    static unsigned int calculate_starting_padding(const unsigned int& year);
    // Writes the week number to the file stream (then increments it)
    static void write_week_number(unsigned int& week_number, std::ofstream& file_stream);
    // Increments the column integer, wraps the integer around to 0 on incrementing 8
    static void increment_column_int(unsigned int& column_int);
    
    static inline const std::vector<std::string> month_title_strings = {
        "Wk",
        "Mo",
        "Tu",
        "We",
        "Th",
        "Fr",
        "Sa",
        "Su"
    };
};

#endif