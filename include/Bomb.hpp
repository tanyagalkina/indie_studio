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
#include "Explosion.hpp"

class Bomb : public ICollidable
{
private:
    Audio* _sounds;
    Character *_player;
    irr::core::vector3df _position;
    MyList<Explosion*> _explosions; // 4x in each direction
public:
    explicit Bomb(SAppContext &ctx, Audio *sounds, Character *player);
    ~Bomb() override = default;
    [[nodiscard]] Character *getPLayer() const;
    bool over = false;
    Timer timer = Timer(3000);
    void drop();
    void initExplosion(std::vector<float> surround);
    void stopExplosion();
    void setPosition(float x, float z) final;
    bool HandleCollision(Character &player) final;
    bool beShureCollision(Character *calculator, const irr::core::vector3df& pos);
    MyList<Explosion*> getExplosions();
    bool _exploded = false;
};

#endif //B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_BOMB_HPP
