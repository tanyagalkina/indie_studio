/*
** EPITECH PROJECT, 2021
** B_YEP_400_BER_4_1_indiestudio_karl_erik_stoerzel
** File description:
** Bomb.hpp
*/

#ifndef B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_BOMB_HPP
#define B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_BOMB_HPP

#include "ICollidable.hpp"
#include "Error.hpp"

class Bomb : public ICollidable
{
protected:
    bool isExisting = true;
public:
    ~Bomb() override = default;
    explicit Bomb(SAppContext &ctx, const irr::core::string<irr::fschar_t>& meshPath, const
    irr::core::string<irr::fschar_t> &texturePath);
    void setPosition(float x, float z) final;
    virtual std::pair<Timer, PowerUpType> getTimerAndType() = 0;
    bool HandleCollision(Player &player) override;
};

#endif //B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_BOMB_HPP
