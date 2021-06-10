/*
** EPITECH PROJECT, 2021
** B_YEP_400_BER_4_1_indiestudio_karl_erik_stoerzel
** File description:
** FireUp.cpp
*/

#include "FireUp.hpp"

FireUp::FireUp(SAppContext &sac) : PowerUp(sac, "media/sydney.md2", "media/sydney.bmp")
{
}

std::pair<Timer, PowerUpType> FireUp::getTimerAndType()
{
    return std::make_pair(Timer(5000), PowerUpType::FireUp_t);
}
