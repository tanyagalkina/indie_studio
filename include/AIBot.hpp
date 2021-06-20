#ifndef AI_BOT_HPP_
#define AI_BOT_HPP_

#include "AppContext.hpp"
#include "Character.hpp"
#include <functional>
#include <stack>


class AIBot : public Character
{
public:
    AIBot(SAppContext &ctx, VisualMap &map, const int &playerIdx = 0);
    virtual ~AIBot();
    bool update(GameEventReceiver &receiver) final;
    std::string serialize() final;
private:
    /* movement */
    void move(GameEventReceiver &receiver) final;
    bool customMove(irr::core::vector3df target);
    bool dropBomb(GameEventReceiver &receiver) final;
    void checkNextMove(irr::core::vector3df &target, GameEventReceiver &receiver);

private:
    int moveIdx;
    bool shouldDropBomb;
    std::stack<irr::core::vector3df> lastSteps;
    int goingBack;
    Floor::Type _lastType;
};

#endif //AI_BOT_HPP_
