#include "include/HtmlFactory.hpp"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <filesystem>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cout << "Wrong number of command line arguments, [file name] [year] expected\n";
        return 0;
    }

    std::string file_name = argv[1];
    file_name.append(".html");
    int target_year = std::stoi(argv[2]); 
    if (target_year < 1582) {
        std::cout << "Application only supports up to october 1582\n";
        return 0;
    }

    std::ofstream file_stream(file_name, std::ofstream::out);

    HtmlFactory::write_html_preamble(file_stream);

    HtmlFactory::write_year(target_year - 1, file_stream);
    HtmlFactory::write_year(target_year, file_stream);
    HtmlFactory::write_year(target_year + 1, file_stream);

    HtmlFactory::write_html_postamble(file_stream);
}