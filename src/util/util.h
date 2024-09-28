//
// Created by vitor on 9/28/24.
//

#ifndef UTIL_H
#define UTIL_H
#include <cassert>
#include <filesystem>
#include "types.h"
#include <vector>
#include <array>


namespace pk {


    pk::hash_t hash(const char* s);
    int randint(int start, int end);

    std::filesystem::path randomFile(const char* dir);

    template<typename T>
    const T& randomChoice(const std::vector<T>& v) {
        assert(v.empty() == false);
        return v[pk::randint(0, v.size())];
    }

    template<typename T, std::size_t size>
    const T& randomChoice(const std::array<T, size>& arr) {
        assert(arr.empty() == false);
        return arr[pk::randint(0, arr.size())];
    }

    template<typename T>
    const T& randomChoice(T* arr, const int size) {
        return *(arr + pk::randint(0, size));
    }


}

#endif //UTIL_H
