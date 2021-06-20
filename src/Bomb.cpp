/*
** EPITECH PROJECT, 2021
** B_YEP_400_BER_4_1_indiestudio_karl_erik_stoerzel
** File description:
** Bomb.cpp
*/

#include <Bomb.hpp>
#include <Explosion.hpp>


Bomb::Bomb(SAppContext &ctx, Audio *sounds, Character *player) : _player(player)
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

    _position = _player->getBody()->getPosition();
    _position.X = _player->calcMiddle(_position.X);
    _position.Z = _player->calcMiddle(_position.Z);
    _position.Y = 10;

    this->body->setVisible(true);
    this->body->setPosition(_position);
}

Character *Bomb::getPLayer() const
{
    return _player;
}

void Bomb::initExplosion(std::vector<float> surround)
{
    this->_exploded = true;
    irr::core::vector3df up = irr::core::vector3df(0.0f, 0.0f, surround[0]); ///surround[0]
    irr::core::vector3df right = irr::core::vector3df(surround[1], 0.0f, 0.0f); ///surround[1]
    irr::core::vector3df down = irr::core::vector3df(0.0f, 0.0f, surround[2]); ///surround[2]
    irr::core::vector3df left = irr::core::vector3df(surround[3], 0.0f, 0.0f); ///surround[3]
    this->_explosions.push_back(new Explosion(this->_position, up, this->context->device));
    this->_explosions.push_back(new Explosion(this->_position, right, this->context->device));
    this->_explosions.push_back(new Explosion(this->_position, down, this->context->device));
    this->_explosions.push_back(new Explosion(this->_position, left, this->context->device));

    this->body->setVisible(false);
    this->timer = Timer(700);
    timer.startTimer();
}

void Bomb::stopExplosion()
{
    for (auto it : this->_explosions) {
        it->_particleSystemSceneNode->setVisible(false);
        delete it;
    }
    this->_explosions.clear();
}

void Bomb::drop()
{
    timer.startTimer();
}

void Bomb::setPosition(float x, float z) {}

bool Bomb::HandleCollision(Character &player)
{
    if (player.getBody()->getTransformedBoundingBox().intersectsWithBox(this->body->getTransformedBoundingBox())) {
        this->body->setVisible(false);
        std::cout << "hit" << std::endl;
        return true;
    }
    return false;
}

bool Bomb::beShureCollision(Character *player, const irr::core::vector3df& pos)
{
    auto posx = player->calcMiddle(pos.X);
    auto posz = player->calcMiddle(pos.Z);
    auto posxB = player->calcMiddle(body->getPosition().X);
    auto poszB = player->calcMiddle(body->getPosition().Z);
    if ((posxB == posx && (poszB == posz
                           || poszB == posz - 50 || poszB == posz - 100
                           || poszB == posz + 50 || poszB == posz + 100) ||
         (poszB == posz && (posxB == posx
                            || posxB == posx - 50 || posxB == posx - 100
                            || posxB == posx + 50 || poszB == posx + 100))))
        return true;
    return false;
}

MyList<Explosion *> Bomb::getExplosions()
{
    return _explosions;
}
