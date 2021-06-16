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
#include "Player.hpp"
#include "Bomb.hpp"

class PowerUpHandler
{
private:
    SAppContext *appContext;
    MyList<std::tuple<Timer, PowerUpType, Player *>> currentPowerUps;
    MyList<PowerUp *> allPowerUps;

    static void handlePlayerItems(PowerUpType type, Player *);

public:
    explicit PowerUpHandler(SAppContext &ctx) : appContext(&ctx){}
    void loop(MyList<Player>& players);
    void addPowerUp(PowerUpType, float x, float z);
};

#endif //B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_POWERUPHANDLER_HPP
