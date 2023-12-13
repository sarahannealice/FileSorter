//
// Created by sarah on 12/12/2023.
//

#include <string>
#include <vector>
#include <sstream>
#include <iostream>

#include "../inc/file_sort.h"
#include "../inc/file_manager.h"

// returns indexed element to compare
// received help from ewan -- code is understood but his
std::string FileSorter::get_indexed(const std::string& line) const {
    // istringstream info -- https://stackoverflow.com/a/3292157
    std::istringstream iss(line);
    std::string indexed;

    for (int i = 0; i <= this->index; i++) {
        std::getline(iss, indexed, '\t');
    }

    return indexed;
}

//-----------ANNOYING-----------//
bool FileSorter::elements_in_sublist(const std::string& first, const std::string& last) const {
    std::cout << "first of first: " << get_indexed(peek(first)) << std::endl;
    std::cout << "first of last: " << get_indexed(peek(last)) << std::endl;
    std::cout << "comparison of both: " << (get_indexed(peek(first)) >= get_indexed(peek(last))) << std::endl;

    return !empty(first) && (get_indexed(peek(first)) >= get_indexed(peek(last)));
}

bool FileSorter::elements_in_column(const std::string& first, const std::string& second, const std::string& last) const {
    return !empty(first) && (get_indexed(peek(first)) >= get_indexed(peek(last)) &&
                                (empty(second) ||
                                 get_indexed(peek(second)) < get_indexed(peek(last)) ||
                                 get_indexed(peek(first)) < get_indexed(peek(second))));
}

bool FileSorter::elements_not_in_current_list(const std::string& first, const std::string& second, const std::string& last) {
    return (empty(first) || !empty(second));

    /*
     *  @brief:
     *  the following lines of code, when uncommented, produce an
     *  infinite loop
     * */
//    &&
//           ((get_indexed(peek(first)) < get_indexed(peek(last))) ||
//            ((get_indexed(peek(first)) > get_indexed(peek(last)) &&
//              get_indexed(peek(second)) < get_indexed(peek(first)))));
}
//-----------ANNOYING-----------//

// compare datasets
// 0 = same, 1 = less than, 2 = greater than
int FileSorter::compare(std::string data1, std::string data2) const {
    int compare_value;
    bool compared = false;
    std::string temp1 = data1;
    std::string temp2 = data2;
    int num = 0;

    std::cout << data1 << std::endl;

    // checks if data is employee number
    // removes W if so
    if (this->index == 0) {
        temp1 = data1.erase(0, 1);
        temp2 = data2.erase(0, 1);
    }
    std::cout << data1 << std::endl;

    // checks if data is address
    // extracts numbers if so
    if (this->index == 3) {
        std::cout << data1 << std::endl;
        for (auto n : data1) {
            if (isdigit(n)) temp1 += n;
        }
        std::cout << temp1 << std::endl;

        for (auto n : data2) {
            if (isdigit(n)) temp2 += n;
        }
    }

    while (!compared) {
        std::cout << (temp1 < temp2) << std::endl;
        // compares digits
        if (isdigit(temp1[num])) {
            if ((int)temp1[num] < (int)temp2[num]) {
                compare_value = 1;
                compared = true;
            } else if ((int)data1[num] > (int)data2[num]) {
                compare_value = 2;
                compared = true;
            } else {
                num++;
                continue;
            }
        }

        // compares alpha letters
        if (data1[num] < data2[num]) {
            compare_value = 1;
            compared = true;
        } else if (data1[num] > data2[num]) {
            compare_value = 2;
            compared = true;
        } else {
            num++;
            continue;
        }
    }
}


// merge files until sorted
int FileSorter::merge() {
    int num_subfiles = 0;

    // which file starts the process
    auto first = empty(this->split2) || get_indexed(peek(this->split1)) < get_indexed(peek(this->split2)) ?
            this->split1 : this->split2;
    auto second = first == this->split1 ? this->split2 : this->split1;

    // keep merging while there are records left
    while (!empty(this->split1) || !empty(this->split2)) {
        std::string last;

        while (elements_in_sublist(first, last)) {
            // take records from column while in order
            do {
                last = peek(first);
                pop(first);
                push(this->merge_file, last);
            } while (elements_in_column(first, second, last));

            // when done, switch to taking elements from second column
            // if there is none left in second, stay on first
            if (elements_not_in_current_list(first, second, last)) {
                std::swap(first, second);
            }
        }

        // move to next subfiles
        num_subfiles++;
    }

    return num_subfiles;
}

// splits file into 2 subfiles for natural sorting
void FileSorter::split() const {
    int num_subfiles = 0;

    std::string prev;
    while (!empty(this->merge_file)) {
        // read in data
        auto curr = peek(this->merge_file);
        pop(this->merge_file);

        auto curr_data = get_indexed(curr);
        auto prev_data = get_indexed(prev);

        if (!prev.empty() && get_indexed(curr) < get_indexed(prev)) num_subfiles++;

        // writes out odds and evens
        if (num_subfiles % 2 == 0) {
             push(this->split1, curr);
        } else {
            push(this->split2, curr);
        }

        prev = curr;
    }
}

// splits and merges file until sorted
void FileSorter::merge_sort() {
    int subfiles;

    do {
        split();
        subfiles = merge();
    } while (subfiles != 1);

    // remove empty temp files created
    remove_temp_files();
}

void FileSorter::remove_temp_files() const {
    // file names need to be const char* rather than strings
    // to access the 'remove' function
    std::remove(this->split1);
    std::remove(this->split2);
}