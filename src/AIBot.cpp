#include "AIBot.hpp"
#include "Character.hpp"
#include "Floor.hpp"
#include "vector3d.h"

AIBot::AIBot(SAppContext &ctx, VisualMap &map, const int &playerIdx)
    : Character(ctx, map, playerIdx)
{
    moveIdx = 0;
    goingBack = 0;
    shouldDropBomb = false;
    bombsMax = 1;
    lastSteps.push(this->body->getPosition());
}

AIBot::~AIBot()
{
}

bool AIBot::dropBomb(GameEventReceiver &receiver)
{
    shouldDropBomb = true;
    goingBack = 10;
    return true;
}

bool AIBot::update(GameEventReceiver &receiver)
{
    move(receiver);

    return shouldDropBomb;
}

std::string AIBot::serialize()
{
    SerializeHelper s;
    s.beginKey("AIBot");

    s.addXML(Character::serialize());

    s.endKey("AIBot");
    return s.getXML();
}

bool AIBot::customMove(irr::core::vector3df target)
{
    const irr::u32 now = context->device->getTimer()->getTime();
    auto currentPos = this->body->getPosition();
    auto dir = target - currentPos;

    if (goingBack != 0 && target.getDistanceFrom(currentPos) < 10) {
        std::cout << "Reducing this shit" << std::endl;
        goingBack--;
    }

    frameDeltaTime = (irr::f32)(now - then) / 1000.f;
    then = now;

    dir.Y = 0;

    if (dir.getLength() > MOVEMENT_SPEED * frameDeltaTime) {
        target = currentPos + dir * (MOVEMENT_SPEED * frameDeltaTime) / dir.getLength();
    }

    target.Y = currentPos.Y;
    this->body->setPosition(target);
    return false;
}

Floor::Type AIBot::checkNextMove(irr::core::vector3df &target)
{
    int x = round(abs((target.X + 300) / 50));
    int y = round(abs((target.Z - 300) / 50));

    auto currentMap = map->getMap();

    for (auto [type, coord] : currentMap) {
        if (coord.x == x && coord.y == y) {
            //printf("next\t%d - %d -> %d\n", coord.x, coord.y, (int)type);
            return type;
        }
    }
    std::cout << "here" << std::endl;
    return Floor::Type::EMPTY;
}

void AIBot::move(GameEventReceiver &receiver)
{
    auto next = this->body->getPosition();
    int blockSize = 25;

    //std::cout << "X: " << next.X << " Z: " << next.Z << std::endl;
    //
    std::cout << lastSteps.size() << std::endl;

    //if (goingBack == 0 && lastSteps.size() != 0 && lastSteps.top() != next) {
        //lastSteps.push(next);
    //}
    //if (goingBack != 0 && lastSteps.size() > 2) {
        //lastSteps.pop();

        //auto last = lastSteps.top();

        //if (last.Z < next.Z) {
            //this->body->setRotation(irr::core::vector3df(0, 90, 0));
        //}
        //if (last.Z > next.Z) {
            //this->body->setRotation(irr::core::vector3df(0, 180, 0));
        //}
        //if (last.X < next.X) {
            //this->body->setRotation(irr::core::vector3df(0, 270, 0));
        //}
        //if (last.X > next.X) {
            //this->body->setRotation(irr::core::vector3df(0, 0, 0));
        //}

        //customMove(last);
        //lastSteps.pop();
        //return;
    //}


    //printf("current\t%d - %d\n", abs((int)(next.X + 300) / 50), abs((int)(next.Z - 350) / 50));
    switch (moveIdx % 4) {
        case 0: //UP
            this->body->setRotation(irr::core::vector3df(0, 270, 0));
            next.Z += blockSize;
            break;
        case 1: //right
            this->body->setRotation(irr::core::vector3df(0, 90, 0));
            next.X += blockSize;
            break;
        case 2: //down
            this->body->setRotation(irr::core::vector3df(0, 0, 0));
            next.Z -= blockSize;
            break;
        case 3: //left
            this->body->setRotation(irr::core::vector3df(0, 180, 0));
            next.X -= blockSize;
            break;
    }
    changeMovementState();

    auto type = checkNextMove(next);

    if (type == Floor::Type::WALL) {
        moveIdx++;
    }
    if (type == Floor::Type::BOX) {
        dropBomb(receiver);
    } else {
        shouldDropBomb = false;
    }
    if (type == Floor::Type::EMPTY) {
        customMove(next);
    }
    return;
}
