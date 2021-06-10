#include "../include/Player.hpp"
#include "Error.hpp"
#include "IAnimatedMeshMD2.h"
#include "VisualMap.hpp"
#include <assert.h>

void Player::initPlayer()
{
    irr::scene::IAnimatedMesh *mesh;

    if ((mesh = smgr->getMesh("media/sydney.md2")) == NULL) {
        AssetLoadErrorMac("Can't load 'media/sydney.md2'");
    }
    if ((this->body = smgr->addAnimatedMeshSceneNode(mesh)) == NULL) {
        SceneErrorMac("Could not add AnimatedMeshSceneNode");
    }

    this->body->setMD2Animation(currentMovementState);
    this->body->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    this->body->setMaterialTexture(0, driver->getTexture("media/sydney.bmp"));

    /* lift the player up a bit */
    auto pos = this->body->getPosition();
    pos.Y += 45;
    this->body->setPosition(pos);
}

Player::Player(SAppContext &ctx, VisualMap &vmap, const int &playerIdx)
    : context(&ctx), playerIndex(playerIdx), map(&vmap),
    MOVEMENT_SPEED(100.f), currentMovementState(irr::scene::EMAT_STAND),
    extraSpeedFactor(1.f)
{
    assert(playerIndex < 2); // just for now because it would crash
    this->smgr = context->device->getSceneManager();
    this->driver = context->device->getVideoDriver();
    then = context->device->getTimer()->getTime();

    initPlayer();

    this->selector = this->smgr->createOctreeTriangleSelector(this->body->getMesh(), this->body);
    this->body->setTriangleSelector(this->selector);

    /* adding collision between the player and the map */
    map->addCollision(body);
}

Player::~Player()
{
    this->selector->drop();
}

void Player::changeMovementState()
{
    if (currentMovementState == irr::scene::EMAT_STAND) {
        currentMovementState = irr::scene::EMAT_RUN;
        this->body->setMD2Animation(currentMovementState);
    }
}

void Player::moveUp(irr::core::vector3df &pos)
{
    this->body->setRotation(irr::core::vector3df(0, 270, 0));
    pos.Z += (MOVEMENT_SPEED * frameDeltaTime) * extraSpeedFactor;
    changeMovementState();
}

void Player::moveDown(irr::core::vector3df &pos)
{
    this->body->setRotation(irr::core::vector3df(0, 90, 0));
    pos.Z -= (MOVEMENT_SPEED * frameDeltaTime) * extraSpeedFactor;
    changeMovementState();
}

void Player::moveRight(irr::core::vector3df &pos)
{
    this->body->setRotation(irr::core::vector3df(0, 0, 0));
    pos.X += (MOVEMENT_SPEED * frameDeltaTime) * extraSpeedFactor;
    changeMovementState();
}

void Player::moveLeft(irr::core::vector3df &pos)
{
    this->body->setRotation(irr::core::vector3df(0, 180, 0));
    pos.X -= (MOVEMENT_SPEED * frameDeltaTime) * extraSpeedFactor;
    changeMovementState();
}

void Player::move(GameEventReceiver &receiver)
{
    const irr::u32 now = context->device->getTimer()->getTime();

    frameDeltaTime = (irr::f32)(now - then) / 1000.f;
    then = now;

    auto pos = body->getPosition();

    if (receiver.IsKeyDown(keyCodes[this->playerIndex][this->UP]))
        moveUp(pos);
    else if (receiver.IsKeyDown(keyCodes[this->playerIndex][this->DOWN]))
        moveDown(pos);
    else if (receiver.IsKeyDown(keyCodes[this->playerIndex][this->RIGHT]))
        moveRight(pos);
    else if (receiver.IsKeyDown(keyCodes[this->playerIndex][this->LEFT]))
        moveLeft(pos);
    else {
        currentMovementState = irr::scene::EMAT_STAND;
        this->body->setMD2Animation(currentMovementState);
    }
    body->setPosition(pos);
}

void Player::update(GameEventReceiver &receiver)
{
    move(receiver);
    // @todo look for bombs, powerups ...
}

irr::scene::IAnimatedMeshSceneNode *Player::getBody()
{
    return this->body;
}


bool Player::checkCollision(const irr::scene::IAnimatedMeshSceneNode *object) const
{
    return object->getTransformedBoundingBox().intersectsWithBox(this->body->getTransformedBoundingBox());
}
