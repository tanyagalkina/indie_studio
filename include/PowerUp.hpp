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
public:
    explicit PowerUp(SAppContext &ctx, const std::string& meshPath, const std::string& texturePath) : context
    (ctx){
        this->smgr = context->device->getSceneManager();
        this->driver = context->device->getVideoDriver();

        irr::scene::IAnimatedMesh *mesh;

        if ((mesh = smgr->getMesh(meshPath)) == NULL) {
            AssetLoadErrorMac("Can't load: " + meshPath);
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
};

#endif //B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_POWERUP_HPP
