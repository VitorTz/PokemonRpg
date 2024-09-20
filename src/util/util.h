//
// Created by vitor on 9/14/24.
//

#ifndef UTIL_H
#define UTIL_H
#include "../pokemon.h"

namespace pk {


    // random

        /**
         * @return Um número de ponto flutuante (float) aleatório entre [start, end]
         */
        float randfloat(float start, float end);

        /**
        * @return Um número de ponto flutuante (double) aleatório entre [start, end]
        */
        double randDouble(double start, double end);
        /**
         * @return Um número inteiro aleatório entre [start, end - 1]
         */
        int randint(int start, int end);
        std::filesystem::path randomFile(const char* dir);

        /**
         * @return um elemento aleatório do vector
         */
        template<typename T>
        const T& randomChoice(const std::vector<T>& v) {
            assert(v.empty() == false);
            return v[pk::randint(0, v.size() - 1)];
        }

        /**
         * @return um elemento aleatório do array
         */
        template<typename T, std::size_t size>
        const T& randomChoice(const std::array<T, size>& v) {
            assert(v.empty() == false);
            return v[pk::randint(0, v.size() - 1)];
        }

            /**
         * @return um elemento aleatório do array
         */
        template<typename T>
        const T* randomChoice(const T* arr, const std::size_t size) {
            assert(size != 0);
            return arr + pk::randint(0, size - 1);
        }

    // print
        void printVec2f(const sf::Vector2f& v);
        void printFloatRect(const sf::FloatRect& rect);

    // filesystem
        /**
         * @return Os arquivos dentro de um diretório
         */
        std::vector<std::filesystem::path> getFilesFromDir(const char* dir);

    // ecs
        /**
         * Adiciona o component sprite_t a uma entidade.
         */
        void addSpriteToEntity(pk::entity_t e, const char* fileName);

        void addSpriteAnimation(pk::entity_t e, pk::AssetId assetId, pk::animation_speed_t animationSpeed);

        /**
        * Muda a texture do component sprite_t da entidade e
        */
        void changeEntitySprite(pk::entity_t e, const char* fileName);
        /**
        * Muda a texture do component sprite_t da entidade e
        */
        void changeEntitySprite(pk::entity_t e, const sf::Sprite& sprite);

        void addCollisionBoxStaticToEntity(pk::entity_t e);
        void createCollisionBoxStatic(pk::entity_t e, const sf::Vector2f& pos, const sf::Vector2f& size);

    // math
        unsigned long hash(const char* s);
        void normalizeVec(sf::Vector2f* v);
        sf::Vector2f getMoveDirection(sf::Keyboard::Key left, sf::Keyboard::Key right, sf::Keyboard::Key top, sf::Keyboard::Key bottom);
        sf::Vector2f getMoveDirection();
        float easeIn(float t);
        float getTimePercentage(float currentTime, float maxTime);
        sf::Vector2f lerp(const sf::Vector2f& start, const sf::Vector2f& end, float t);

        /**
         * Multiplica um vetor por um escalar
         */
        sf::Vector2f vector2Scale(const sf::Vector2f& v, float scale);
        /**
         * Multiplica um vetor por um escalar
         */
        sf::Vector2f vector2Scale(const sf::Vector2f& v, double scale);
        /**
         * Adiciona dois vetores
         */
        sf::Vector2f vector2Add(const sf::Vector2f& v1, const sf::Vector2f& v2);
        int binomialCoefficient(int n, int k);



}

#endif //UTIL_H
