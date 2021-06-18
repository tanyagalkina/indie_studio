#ifndef AI_BOT_HPP_
#define AI_BOT_HPP_

#include "AppContext.hpp"
#include "Character.hpp"
#include <functional>



class AIBot : public Character
{
public:
    AIBot(SAppContext &ctx, VisualMap &map, const int &playerIdx = 0);
    virtual ~AIBot();
    bool update(GameEventReceiver &receiver) final;
    std::string serialize() final;
    void deserialize(std::string xmlCode) final;
private:
    /* movement */
    void move(GameEventReceiver &receiver) final;
    bool dropBomb(GameEventReceiver &receiver) final;

private:
    int moveIdx;
};

#endif //AI_BOT_HPP_
