//
// Created by vitor on 9/14/24.
//

#ifndef UTIL_H
#define UTIL_H
#include "pokemon.h"

namespace pk {

    unsigned long hash(const char* s);
    float randfloat(float start, float end);
    int randint(int start, int end);

    std::filesystem::path choiceRandomFile(const char* dir);

    template<typename T>
    const T& randomChoice(const std::vector<T>& v) {
        assert(v.empty() == false);
        return v[pk::randint(0, v.size() - 1)];
    }

    void addSpriteToEntity(pk::entity_t e, const char* fileName);

    void addCollisionBoxStaticToEntity(pk::entity_t e);
    void createCollisionBoxStatic(pk::entity_t e, const sf::Vector2f& pos, const sf::Vector2f& size);

    void normalizeVec(sf::Vector2f* v);
    sf::Vector2f getMoveDirection(sf::Keyboard::Key left, sf::Keyboard::Key right, sf::Keyboard::Key top, sf::Keyboard::Key bottom);
    sf::Vector2f getMoveDirection();

}

#endif //UTIL_H
