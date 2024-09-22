//
// Created by vitor on 9/21/24.
//
#include "FrameCounter.h"


pk::FrameCounter::FrameCounter(const int speed, const int maxCounter) : speed(speed), maxCounter(maxCounter) {

}


void pk::FrameCounter::update() {
    this->currentFrame++;
    if (this->currentFrame > this->speed) {
        this->currentFrame = 0;
        this->counter = (this->counter + 1) % this->maxCounter;
    }
}


int pk::FrameCounter::getCounter() const {
    return this->counter;
}




