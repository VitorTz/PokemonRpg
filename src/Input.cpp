#include "../include/Input.hpp"


void pk::Input::handleEvent(const sf::Event& e) {
    switch (e.type) {
        case sf::Event::KeyPressed:
            this->arr[e.key.code] += 1;            
            break;
        case sf::Event::KeyReleased:
            this->arr[e.key.code] = 0;
            break;
        case sf::Event::MouseWheelScrolled:
            if (e.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                this->mouseWheelDelta = e.mouseWheelScroll.delta;
            }
            break;
        default:
            break;
    }
}


bool pk::Input::isKeyPressed(const sf::Keyboard::Key k) {
    return sf::Keyboard::isKeyPressed(k);
}


bool pk::Input::isKeyJustPressed(const sf::Keyboard::Key k) {
    return this->arr[k] == 1 && !sf::Keyboard::isKeyPressed(k);
}


float pk::Input::getMouseWheelDelta() {    
    return this->mouseWheelDelta;
}


void pk::Input::resetMouseWheelStatus() {
    this->mouseWheelDelta = 0.0f;
}