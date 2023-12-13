//
// Created by sarah on 12/12/2023.
//

#ifndef FILESORTER_FILE_SORT_H
#define FILESORTER_FILE_SORT_H

#include <string>

class FileSorter {
public:
    std::string merge_file;
    const char *split1 = "../split1.txt";
    const char *split2 = "../split2.txt";
    int index;

public:
    //---main methods---//
    void merge_sort();
    void split() const;
    int merge();

    void remove_temp_files() const;

    [[nodiscard]] int compare(std::string, std::string) const;
    [[nodiscard]] std::string get_indexed(const std::string&) const;
    [[nodiscard]] bool elements_in_sublist(const std::string&, const std::string&) const;
    [[nodiscard]] bool elements_in_column(const std::string&, const std::string&, const std::string&) const;
    [[nodiscard]] static bool elements_not_in_current_list(const std::string&, const std::string&, const std::string&);
};


#endif //FILESORTER_FILE_SORT_H
