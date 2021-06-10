/*
** EPITECH PROJECT, 2021
** B_YEP_400_BER_4_1_indiestudio_karl_erik_stoerzel
** File description:
** Timer.hpp
*/

#ifndef B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_TIMER_HPP
#define B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_TIMER_HPP
#include <chrono>

class Timer {
    std::chrono::time_point<std::chrono::system_clock> start{};
    std::chrono::time_point<std::chrono::system_clock> end{};
    float time;
public:
    explicit Timer(float Milliseconds) : time(Milliseconds){}
    void startTimer()
    {
        start = std::chrono::system_clock::now();
    }
    float getElapsedTime()
    {
        end = std::chrono::system_clock::now();
        return float(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
    }
    void reset()
    {
        start = std::chrono::system_clock::now();
    }
    bool isFinished()
    {
        return getElapsedTime() >= time;
    }
};

#endif //B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_TIMER_HPP
