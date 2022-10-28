#include <iostream>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cout << "Wrong number of command line arguments, [file name] [year] expected\n";
        return 0;
    }

    std::string file_name = argv[1];
    int target_year = std::stoi(argv[2]); 
    if (target_year < 1582) {
        std::cout << "Application only supports up to october 1582\n";
        return 0;
    }
}