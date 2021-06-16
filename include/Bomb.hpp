/*
** EPITECH PROJECT, 2021
** B_YEP_400_BER_4_1_indiestudio_karl_erik_stoerzel
** File description:
** Bomb.hpp
*/

#ifndef B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_BOMB_HPP
#define B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_BOMB_HPP

#include "AppContext.hpp"
#include "ICollidable.hpp"
//#include "Error.hpp"
#include "Player.hpp"

class Bomb : public ICollidable
{
public:
    explicit Bomb(SAppContext &ctx);
    ~Bomb() override = default;
    void drop(const irr::core::vector3df &pos);
    void setPosition(float x, float z) final;
    bool HandleCollision(Player &player) final;
};

#endif //B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_BOMB_HPP
