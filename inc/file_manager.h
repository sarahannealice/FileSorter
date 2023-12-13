//
// Created by sarah on 13/12/2023.
//

#ifndef FILESORTER_FILE_MANAGER_H
#define FILESORTER_FILE_MANAGER_H

bool valid_file(const std::string&);
bool empty(const std::string&);

//---standard operations for files---//
std::string peek(const std::string&);
void pop(const std::string&);
void push (const std::string&, const std::string&);

#endif //FILESORTER_FILE_MANAGER_H
