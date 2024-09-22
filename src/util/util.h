//
// Created by vitor on 9/21/24.
//

#ifndef UTIL_H
#define UTIL_H
#include "AssetPool.h"


namespace pk {

    unsigned long hash(const char* s);

    int randint(int start, int end);
    double euclideanDistance(const std::pair<int, int>& start, const std::pair<int, int>& end);
    double euclideanDistance(int startX, int startY, int endX, int endY);

}

#endif //UTIL_H
