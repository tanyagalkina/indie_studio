/*
** EPITECH PROJECT, 2021
** B_YEP_400_BER_4_1_indiestudio_karl_erik_stoerzel
** File description:
** Bomb.cpp
*/

#include <Bomb.hpp>

Bomb::Bomb(SAppContext &ctx) {
    context = &ctx;
    this->smgr = context->device->getSceneManager();
    this->driver = context->device->getVideoDriver();
    irr::scene::IAnimatedMesh *mesh;

    if ((mesh = smgr->getMesh("media/bomb.3ds")) == nullptr) {
        AssetLoadErrorMac("Can't load 'media/bomb.3ds'");
    }
    if ((this->body = smgr->addAnimatedMeshSceneNode(mesh)) == nullptr) {
        SceneErrorMac("Could not add AnimatedMeshSceneNode");
    }

    this->body->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    this->body->setMaterialTexture(0, driver->getTexture("media/sydney.bmp"));
    this->body->setScale(irr::core::vector3df(.1));

    this->selector = this->smgr->createOctreeTriangleSelector(this->body->getMesh(), this->body, 128);
    this->body->setTriangleSelector(this->selector);
}

void Bomb::drop(const irr::core::vector3df &pos)
{
    this->body->setPosition(pos);
    this->body->setVisible(true);
    // @todo start timer ... explode etc.
}

void Bomb::setPosition(float x, float z) {
    this->body->setPosition(irr::core::vector3d<irr::f32>(x, 45, z));
}

bool Bomb::HandleCollision(Player &player) {
    if (player.getBody()->getTransformedBoundingBox().intersectsWithBox(this->body->getTransformedBoundingBox())) {
        this->body->setVisible(false);
        std::cout << "hit" << std::endl;
        return true;
    }
    return false;
}