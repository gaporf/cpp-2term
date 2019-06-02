//
// Created by gaporf on 01.06.19.
//

#ifndef UTILITY_FILE_WRITER_H
#define UTILITY_FILE_WRITER_H

#include <string>

struct file_writer {
    explicit file_writer(std::string const &file_name);

    file_writer(file_writer const &rhs) = delete;

    ~file_writer();

    file_writer &operator=(file_writer const &rhs) = delete;
    
    void close_file();

    bool is_open();

    void put_char(size_t N, char const *buf);

    void open_file(std::string const &file_name);

private:

    int fd;
};

#endif //UTILITY_FILE_WRITER_H
