/*
** EPITECH PROJECT, 2021
** B_YEP_400_BER_4_1_indiestudio_karl_erik_stoerzel
** File description:
** Bomb.cpp
*/

#include <B.hpp>


Bomb::Bomb(SAppContext &ctx, const irr::core::string<irr::fschar_t> &meshPath,
                 const irr::core::string<irr::fschar_t> &texturePath)
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
    std::cout << "here" << std::endl;
    //        this->body->setMD2Animation(currentMovementState);
    this->body->setMaterialFlag(irr::video::EMF_LIGHTING, false);
//    this->body->setScale(irr::core::vector3df(18, 18, 8));
    this->body->setMaterialTexture(1, driver->getTexture(texturePath));
    this->body->setMaterialTexture(0, driver->getTexture(
            "./media/textures/textures/swiatlo1obj_1001_BaseColor.jpg"
    ));
    this->body->setMaterialTexture(2, driver->getTexture(
            "./media/textures/textures/swiatlo1obj_1001_Emissive.jpg"
    ));
    this->body->setMaterialTexture(3, driver->getTexture(
            "./media/textures/textures/swiatlo1obj_1001_Roughness.jpg"
    ));

    /* lift the player up a bit */
    auto pos = this->body->getPosition();
    pos.Y += 45;
    this->body->setPosition(pos);

    this->selector = this->smgr->createOctreeTriangleSelector(this->body->getMesh(), this->body,
                                                              128);
    this->body->setTriangleSelector(this->selector);
}

void Bomb::setPosition(float x, float z)
{
    this->body->setPosition(irr::core::vector3d<irr::f32>(x, 45, z));
}

bool Bomb::HandleCollision(Player &player)
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