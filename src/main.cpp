#include <iostream>
#include <regex>
#include <cstring>

#include "../inc/file_sort.h"
#include "../inc/file_manager.h"

using namespace std;

int main(int argc, char *argv[]) {
    // variables
    FileSorter files;
    regex field_regex("-field=(1[0-3]|[0-9])");
    const char *delimiter = "=";

    //validate program arguments
    if (3 != argc) {
        cout << "too few/many arguments\n'/mergesort -<file> -field=#[0-13]'" << endl;
        return 1;
    } else if (!regex_match(argv[2], field_regex)) {
        cout << "argument 2 must indicate a field between 0 and 13 in the -format:\nfield=#" << endl;
    } else {
        if (valid_file(argv[1])) {
            if (empty(argv[1])) {
                cout << "file to sort is empty" << endl;
            } else {
                char *token = strtok(argv[2], delimiter);

                // takes index from 2nd argument
                for (int ind = 0; ind < 2; ind++) {
                    if (1 == ind) {
                        files.index = atoi(token);
                    }
                    token = strtok(nullptr, delimiter);
                }

                // start merge sorting
                files.merge_file = argv[1];
                files.merge_sort();
            }
        } else {
            cout <<"file not found" << endl;
        }
    }

    return 0;
}