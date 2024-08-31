#pragma once
#include <SFML/Graphics.hpp>
#include <array>


namespace pk {


    class Input {

        private:
            std::array<int, sf::Keyboard::KeyCount> arr{};
            float mouseWheelDelta{};

        public:
            void handleEvent(const sf::Event& event);
            bool isKeyPressed(sf::Keyboard::Key k);
            bool isKeyJustPressed(sf::Keyboard::Key k);
            void resetMouseWheelStatus();
            float getMouseWheelDelta();
            
    };

    inline pk::Input gInput{};
    
} // namespace pk
