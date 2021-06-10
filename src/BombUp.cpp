/*
** EPITECH PROJECT, 2021
** B_YEP_400_BER_4_1_indiestudio_karl_erik_stoerzel
** File description:
** BombUp.cpp
*/

#include "BombUp.hpp"

BombUp::BombUp(SAppContext &sac) : PowerUp(sac, "media/sydney.md2", "media/sydney.bmp")
{
}

std::pair<Timer, PowerUpType> BombUp::getTimerAndType()
{
    return std::make_pair(Timer(5000), PowerUpType::BombUp_t);
}
