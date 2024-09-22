//
// Created by vitor on 9/21/24.
//
#include "util.h"

unsigned long pk::hash(const char *s) {
    unsigned long hash = 5381;
    int c;
    while ((c = *s++))
        hash = ((hash << 5) + hash) + c;
    return hash;
}
