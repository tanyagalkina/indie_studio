/*
** EPITECH PROJECT, 2021
** B_YEP_400_BER_4_1_indiestudio_karl_erik_stoerzel
** File description:
** PowerUp.hpp
*/

#ifndef B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_POWERUP_HPP
#define B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_POWERUP_HPP

#include "ICollidable.hpp"
#include "Error.hpp"

class PowerUp : public ICollidable
{
protected:
    bool isExisting = true;
public:
    ~PowerUp() override = default;
    explicit PowerUp(SAppContext &ctx, const irr::core::string<irr::fschar_t>& meshPath, const
    irr::core::string<irr::fschar_t> &texturePath);
    void setPosition(float x, float z) final;
    virtual std::pair<Timer, PowerUpType> getTimerAndType() = 0;
    bool HandleCollision(Player &player) override;
};

#endif //B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_POWERUP_HPP
