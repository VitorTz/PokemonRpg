//
// Created by vitor on 9/28/24.
//
#include <random>
#include "util.h"
#include "../ecs/ECS.h"

std::random_device dev{};
std::uniform_int_distribution<int> dist(0, std::numeric_limits<int>::max());


pk::hash_t pk::hash(const char *s) {
    unsigned long hash = 5381;
    int c;
    while ((c = *s++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}


int pk::randint(const int start, const int end) {
    return start + dist(dev) % (end - start);
}


std::filesystem::path pk::randomFile(const char *dir) {
    std::vector<std::filesystem::path> v{};
    for (const auto& p : std::filesystem::directory_iterator(dir)) {
        const std::filesystem::path& path = p.path();
        if (std::filesystem::is_regular_file(path)) {
            v.push_back(path);
        }
    }
    return pk::randomChoice(v);
}


void pk::loadWorldMap(const char *fileName) {

}


