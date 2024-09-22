//
// Created by vitor on 9/21/24.
//
#include "util.h"
#include <cmath>

unsigned long pk::hash(const char *s) {
    unsigned long hash = 5381;
    int c;
    while ((c = *s++))
        hash = ((hash << 5) + hash) + c;
    return hash;
}


double pk::euclideanDistance(const int startX, const int startY, const int endX, const int endY) {
    return std::sqrt(
        std::pow(startX - endX, 2) + std::pow(startY + endY, 2)
    );
}


double pk::euclideanDistance(const std::pair<int, int>& start, const std::pair<int, int>& end) {
    return std::sqrt(
        std::pow(start.first - end.first, 2) + std::pow(start.second - end.second, 2)
    );
}


