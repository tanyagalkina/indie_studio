#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "AppContext.hpp"
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

	GameEventReceiver()
	{
		for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; i++)
			KeyIsDown[i] = false;
	}

private:
	bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
};

/* up, right, down, left */
static const irr::EKEY_CODE keyCodes[2][4] = {
    { irr::KEY_KEY_W, irr::KEY_KEY_D, irr::KEY_KEY_S, irr::KEY_KEY_A },
    { irr::KEY_UP, irr::KEY_RIGHT, irr::KEY_DOWN, irr::KEY_LEFT }
};

class Player
{
public:
    enum keyDirection {
        UP = 0,
        RIGHT,
        DOWN,
        LEFT
    };
    Player(SAppContext &ctx, VisualMap &map, const int &playerIdx = 0);
    ~Player();
    void update(GameEventReceiver &receiver);
    void setExtraSpeed(irr::f32 newExtraSpeed);
    irr::scene::IAnimatedMeshSceneNode *getBody();

private:
    /* movement */
    void changeMovementState();
    void move(GameEventReceiver &receiver);
    void moveUp(irr::core::vector3df &pos);
    void moveDown(irr::core::vector3df &pos);
    void moveLeft(irr::core::vector3df &pos);
    void moveRight(irr::core::vector3df &pos);
    /* initialize */
    void initPlayer();
    bool checkCollision(const irr::scene::IAnimatedMeshSceneNode *object) const;

    /* collision */
    void addCollision(irr::scene::IAnimatedMeshSceneNode *_body);

private:
    /* general */
    SAppContext *context;
    irr::scene::ISceneManager *smgr;
    irr::video::IVideoDriver *driver;
    irr::scene::IAnimatedMeshSceneNode *body;

    /* movement */
    irr::u32 then;
    int playerIndex;
	irr::f32 MOVEMENT_SPEED;
    irr::f32 frameDeltaTime;
    irr::scene::EMD2_ANIMATION_TYPE currentMovementState;

    /* collision */
    irr::scene::ITriangleSelector *selector;

    /* map needed to add collision to it */
    VisualMap *map;

    /* PowerUp handling */
    //Maybe we can use something like this to time the duration after you hit a
    //speed powerup ... we can reuse this class for bombs too.
    irr::f32 extraSpeedFactor; /* used for the SpeedUp powerUp */
};

#endif //PLAYER_HPP_
