/*
** EPITECH PROJECT, 2021
** B_YEP_400_BER_4_1_indiestudio_karl_erik_stoerzel
** File description:
** PowerUpHandler.hpp
*/

#ifndef B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_POWERUPHANDLER_HPP
#define B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_POWERUPHANDLER_HPP

#include "SpeedUp.hpp"
#include "FireUp.hpp"
#include "BombUp.hpp"

class PowerUpHandler
{
private:
    SAppContext *appContext;
    MyList<std::pair<Timer, PowerUpType>> currentPowerUps;
    MyList<PowerUp *> allPowerUps;
    Player &playerRef;

    void handlePlayerItems(PowerUpType type);

public:
    explicit PowerUpHandler(SAppContext &ctx, Player &pl) : appContext(&ctx), playerRef(pl){}
    void loop(GameEventReceiver &receiver);
    void addPowerUp(PowerUpType, float x, float z);
};

#endif //B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_POWERUPHANDLER_HPP
