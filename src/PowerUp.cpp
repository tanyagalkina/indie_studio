/*
** EPITECH PROJECT, 2021
** B_YEP_400_BER_4_1_indiestudio_karl_erik_stoerzel
** File description:
** PowerUp.cpp
*/

#include "IAnimatedMesh.h"
#include <PowerUp.hpp>

PowerUp::PowerUp(SAppContext &ctx, const irr::core::string<irr::fschar_t> &meshPath,
                 const irr::core::string<irr::fschar_t> &texturePath)
{

    context = &ctx;
    this->smgr = context->device->getSceneManager();
    this->driver = context->device->getVideoDriver();

    //irr::scene::IAnimatedMesh *mesh;

    //if ((mesh = smgr->getMesh(meshPath)) == NULL)
        //AssetLoadErrorMac("powerup");
    //if ((this->body = smgr->addAnimatedMeshSceneNode(mesh)) == NULL)
        //SceneErrorMac("powerup");

    //this->body = smgr->addAnimatedMeshSceneNode(smgr->getMesh("./media/asset/powerup/powerUpP.obj"));
    ////this->body = smgr->addAnimatedMeshSceneNode(smgr->getMesh("media/boot.3ds"));

    //this->body->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    //auto *texture = driver->getTexture("media/WoodPlanks_Normal.png");

    //if (texture == NULL)
        //std::cout << "--------------------------__" << std::endl;
    //this->body->setMaterialTexture(0, texture);
    //this->body->setScale(irr::core::vector3df(.04));
    //this->body->setPosition(irr::core::vector3df(-300, 30, 300));

    this->body->setMaterialTexture(
        0,driver->getTexture("./media/asset/pillier/Texture_pillier_Selfillum_Orange.png"));
    this->body->setMaterialTexture(
        1,driver->getTexture("./media/asset/pillier/Texture_pillier_alpha_Orange.png"));
    this->body->setMaterialFlag(irr::video::EMF_LIGHTING, true);
    this->body->setScale(irr::core::vector3df(0.7, 0.7, 0.7));
    this->body->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
    this->body->setRotation(irr::core::vector3df(130, 0, 0));
    this->body->addAnimator(smgr->createRotationAnimator(irr::core::vector3df(0, 1, 0)));

    //
//    irr::scene::IAnimatedMesh *mesh;
//    if ((mesh = smgr->getMesh("meshPath")) == NULL) {
//        AssetLoadErrorMac("Can't load mesh");
//    }
//    if ((this->body = smgr->addAnimatedMeshSceneNode(mesh)) == NULL) {
//        SceneErrorMac("Could not add AnimatedMeshSceneNode");
//    }
//    std::cout << "here" << std::endl;
//    //        this->body->setMD2Animation(currentMovementState);
//    this->body->setMaterialFlag(irr::video::EMF_LIGHTING, false);
//    this->body->setMaterialTexture(1, driver->getTexture(texturePath));
//    this->body->setMaterialTexture(0, driver->getTexture(
//        "./media/textures/textures/swiatlo1obj_1001_BaseColor.jpg"
//        ));
//    this->body->setMaterialTexture(2, driver->getTexture(
//        "./media/textures/textures/swiatlo1obj_1001_Emissive.jpg"
//    ));
//    this->body->setMaterialTexture(3, driver->getTexture(
//        "./media/textures/textures/swiatlo1obj_1001_Roughness.jpg"
//    ));

    /* lift the player up a bit */
    auto pos = this->body->getPosition();
    pos.Y += 45;
    this->body->setPosition(pos);

    this->selector = this->smgr->createOctreeTriangleSelector(this->body->getMesh(), this->body,
                                                              128);
    this->body->setTriangleSelector(this->selector);
}

void PowerUp::setPosition(float x, float z)
{
    this->body->setPosition(irr::core::vector3d<irr::f32>(x, 45, z));
}

bool PowerUp::HandleCollision(Player &player)
{
    if (player.getBody()->getTransformedBoundingBox().intersectsWithBox(
        this->body->getTransformedBoundingBox()))
    {
//        this->body->setVisible(false);
        std::cout << "hit" << std::endl;
        return true;
    }
    return false;
}
