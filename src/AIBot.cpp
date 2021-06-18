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

bool AIBot::update(GameEventReceiver &receiver)
{
    move(receiver);
    return dropBomb(receiver);
}

std::string AIBot::serialize()
{
    SerializeHelper s;
    s.beginKey("AIBot");

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

    s.endKey("AIBot");
    return s.getXML();
}

void AIBot::deserialize(std::string xmlCode)
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
