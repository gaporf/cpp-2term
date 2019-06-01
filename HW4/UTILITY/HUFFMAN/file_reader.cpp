//
// Created by gaporf on 01.06.19.
//

#include <cstring>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include "file_reader.h"

file_reader::file_reader(std::string const &file_name) {
    fd = open(file_name.c_str(), O_RDONLY);
}

file_reader::~file_reader() {
    if (fd != -1) {
        close(fd);
    }
    fd = -1;
}

size_t file_reader::get_char(size_t N, char *buf) {
    return read(fd, buf, N);
}

bool file_reader::is_open() {
    return fd != -1;
}

void file_reader::close_file() {
    if (fd != -1) {
        close(fd);
    }
    fd = -1;
}

void file_reader::open_file(std::string const &file_name) {
    close_file();
    fd = open(file_name.c_str(), O_RDONLY);
}