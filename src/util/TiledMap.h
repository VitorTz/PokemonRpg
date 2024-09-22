//
// Created by vitor on 9/22/24.
//

#ifndef TILEDMAP_H
#define TILEDMAP_H
#include <cstdint>
#include <vector>
#include <array>
#include <queue>
#include <map>

namespace pk {

    class TiledMap {

    private:
        typedef struct std::pair<double, std::pair<int, int>> pPair;
        typedef struct std::priority_queue<pPair, std::vector<pPair>, std::greater<>> PriorityQueue;

    private:
        int rows{};
        int cols{};
        std::vector<std::vector<bool>> grid{};
        std::pair<int, int> start{};
        std::pair<int, int> end{};

    private:
        std::map<std::pair<int, int>, std::pair<int, int>> cameFrom{};
        std::map<std::pair<int, int>, double> costSoFar{};
        std::array<pPair, 8> neighborsDelta = {
            pPair{1.0, {0, -1}}, // left
            {1.0, {0, 1}},  // right
            {1.0, {1, 0}},  // bottom
            {1.0, {-1, 0}}, // top
            {0.50, {1, 1}}, // right bottom
            {0.50, {-1, 1}}, // right top
            {0.50, {1, -1}}, // left bottom
            {0.50, {-1, -1}} // left top
        };
        std::size_t validNeighbors{};
        std::array<pPair, 8> neighbors{};
        std::vector<std::pair<int, int>> path{};

    private:
        void fillNeighbors(const std::pair<int, int>& pos);
        bool isDestination(int x, int y) const;

    public:
        bool isValidPos(const std::pair<int, int>& pos) const;
        bool isValidPos(int x, int y) const;

    public:
        explicit TiledMap(const char* source);
        const std::vector<std::pair<int, int>>& getPath(int startX, int startY, int endX, int endY);



    };

}

#endif //TILEDMAP_H
