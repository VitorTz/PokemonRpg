//
// Created by vitor on 9/22/24.
//

#ifndef TILEDMAP_H
#define TILEDMAP_H
#include "../pokemon.h"


namespace pk {

    class TiledMap {
    private:
        int rows{};
        int cols{};
        std::vector<std::vector<bool>> grid{};
        std::pair<int, int> start{};
        std::pair<int, int> end{};

    private:
        std::map<std::pair<int, int>, std::pair<int, int>> cameFrom{};
        std::map<std::pair<int, int>, double> costSoFar{};
        std::size_t validNeighbors{};
        std::array<pk::pPair, 8> neighbors{};
        std::vector<std::pair<int, int>> path{};

    private:
        void fillNeighbors(const std::pair<int, int>& pos);
        bool isDestination(int x, int y) const;

    public:
        static std::pair<int, int> getTilePressedByMouse();
        static std::pair<int, int> getPlayerTile();

    public:
        explicit TiledMap(const char* source);
        bool isValidPos(const std::pair<int, int>& pos) const;
        bool isValidPos(int x, int y) const;
        const std::vector<std::pair<int, int>>& getPath(const std::pair<int, int>& start, const std::pair<int, int>& end);
        const std::vector<std::pair<int, int>>& getPath(int startX, int startY, int endX, int endY);

    };

}

#endif //TILEDMAP_H
