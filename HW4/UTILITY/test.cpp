//
// Created by gaporf on 01.06.19.
//

#include "test.h"
#include <cstring>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

#include "compress.h"
#include "decompress.h"

bool coincidence(std::string first, std::string second) {
    int32_t f1 = open(first.c_str(), O_RDONLY),
            f2 = open(second.c_str(), O_RDONLY);
    if (f1 == -1) {
        std::cerr << "Could not open the file " << first << std::endl;
        exit(1);
    } else if (f2 == -1) {
        std::cerr << "Could not open the file " << second << std::endl;
        exit(1);
    }
    const size_t N = 1024;
    for (;;) {
        std::vector<char> buf1(N),
                buf2(N);
        size_t n1 = read(f1, buf1.data(), N),
                n2 = read(f2, buf2.data(), N);
        if (n1 != n2) {
            close(f1);
            close(f2);
            return false;
        } else if (n1 == 0) {
            break;
        } else if (buf1 != buf2) {
            close(f1);
            close(f2);
            return false;
        }
    }
    close(f1);
    close(f2);
    return true;
}

void get_random(std::string first) {
    int32_t wd = open(first.c_str(), O_TRUNC | O_WRONLY);
    size_t N = 1024;
    for (size_t i = 0; i < N; i++) {
        std::vector<char> symbols(N);
        for (size_t j = 0; j < N; j++) {
            symbols[j] = rand() % 256;
        }
        write(wd, symbols.data(), N);
    }
    close(wd);
}

void test(std::string first, std::string second) {
    srand(time(nullptr));
    std::string midle = "temp.txt";
    compress(first, midle);
    decompress(midle, second);
    if (!coincidence(first, second)) {
        std::cout << "Error" << std::endl;
        exit(20);
    } else {
        std::cout << "Ok" << std::endl;
    }
    std::cout << "Start random tests" << std::endl;
    for (size_t i = 0; i < 100; i++) {
        get_random(first);
        compress(first, midle);
        decompress(midle, second);
        if (!coincidence(first, second)) {
            std::cout << "Error" << std::endl;
            exit(20);
        }
    }
    std::cout << "All random tests are completed!" << std::endl;
}
