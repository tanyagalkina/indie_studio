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

SpeedUp::SpeedUp(SAppContext &sac) : PowerUp(sac, "media/boot.3ds", "media/sydney.bmp")
{
    this->body->setScale(irr::core::vector3df(0.07, 0.07, 0.07));
}

