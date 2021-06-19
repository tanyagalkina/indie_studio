#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "AppContext.hpp"
#include "Character.hpp"
#include "IAnimatedMesh.h"
#include "IAnimatedMeshMD2.h"
#include "IEventReceiver.h"
#include "ISceneManager.h"
#include "ITriangleSelector.h"
#include "Keycodes.h"
#include "VisualMap.hpp"
#include "vector3d.h"
#include <irrlicht.h>
#include "IAnimatedMeshMD2.h"
#include "Timer.hpp"
#include "PowerUpEnum.hpp"
#include "IXML.hpp"

class GameEventReceiver : public irr::IEventReceiver
{
public:
	virtual bool OnEvent(const irr::SEvent& event)
	{
		if (event.EventType == irr::EET_KEY_INPUT_EVENT)
			KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
		return false;
	}

	virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const
	{
		return KeyIsDown[keyCode];
	}

	void setIsKeyDown(irr::EKEY_CODE keyCode, bool value)
	{
        KeyIsDown[keyCode] = value;
    }

	GameEventReceiver()
	{
		for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; i++)
			KeyIsDown[i] = false;
	}

private:
	bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
};

/* up, right, down, left, bomb */
static const irr::EKEY_CODE keyCodes[2][5] = {
    { irr::KEY_KEY_W, irr::KEY_KEY_D, irr::KEY_KEY_S, irr::KEY_KEY_A, irr::KEY_SPACE},
    { irr::KEY_UP, irr::KEY_RIGHT, irr::KEY_DOWN, irr::KEY_LEFT,
      irr::KEY_RETURN}
};

class Player : public Character
{
public:
    Player(SAppContext &ctx, VisualMap &map, const int &playerIdx = 0);
    virtual ~Player();
    bool update(GameEventReceiver &receiver) final;
    //int calcMiddle(int coordinate);
    std::string serialize() final;
    //int bombsMax = 2;
    void upgradeBombsMax();
    //bool getUnlimitedBombs() const;

private:
    enum keyDirection {
        UP = 0,
        RIGHT,
        DOWN,
        LEFT,
        DROP_BOMB,
    };

    /* movement */
    void move(GameEventReceiver &receiver) final;
    bool dropBomb(GameEventReceiver &receiver) final;

private:

//    std::vector<Bomb> bombs; // @todo put this into the overall game class with all bombs on the field

    MyList<std::pair<Timer, PowerUpType>> powerUpTimers;
};

#endif //PLAYER_HPP_
