//
// Created by gaporf on 01.06.19.
//

#include "test.h"
#include <cstring>
#include <vector>
#include <iostream>

#include "HUFFMAN/file_reader.h"
#include "HUFFMAN/file_writer.h"
#include "compress.h"
#include "decompress.h"

int coincidence(std::string const &first, std::string const &second) {
    file_reader f1(first),
            f2(second);
    if (!f1.is_open()) {
        std::cerr << "Could not open_file the file " << first << std::endl;
        return 2;
    } else if (!f2.is_open()) {
        std::cerr << "Could not open_file the file " << second << std::endl;
        return 2;
    }
    const size_t N = 1024;
    for (;;) {
        std::vector<char> buf1(N),
                buf2(N);
        size_t n1 = f1.get_char(N, buf1.data()),
                n2 = f2.get_char(N, buf2.data());
        if (n1 != n2 || buf1 != buf2) {
            return 0;
        } else if (n1 == 0) {
            break;
        }
    }
    f1.close_file();
    f2.close_file();
    return 1;
}

void get_random(std::string const &first) {
    file_writer out(first);
    size_t N = 1024;
    for (size_t i = 0; i < N; i++) {
        std::vector<char> symbols(N);
        for (size_t j = 0; j < N; j++) {
            symbols[j] = rand() % 256;
        }
        out.put_char(N, symbols.data());
    }
    out.close_file();
}

int test(std::string const &first, std::string const &second) {
    srand(time(nullptr));
    std::string midle = "temp.txt";
    std::cout << "Start random tests" << std::endl;
    for (size_t i = 0; i < 100; i++) {
        get_random(first);
        compress(first, midle);
        decompress(midle, second);
        int check = coincidence(first, second);
        if (check == 0) {
            std::cout << "Error" << std::endl;
            return 0;
        } else if (check == 1) {
            std::cout << "Ok" << std::endl;
        } else {
            return check;
        }
    }
    std::cout << "All random tests are completed!" << std::endl;
    return 0;
}
