#include  "../include/util.hpp"
#include <iostream>
#include <cstdlib>


void pk::mAssert(const bool status) {
    if (status == false) {
        std::exit(EXIT_FAILURE);
    }
}


void pk::mAssert(const bool status, const char* msg) {
    if (status == false) {
        std::cout << msg << '\n';
        std::exit(EXIT_FAILURE);
    }
}
