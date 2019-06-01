#include <iostream>
#include <string>
#include "compress.h"
#include "decompress.h"
#include "test.h"
#include <time.h>

int main(int argc, char **argv) {
    clock_t start = clock();
    if (argc != 4) {
        std::cerr << "It's necessary to give 3 arguments, got " << argc - 1 << std::endl;
        return 1;
    }
    std::string mode = argv[1],
            file_in = argv[2],
            file_out = argv[3];
    if (mode != "-c" && mode != "-d" && mode != "-t") {
        std::cerr << R"(The mode should be "-c" (compress) or "-d" (decompress) or "-t" (test))" << std::endl;
        return 1;
    }
    int error;
    if (mode == "-c") {
        error = compress(file_in, file_out);
    } else if (mode == "-d") {
        error = decompress(file_in, file_out);
    } else {
        error = test(file_in, file_out);
    }
    if (error != 0) {
        return error;
    }
    clock_t end = clock();
    std::cout << "Time: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << " s" << std::endl;
    return 0;
}