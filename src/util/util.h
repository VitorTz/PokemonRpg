//
// Created by vitor on 9/30/24.
//

#ifndef UTIL_H
#define UTIL_H
#include "../pokemon.h"


namespace pk {

    unsigned long hash(const char* s);

    int randint(int start, int end);

    template<typename T, std::size_t size>
    const T& randomChoice(const std::array<T, size>& arr) {
        assert(arr.empty() == false);
        return arr[pk::randint(0, arr.size())];
    }

    template<typename T>
    const T& randomChoice(const std::vector<T>& arr) {
        assert(arr.empty() == false);
        return arr[pk::randint(0, arr.size())];
    }

    std::filesystem::path randomFile(const char* dir);

    double euclideanDistance(int p1, int p2, int q1, int q2);

    void printRect(const Rectangle& r);
    void printVec(const Vector2& v);
    

}


#endif //UTIL_H
