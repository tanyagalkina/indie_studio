/*
** EPITECH PROJECT, 2021
** B_YEP_400_BER_4_1_indiestudio_karl_erik_stoerzel
** File description:
** Bomb.cpp
*/

#include <Bomb.hpp>


Bomb::Bomb(SAppContext &ctx, Audio *sounds, Player *player) : _player(player)
{
    _sounds = sounds;
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
    this->body->setScale(irr::core::vector3df(.4));

    this->selector = this->smgr->createOctreeTriangleSelector(this->body->getMesh(), this->body, 128);
    this->body->setTriangleSelector(this->selector);

    auto position = _player->getBody()->getPosition();
    position.X = _player->calcMiddle(position.X);
    position.Z = _player->calcMiddle(position.Z);
    position.Y = 10;

    this->body->setVisible(true);
    this->body->setPosition(position);
}

Player *Bomb::getPLayer() const
{
    return _player;
}

void Bomb::explosion()
{
    this->body->setVisible(false);

}

void Bomb::drop()
{
    timer.startTimer();
}

void Bomb::setPosition(float x, float z) {}

bool Bomb::HandleCollision(Player &player) {
    if (player.getBody()->getTransformedBoundingBox().intersectsWithBox(this->body->getTransformedBoundingBox())) {
        this->body->setVisible(false);
        std::cout << "hit" << std::endl;
        return true;
    }
    return false;
}