#pragma once
#include <cstdint>


namespace pk {


    class FrameCounter {

        private:
            std::uint8_t currentFrame{};
            std::uint8_t maxFrame{};
            std::uint8_t counter{};
            std::uint8_t speed{};
        
        public:
            FrameCounter(std::uint8_t maxFrame, std::uint8_t speed);
            void setSpeed(std::uint8_t speed);
            void setMaxFrame(std::uint8_t maxFrame);
            void reset();
            std::uint8_t update();

    };

}