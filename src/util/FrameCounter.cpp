//
// Created by vitor on 9/19/24.
//
#include "FrameCounter.h"


pk::FrameCounter::FrameCounter(const std::uint32_t speed, const std::uint32_t maxCounter) : speed(speed), maxCounter(maxCounter) {

}


void pk::FrameCounter::update() {
    this->currentFrame++;
    if (this->currentFrame > this->speed) {
        this->currentFrame = 0;
        this->counter = (this->counter + 1) % this->maxCounter;
    }
}


std::uint32_t pk::FrameCounter::getCounter() const {
    return this->counter;
}



