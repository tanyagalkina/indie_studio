/*
** EPITECH PROJECT, 2021
** B_YEP_400_BER_4_1_indiestudio_karl_erik_stoerzel
** File description:
** PowerUp.hpp
*/

#ifndef B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_POWERUP_HPP
#define B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_POWERUP_HPP

#include "ICollidable.hpp"

class PowerUp : public ICollidable
{
protected:
    bool isExisting = true;
public:
    ~PowerUp() override = default;
    explicit PowerUp(SAppContext &ctx, const irr::core::string<irr::fschar_t>& meshPath, const
    irr::core::string<irr::fschar_t> &texturePath)
    {
        context = &ctx;
        this->smgr = context->device->getSceneManager();
        this->driver = context->device->getVideoDriver();

        irr::scene::IAnimatedMesh *mesh;
        if ((mesh = smgr->getMesh(meshPath)) == NULL) {
            AssetLoadErrorMac("Can't load mesh");
        }
        if ((this->body = smgr->addAnimatedMeshSceneNode(mesh)) == NULL) {
            SceneErrorMac("Could not add AnimatedMeshSceneNode");
        }

//        this->body->setMD2Animation(currentMovementState);
        this->body->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        this->body->setMaterialTexture(0, driver->getTexture(texturePath));

        /* lift the player up a bit */
        auto pos = this->body->getPosition();
        pos.Y += 45;
        this->body->setPosition(pos);

        this->selector = this->smgr->createOctreeTriangleSelector(this->body->getMesh(), this->body);
        this->body->setTriangleSelector(this->selector);
    }
    bool checkExisting() const
    {
        return this->isExisting;
    }
    void setPosition(float x, float z) final {
        this->body->setPosition(irr::core::vector3d<irr::f32>(x, 45, z));
    }
};

#endif //B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_POWERUP_HPP
