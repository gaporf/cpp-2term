//
// Created by gaporf on 01.06.19.
//

#ifndef UTILITY_FILE_READER_H
#define UTILITY_FILE_READER_H

#include <string>

struct file_reader {
    explicit file_reader(std::string const &file_name);

    ~file_reader();

    file_reader(file_reader const &rhs) = delete;

    file_reader &operator=(file_reader const &rhs) = delete;

    size_t get_char(size_t N, char *buf);

    bool is_open();

    void close_file();

    void open_file(std::string const &file_name);

private:
    int fd;
};

#endif //UTILITY_FILE_READER_H
