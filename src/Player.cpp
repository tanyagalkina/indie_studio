#include "../include/Player.hpp"
#include "Character.hpp"
#include "Error.hpp"
#include "VisualMap.hpp"
#include <assert.h>
#include "Bomb.hpp"

Player::Player(SAppContext &ctx, VisualMap &vmap, const int &playerIdx)
    : Character(ctx, vmap, irr::core::vector3df(-250, 0, 250))
{
}

Player::~Player()
{
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

irr::scene::IAnimatedMeshSceneNode *Player::getBody()
{
    return this->body;
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
