//
// Created by vitor on 9/19/24.
//

#ifndef FRAMECOUNTER_H
#define FRAMECOUNTER_H
#include <cstdint>


namespace pk {


    class FrameCounter {

    private:
        std::uint32_t currentFrame{};
        std::uint32_t counter{};
        std::uint32_t maxFrame{1};
        std::uint32_t speed{1};

    public:
        FrameCounter() = default;
        FrameCounter(std::uint32_t speed, std::uint32_t maxFrame);
        void update();
        void setMaxFrame(std::uint32_t frame);
        std::uint32_t getMaxFrame() const;
        std::uint32_t getCounter() const;

    };


}

#endif //FRAMECOUNTER_H
