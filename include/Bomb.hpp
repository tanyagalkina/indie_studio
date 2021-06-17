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
#include "Audio.hpp"

class Bomb : public ICollidable
{
private:
    Audio* _sounds;
    Character *_player;
public:
    explicit Bomb(SAppContext &ctx, Audio *sounds, Character *player);
    ~Bomb() override = default;
    Character *getPLayer() const;
    bool over = false;
    Timer timer = Timer(3000);
    void drop();
    void explosion();
    void setPosition(float x, float z) final;
    bool HandleCollision(Character &player) final;
};

#endif //B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_BOMB_HPP
