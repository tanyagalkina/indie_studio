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
    _surround = surround;
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
    //_explosions
    auto playerX = player->calcMiddle(pos.X);
    auto playerZ = player->calcMiddle(pos.Z);
    auto bombX = player->calcMiddle(body->getPosition().X);
    auto bombZ = player->calcMiddle(body->getPosition().Z);

    float up = _surround[0];
    float right = _surround[1];
    float down = _surround[2];
    float left = _surround[3];

    int tanya = 0;
    while (up > 0.1) {

        if (bombX == playerX && (bombZ == (playerZ - tanya)))
            return true;
        else {
            up -= 0.01;
            tanya += 50;
        }
    }
    tanya = 0;

    while (left < -0.1) {
        if (bombZ == playerZ && (bombX == (playerX - tanya)))
            return true;
        else {
            left += 0.01;
            tanya += 50;
        }
    }
    tanya = 0;

    while (down < -0.1) {
        if (bombX == playerX && (bombZ == (playerZ + tanya)))
            return true;
        else {
            down += 0.01;
            tanya += 50;
        }
    }
    tanya = 0;
    while (right > 0.1) {
        if (bombZ == playerZ && (bombX == (playerX + tanya)))
            return true;
        else {
            right -= 0.01;
            tanya += 50;
        }
    }

    /*if ((bombX == playerX && (bombZ == playerZ
                           || bombZ == playerZ - 50 || bombZ == playerZ - 100
                           || bombZ == playerZ+ 50 || bombZ == playerZ + 100) ||
         (bombZ == playerZ && (bombX == playerX
                            || bombX == playerX - 50 || bombX == playerX - 100
                            || bombX == playerX + 50 || bombX == playerX + 100))))
        return true;*/
    return false;
}

MyList<Explosion *> Bomb::getExplosions()
{
    return _explosions;
}
