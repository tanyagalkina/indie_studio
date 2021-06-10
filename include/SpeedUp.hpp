/*
** EPITECH PROJECT, 2021
** B_YEP_400_BER_4_1_indiestudio_karl_erik_stoerzel
** File description:
** SpeedUp.hpp
*/

#ifndef B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_SPEEDUP_HPP
#define B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_SPEEDUP_HPP

#include "PowerUp.hpp"
#include "Timer.hpp"

class SpeedUp : public PowerUp
{
private:
    Timer timer;
public:
    explicit SpeedUp(SAppContext &sac) : PowerUp(sac, "media/sydney.md2", "media/sydney.bmp"){}
    void HandleCollision(Player &player) final;
};

void SpeedUp::HandleCollision(Player &player)
{
    if (this->body->isVisible() && player.getBody()->getTransformedBoundingBox().intersectsWithBox(
        this->body->getTransformedBoundingBox()))
    {
        timer.startTimer();
        player.setExtraSpeed(irr::f32(2));
        this->body->setVisible(false);
    }
    else if (!this->body->isVisible() && this->isExisting)
    {
        if (timer.getElapsedTime() > 15000)
        {
            this->isExisting = false;
            player.setExtraSpeed(irr::f32(1));
        }
    }
}

#endif //B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_SPEEDUP_HPP
