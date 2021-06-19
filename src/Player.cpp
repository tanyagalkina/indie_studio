#include "../include/Player.hpp"
#include "Character.hpp"
#include "Error.hpp"
#include "VisualMap.hpp"

Player::Player(SAppContext &ctx, VisualMap &vmap, const int &playerIdx)
    : Character(ctx, vmap, playerIdx)
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
void Player::upgradeBombsMax()
{
    bombsMax++;
}


//int Player::calcMiddle(int coordinate)
//{
//    int n = coordinate / 50;
//    int min_x = 50 * n;
//    int max_x = 50 * (n + (n >= 0 && coordinate >= 0 ? + 1 : - 1));
//
//    return abs(min_x - coordinate) < abs(max_x - coordinate) ? min_x : max_x;
//}

bool Player::update(GameEventReceiver &receiver)
{
    move(receiver);
    return dropBomb(receiver);
    // @todo look for bombs, powerups ...
}

//bool Player::getUnlimitedBombs() const
//{
//    return unlimitedBombs;
//}

std::string Player::serialize()
{
    SerializeHelper s;
    s.beginKey("Player");

    s.addXML(Character::serialize());

    s.endKey("Player");
    return s.getXML();
}
