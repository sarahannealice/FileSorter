//
// Created by sarah on 13/12/2023.
//

#include <string>
#include <sys/stat.h>
#include <fstream>
#include <vector>

// checks if file is valid -- https://stackoverflow.com/a/12774387
// stat struct -- https://stackoverflow.com/q/3512434
bool valid_file(const std::string& filename) {
    struct stat buffer{};
    return (stat(filename.c_str(), &buffer) == 0);
}

// checks if file is empty
bool empty(const std::string& filename) {
    std::fstream file(filename, std::ios::in);
    std::string line;

    if (std::getline(file, line)) return false;
    else return true;
}

// get first line of file
std::string peek(const std::string& filename) {
    std::fstream file(filename, std::ios::in);
    std::string line;

    if (std::getline(file, line)) return line;
    else return "";
}

// remove first line from file
void pop(const std::string& filename) {
    std::fstream file(filename, std::ios::in);
    std::string line;
    std::vector<std::string> temp;
    int count = 0;

    // reads file into vector, except first line
    while (std::getline(file, line)) {
        if (count < 1) {
            // skip first line
            count++;
        } else {
            temp.push_back(line);
            count++;
        }
    }

    // close then re-open file
    file.close();
    file.open(filename, std::ios::out);

    // write remaining lines to file
    for (const auto& employee: temp) {
        file << employee << std::endl;
    }

    file.close();
}

// adds line to file
void push(const std::string& filename, const std::string& line) {
    // appends to file
    std::fstream file(filename, std::ios::app);
    file << line << std::endl;
}
