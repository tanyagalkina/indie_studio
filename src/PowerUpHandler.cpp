/*
** EPITECH PROJECT, 2021
** B_YEP_400_BER_4_1_indiestudio_karl_erik_stoerzel
** File description:
** PowerUpHandler.cpp
*/

#include "PowerUpHandler.hpp"

void PowerUpHandler::loop(GameEventReceiver &receiver)
{
    playerRef.update(receiver);
    MyList<MyList<std::pair<Timer, PowerUpType>>::iterator> erasablePair;
    MyList<MyList<PowerUp *>::iterator> erasablePowerUps;


//    std::cout << playerRef.getBody()->getPosition().X << " ";
//    std::cout << playerRef.getBody()->getPosition().Z << " ";
//    std::cout << playerRef.getBody()->getPosition().Y << std::endl;
    for (auto it = allPowerUps.begin(); it!= allPowerUps.end(); it++)
    {
        if ((*it)->HandleCollision(playerRef))
        {
            auto pu = (*it)->getTimerAndType();
            pu.first.startTimer();
            currentPowerUps.push_back(pu);
            erasablePowerUps.push_back(it);
        }
    }
    for (auto & it : erasablePowerUps)
    {
        allPowerUps.erase(it);
    }

    playerRef.setExtraSpeed(1);
    playerRef.setFire(false);
    playerRef.setUnlimitedBombs(false);

    for (auto it = currentPowerUps.begin(); it != currentPowerUps.end(); it++)
    {
        if (it->first.isFinished())
            erasablePair.push_back(it);
        else
            handlePlayerItems(it->second);
    }
    for (auto & it : erasablePair)
    {
        currentPowerUps.erase(it);
    }
}

void PowerUpHandler::addPowerUp(PowerUpType type, float x, float z)
{
    PowerUp *item = nullptr;
    switch (type)
    {
        case PowerUpType::SpeedUp_t:
            item = new SpeedUp(*appContext);
            break;
        case PowerUpType::FireUp_t:
            item = new FireUp(*appContext);
            break;
        case PowerUpType::BombUp_t:
            item = new BombUp(*appContext);
            break;
        default:
            break;
    }
    if (item)
        item->setPosition(x, z);
    else
        SceneErrorMac("uncoded powerup");
    allPowerUps.push_back(item);
}

void PowerUpHandler::handlePlayerItems(PowerUpType type)
{
    switch (type)
    {
        case PowerUpType::SpeedUp_t:
            playerRef.setExtraSpeed(2);
            break;
        case PowerUpType::FireUp_t:
            playerRef.setFire(true);
            break;
        case PowerUpType::BombUp_t:
            playerRef.setUnlimitedBombs(true);
        default:
            break;
    }
}
