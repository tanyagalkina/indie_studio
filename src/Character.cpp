#include "Character.hpp"

void Character::changeMovementState()
{
    if (currentMovementState == irr::scene::EMAT_STAND) {
        currentMovementState = irr::scene::EMAT_RUN;
        this->body->setMD2Animation(currentMovementState);
    }
}

void Character::moveUp(irr::core::vector3df &pos)
{
    this->body->setRotation(irr::core::vector3df(0, 270, 0));
    pos.Z += (MOVEMENT_SPEED * frameDeltaTime) * extraSpeedFactor;
    changeMovementState();
}

void Character::moveDown(irr::core::vector3df &pos)
{
    this->body->setRotation(irr::core::vector3df(0, 90, 0));
    pos.Z -= (MOVEMENT_SPEED * frameDeltaTime) * extraSpeedFactor;
    changeMovementState();
}

void Character::moveRight(irr::core::vector3df &pos)
{
    this->body->setRotation(irr::core::vector3df(0, 0, 0));
    pos.X += (MOVEMENT_SPEED * frameDeltaTime) * extraSpeedFactor;
    changeMovementState();
}

void Character::moveLeft(irr::core::vector3df &pos)
{
    this->body->setRotation(irr::core::vector3df(0, 180, 0));
    pos.X -= (MOVEMENT_SPEED * frameDeltaTime) * extraSpeedFactor;
    changeMovementState();
}
