#include "../include/Player.hpp"
#include "Error.hpp"
#include "VisualMap.hpp"
#include <assert.h>
#include "Bomb.hpp"

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

    if (playerIndex == 0) {
        pos.X = -250;
        pos.Z = 250;
    }
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

 bool Player::dropBomb(GameEventReceiver &receiver)
{
    if (receiver.IsKeyDown(keyCodes[this->playerIndex][this->DROP_BOMB])) {
        return true;
//        bombs.push_back(b);
    }
    return false;
}

bool Player::update(GameEventReceiver &receiver)
{
    move(receiver);
    return dropBomb(receiver);
    // @todo look for bombs, powerups ...
}

/* use this function to create Collision between multiple Players or monsters */
void Player::addCollision(irr::scene::IAnimatedMeshSceneNode *_body)
{
    auto *anim = smgr->createCollisionResponseAnimator(selector, _body,
            irr::core::vector3df(10, 10, 10),
            irr::core::vector3df(0, 0, 0));
    _body->addAnimator(anim);
    anim->drop();
}

irr::scene::IAnimatedMeshSceneNode *Player::getBody()
{
    return this->body;
}

bool Player::checkCollision(const irr::scene::IAnimatedMeshSceneNode *object) const
{
    return object->getTransformedBoundingBox().intersectsWithBox(this->body->getTransformedBoundingBox());
}

void Player::setExtraSpeed(irr::f32 newExtraSpeed)
{
    this->extraSpeedFactor = newExtraSpeed;
}

bool Player::isAlive() const
{
    return alive;
}

void Player::kill()
{
    alive = false;
}

void Player::revive()
{
    alive = true;
}

void Player::setFire(bool enable)
{
    fireUp = enable;
}

void Player::setUnlimitedBombs(bool enabled)
{
    unlimitedBombs = enabled;
}

std::string Player::serialize()
{
    SerializeHelper s;
    s.beginKey("Player");

    s.beginKey("Position");
    s.addKeyValue("X", std::to_string(this->getBody()->getPosition().X));
    s.addKeyValue("Y", std::to_string(this->getBody()->getPosition().Y));
    s.addKeyValue("Z", std::to_string(this->getBody()->getPosition().Z));
    s.endKey("Position");

    s.addKeyValue("playerIndex", std::to_string(playerIndex));
    s.addKeyValue("extraSpeedFactor", std::to_string(extraSpeedFactor));
    s.addKeyValue("alive", std::to_string(alive));
    s.addKeyValue("fireUp", std::to_string(fireUp));
    s.addKeyValue("unlimitedBombs", std::to_string(unlimitedBombs));

    s.endKey("Player");
    return s.getXML();
}

void Player::deserialize(std::string xmlCode)
{
    std::string xpos = SerializeHelper::FindKeyValue(xmlCode, "X");
    std::string ypos = SerializeHelper::FindKeyValue(xmlCode, "Y");
    std::string zpos = SerializeHelper::FindKeyValue(xmlCode, "Z");
    std::string playerIndexS = SerializeHelper::FindKeyValue(xmlCode, "playerIndex");
    std::string aliveS = SerializeHelper::FindKeyValue(xmlCode, "alive");
    std::string fireUpS = SerializeHelper::FindKeyValue(xmlCode, "fireUp");
    std::string unlimitedBombsS = SerializeHelper::FindKeyValue(xmlCode, "unlimitedBombs");

    body->setPosition(irr::core::vector3df(stof(xpos), stof(ypos), stof(zpos)));
    playerIndex = stoi(playerIndexS);
    alive = stoi(aliveS);
    fireUp = stoi(fireUpS);
    unlimitedBombs = stoi(unlimitedBombsS);
}
