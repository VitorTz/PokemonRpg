//
// Created by vitor on 9/19/24.
//
#include "FrameCounter.h"


pk::FrameCounter::FrameCounter(const std::uint32_t speed, const std::uint32_t maxFrame) : maxFrame(maxFrame), speed(speed) {

}


void pk::FrameCounter::update() {
    this->currentFrame++;
    if (this->currentFrame > this->speed) {
        this->currentFrame = 0;
        this->counter = (this->counter + 1) % this->maxFrame;
    }
}


void pk::FrameCounter::setMaxFrame(const std::uint32_t frame) {
    this->maxFrame = frame;
}


std::uint32_t pk::FrameCounter::getMaxFrame() const {
    return this->maxFrame;
}


std::uint32_t pk::FrameCounter::getCounter() const {
    return this->counter;
}


