#include "AIBot.hpp"
#include "Character.hpp"

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

std::string AIBot::serialize()
{
    return "Fuck off";
}

void AIBot::deserialize(std::string xmlCode)
{
}

void AIBot::move(GameEventReceiver &receiver)
{
    const irr::u32 now = context->device->getTimer()->getTime();

    frameDeltaTime = (irr::f32)(now - then) / 1000.f;
    then = now;

    auto pos = body->getPosition();
    auto savedPos = pos;

    switch (moveIdx % 4) {
        case 0:
            moveUp(pos);
            break;
        case 1:
            moveRight(pos);
            break;
        case 2:
            moveDown(pos);
            break;
        case 3:
            moveLeft(pos);
            break;
    }

    if (savedPos.equals(pos)) {
        moveIdx++;
    }

    body->setPosition(pos);
}
