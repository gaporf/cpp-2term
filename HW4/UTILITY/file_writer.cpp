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
#include "file_writer.h"

file_writer::file_writer(std::string const &file_name) {
    fd = open(file_name.c_str(), O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
}

file_writer::~file_writer() {
    if (fd != -1) {
        close(fd);
    }
}

void file_writer::put_char(size_t N, char const *buf) {
    write(fd, buf, N);
}

bool file_writer::is_open() {
    return fd != -1;
}

void file_writer::close_file() {
    if (fd != -1) {
        close(fd);
    }
}

void file_writer::open_file(std::string const &file_name) {
    fd = open(file_name.c_str(), O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
}