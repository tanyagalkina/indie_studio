#include "AIBot.hpp"
#include "Character.hpp"
#include "Floor.hpp"
#include "vector3d.h"

AIBot::AIBot(SAppContext &ctx, VisualMap &map, const int &playerIdx)
    : Character(ctx, map, playerIdx)
{
    moveIdx = 0;
}

AIBot::~AIBot()
{
}

bool AIBot::dropBomb(GameEventReceiver &receiver)
{
    return false;
}

bool AIBot::update(GameEventReceiver &receiver)
{
    move(receiver);
    return dropBomb(receiver);
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

    //if (target == currentPos) {
        //return true;
    //}

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

void show_template(MyList<std::pair<Floor::Type, Coordinate>> mapTemplate);

Floor::Type AIBot::checkNextMove(irr::core::vector3df &target)
{
    int x = (target.X + 250) / 50;
    int y = (target.Z - 250) / 50;

    //printf("x: %d, y: %d\n", x, y);

    auto currentMap = map->getMap();

    for (auto [type, coord] : currentMap) {
        if (coord.x == x && coord.y == y) {
            printf("next\t%d - %d -> %d\n", coord.x, coord.y, (int)type);
            return type;
        }
    }
    std::cout << "here" << std::endl;
    return Floor::Type::EMPTY;
}

void AIBot::move(GameEventReceiver &receiver)
{
    auto next = this->body->getPosition();
    int blockSize = 50;

    printf("current\t%d - %d\n", (int)((next.X + 250) / 50), (int)((next.Z - 250) / 50));
    std::cout << moveIdx << std::endl;
    switch (moveIdx % 4) {
        case 0: //UP
            next.Z += blockSize;
            break;
        case 1: //right
            next.X += blockSize;
            break;
        case 2: //down
            next.Z -= blockSize;
            break;
        case 3: //left
            next.X -= blockSize;
            break;
    }

    auto type = checkNextMove(next);

    //std::cout << "type: " << (int)type << std::endl;

    if (type == Floor::Type::WALL) {
        moveIdx++;
    }
    if (type == Floor::Type::BOX || type == Floor::Type::TILE) {
        dropBomb(receiver);
    }
    if (type == Floor::Type::EMPTY) {
        customMove(next);
    }
    return;
}
