//
// Created by vitor on 9/21/24.
//

#ifndef FRAMECOUNTER_H
#define FRAMECOUNTER_H


namespace pk {

    class FrameCounter {

    private:
        int currentFrame{};
        int speed{};
        int maxCounter{};
        int counter{};

    public:
        FrameCounter() = default;
        FrameCounter(int speed, int maxCounter);
        void update();
        int getCounter() const;

    };

}

#endif //FRAMECOUNTER_H
