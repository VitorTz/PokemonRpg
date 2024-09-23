//
// Created by vitor on 9/22/24.
//
#include "TiledMap.h"
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include "util.h"
#include "../ecs/components.h"
#include "../ecs/ECS.h"
#include "../util/Mouse.h"


pk::TiledMap::TiledMap(const char *source) {
    std::ifstream file(source);
    assert(file.is_open());
    file >> this->rows;
    file >> this->cols;
    this->grid.reserve(this->rows);
    for (int i = 0; i < this->rows; i++) {
        this->grid.emplace_back();
        this->grid.back().reserve(this->cols);
        bool x;
        for (int j = 0; j < this->cols; j++) {
            file >> x;
            this->grid[i].push_back(x);
        }
    }
    file.close();
}


inline bool pk::TiledMap::isValidPos(const std::pair<int, int> &pos) const {
    return pos.first >= 0 &&
           pos.first < this->rows &&
           pos.second >= 0 &&
           pos.second < this->cols &&
           this->grid[pos.first][pos.second];
}


inline bool pk::TiledMap::isValidPos(const int x, const int y) const {
    return x >= 0 &&
           x < this->rows &&
           y >= 0 &&
           y < this->cols &&
           this->grid[x][y];
}


inline bool pk::TiledMap::isDestination(const int x, const int y) const {
    return this->end.first == x && this->end.second == y;
}


void pk::TiledMap::fillNeighbors(const std::pair<int, int>& pos) {
    this->validNeighbors = 0;
    for (const pPair& pair : CELL_NEIGHBORS) {
        const int x = pos.first + pair.second.first;
        const int y = pos.second + pair.second.second;
        if (this->isValidPos(x, y)) {
            this->neighbors[this->validNeighbors++] = pPair{pair.first, std::pair<int, int>{x, y}};
        }
    }
}


const std::vector<std::pair<int, int>>& pk::TiledMap::getPath(
    const std::pair<int, int>& start,
    const std::pair<int, int>& end
) {
    return this->getPath(start.first, start.second, end.first, end.second);
}


const std::vector<std::pair<int, int>>& pk::TiledMap::getPath(const int startX, const int startY, const int endX, const int endY) {
    this->cameFrom.clear();
    this->costSoFar.clear();
    this->path.clear();

    this->start = std::pair<int, int>{startX, startY};
    this->end = std::pair<int, int>{endX, endY};

    if (this->start == this->end ||
        this->isValidPos(this->start) == false ||
        this->isValidPos(this->end) == false
    ) {
        return this->path;
    }

    pk::PriorityQueue priorityQueue{};
    priorityQueue.push({0.0, {this->start}});
    cameFrom.emplace(this->start, INVALID_POS);
    costSoFar.emplace(this->start, 0.0);

    while (priorityQueue.empty() == false) {
        const auto [currentCost, currentPos] = priorityQueue.top();
        priorityQueue.pop();

        if (currentPos == this->end) {
            break;
        }

        this->fillNeighbors(currentPos);
        for (std::size_t i = 0; i < this->validNeighbors; i++) {
            const auto [cost, pos] = this->neighbors[i];
            const double newCost = currentCost + cost;
            if (costSoFar.find(pos) == costSoFar.end() || newCost < costSoFar[pos]) {
                costSoFar[pos] = newCost;
                cameFrom[pos] = currentPos;
                priorityQueue.emplace(newCost + pk::euclideanDistance(this->end, pos), pos);
            }
        }
    }

    while (cameFrom.find(this->end) != cameFrom.end() && this->start != this->end && this->end != INVALID_POS) {
        this->end = cameFrom[this->end];
        this->path.push_back(this->end);
    }

    std::reverse(this->path.begin(), this->path.end());
    return this->path;
}


std::pair<int, int> pk::TiledMap::getPlayerTile() {
    std::pair<int, int> pair{};
    const pk::transform_t& playerTransform = pk::gEcs.getTransform(pk::gPlayer.playerEntity);
    pair.first = static_cast<int>(playerTransform.pos.x / pk::TILE_SIZE);
    pair.second = static_cast<int>((playerTransform.pos.y + playerTransform.size.y / 2.0f - 5.0f) / pk::TILE_SIZE);
    return pair;
}


std::pair<int, int> pk::TiledMap::getTilePressedByMouse() {
    std::pair<int, int> pair{};
    pair.first = static_cast<int>(pk::gMouse.mouseWorldPos.x / pk::TILE_SIZE);
    pair.second = static_cast<int>(pk::gMouse.mouseWorldPos.y / pk::TILE_SIZE);
    return pair;
}

