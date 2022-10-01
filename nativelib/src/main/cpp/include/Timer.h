//
// Created by newst on 2022-10-01.
//

#ifndef BODA_TIMER_H
#define BODA_TIMER_H

#include <memory>
#include <chrono>

class Timer {
public:
    static Timer* getInstance() {
        static Timer* instance = new Timer();
        return instance;
    }

    std::chrono::milliseconds getTime() {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start);
    }

private:
    Timer() {
        start = std::chrono::system_clock::now();
    };
    std::chrono::system_clock::time_point start;
};

#endif //BODA_TIMER_H
