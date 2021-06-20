/*
** EPITECH PROJECT, 2021
** B_YEP_400_BER_4_1_indiestudio_karl_erik_stoerzel
** File description:
** BombUp.cpp
*/

#include "BombUp.hpp"

BombUp::BombUp(SAppContext &sac, Audio *s) : PowerUp(sac, "./media/asset/powerup/powerUpP.obj",
"./media/asset/pillier/Texture_pillier_Selfillum_Orange.png", s)
{
    this->body->setMaterialTexture(
        1,driver->getTexture("./media/asset/pillier/Texture_pillier_alpha_Orange.png"));
    this->body->setMaterialTexture(
        2,driver->getTexture("./media/asset/pillier/Texture_pillier_Orange.png"));
    this->body->setScale(irr::core::vector3df(5, 5, 5));
    this->body->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
    this->body->setRotation(irr::core::vector3df(50, 0, 0));
}

std::tuple<Timer, PowerUpType, Character *> BombUp::getTimerTypeAndPlayer(Character &player)
{
    return std::tuple(Timer(5000), PowerUpType::BombUp_t, &player);
}
