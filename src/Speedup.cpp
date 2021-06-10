/*
** EPITECH PROJECT, 2021
** B_YEP_400_BER_4_1_indiestudio_karl_erik_stoerzel
** File description:
** Speedup.cpp
*/

#include "SpeedUp.hpp"

std::pair<Timer, PowerUpType> SpeedUp::getTimerAndType()
{
    return std::make_pair(Timer(15000), PowerUpType::SpeedUp_t);
}

SpeedUp::SpeedUp(SAppContext &sac) : PowerUp(sac, "media/sydney.md2", "media/sydney.bmp")
{}

