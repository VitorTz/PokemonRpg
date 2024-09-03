#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include "../types.hpp"


namespace pk {

    class Camera {

        private:
            std::map<pk::zindex_t, std::vector<std::pair<float, pk::entity_t>>> entityVecByIndex{};
            sf::View view{};
            std::size_t entityCount{};            
            float zoom{1.0f};
        
        public:
            Camera();
            void insert(pk::entity_t e);
            void erase(pk::entity_t e);
            void clear();
            void draw(sf::RenderWindow& window);
            void setCenter(const sf::Vector2f& center);
            void setCenter(const float x, const float y);
            void addZoom(float delta);
            void setZoom(float zoom);
            float getZoom() const;
            std::size_t getEntityCount() const;

    };

    inline pk::Camera gCamera{};
    
} // namespace pk
