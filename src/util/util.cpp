//
// Created by vitor on 9/30/24.
//
#include "util.h"


std::random_device dev;
std::mt19937 rng(dev());
std::uniform_int_distribution<int> intDist(0,std::numeric_limits<int>::max());


unsigned long pk::hash(const char *s) {
    unsigned long hash = 5381;
    int c;
    while ((c = *s++))
        hash = ((hash << 5) + hash) + c;
    return hash;
}


int pk::randint(const int start, const int end) {
    return start + intDist(rng) % (end - start);
}


std::filesystem::path pk::randomFile(const char *dir) {
    std::vector<std::filesystem::path> v{};
    const auto& iter = std::filesystem::directory_iterator(dir);
    for (const auto& p : std::filesystem::directory_iterator(dir)) {
        const std::filesystem::path& path = p.path();
        if (std::filesystem::is_regular_file(path)) {
            v.push_back(path);
        }
    }
    return pk::randomChoice(v);
}


double pk::euclideanDistance(
    const int p1, const int p2,
    const int q1, const int q2
) {
   return std::sqrt(std::pow(p1 - q1, 2) + std::pow(p2 - q2, 2));
}


void pk::printVec(const Vector2 &v) {
    std::printf("Vec(%.2f, %.2f)\n", v.x, v.y);
}


void pk::printRect(const Rectangle &r) {
    std::printf("Rect(%.2f, %.2f, %.2f, %.2f)\n", r.x, r.y, r.width, r.height);
}

