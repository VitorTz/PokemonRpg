#include "FrameCounter.hpp"
#include <cstdint>



pk::FrameCounter::FrameCounter(
    const std::uint8_t maxFrame,
    const std::uint8_t speed
) : maxFrame(maxFrame),
    speed(speed) {

}


std::uint8_t pk::FrameCounter::update() {
    this->currentFrame++;
    if (this->currentFrame > this->speed) {
        this->currentFrame = 0;
        this->counter = (this->counter + 1) % this->maxFrame;        
    }
    return this->counter;
}


void pk::FrameCounter::setSpeed(const std::uint8_t speed) {
    this->speed = speed;
}


void pk::FrameCounter::setMaxFrame(const std::uint8_t maxFrame) {
    this->maxFrame = maxFrame;
}


void pk::FrameCounter::reset() {
    this->currentFrame = 0;
    this->counter = 0;
}