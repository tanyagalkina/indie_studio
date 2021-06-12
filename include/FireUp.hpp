/*
** EPITECH PROJECT, 2021
** B_YEP_400_BER_4_1_indiestudio_karl_erik_stoerzel
** File description:
** FireUp.hpp
*/

#ifndef B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_FIREUP_HPP
#define B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_FIREUP_HPP

#include "PowerUp.hpp"

class FireUp : public PowerUp
{
public:
    explicit FireUp(SAppContext &sac);
    std::pair<Timer, PowerUpType> getTimerAndType() final;

};

#endif //B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_FIREUP_HPP
