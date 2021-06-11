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
#include "Error.hpp"

class Bomb : public ICollidable
{
protected:
    bool isExisting = true;
    GameEventReceiver *receiver;

public:
    explicit Bomb(SAppContext &ctx)
    {
        context = &ctx;
        this->smgr = context->device->getSceneManager();
        this->driver = context->device->getVideoDriver();

        irr::scene::IAnimatedMesh *mesh;

        if ((mesh = smgr->getMesh("media/bomb.3ds")) == NULL) {
            AssetLoadErrorMac("Can't load 'media/bomb.3ds'");
        }
        if ((this->body = smgr->addAnimatedMeshSceneNode(mesh)) == NULL) {
            SceneErrorMac("Could not add AnimatedMeshSceneNode");
        }

        this->body->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        this->body->setMaterialTexture(0, driver->getTexture("media/sydney.bmp"));
        this->body->setScale(irr::core::vector3df(.1));

        this->selector = this->smgr->createOctreeTriangleSelector(this->body->getMesh(), this->body, 128);
        this->body->setTriangleSelector(this->selector);
    }

    void drop(const irr::core::vector3df &pos)
    {
        this->body->setPosition(pos);
        this->body->setVisible(true);
        // @todo start timer ... explode etc.
    }

    ~Bomb() override = default;
    void setPosition(float x, float z) final {
        this->body->setPosition(irr::core::vector3d<irr::f32>(x, 45, z));
    }

    bool HandleCollision(Player &player) override
    {
        if (player.getBody()->getTransformedBoundingBox().intersectsWithBox(
                    this->body->getTransformedBoundingBox()))
        {
            this->body->setVisible(false);
            std::cout << "hit" << std::endl;
            return true;
        }
        return false;
    }
};

#endif //B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_BOMB_HPP
