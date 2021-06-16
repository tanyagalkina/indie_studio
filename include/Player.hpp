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

	GameEventReceiver()
	{
		for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; i++)
			KeyIsDown[i] = false;
	}

private:
	bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
};

/* up, right, down, left */
static const irr::EKEY_CODE keyCodes[2][5] = {
    { irr::KEY_KEY_W, irr::KEY_KEY_D, irr::KEY_KEY_S, irr::KEY_KEY_A, irr::KEY_SPACE},
    { irr::KEY_UP, irr::KEY_RIGHT, irr::KEY_DOWN, irr::KEY_LEFT, irr::KEY_RETURN}
};

class Player : public IXML
{
public:
    enum keyDirection {
        UP = 0,
        RIGHT,
        DOWN,
        LEFT,
        DROP_BOMB,
    };
    Player(SAppContext &ctx, VisualMap &map, const int &playerIdx = 0);
    ~Player();
    bool update(GameEventReceiver &receiver);
    void setExtraSpeed(irr::f32 newExtraSpeed);
    irr::scene::IAnimatedMeshSceneNode *getBody();
    bool isAlive() const;
    void kill();
    void revive();
    void setFire(bool enable);
    void setUnlimitedBombs(bool enabled);
    std::string serialize() final;
    void deserialize(std::string xmlCode) final;

private:
    /* movement */
    void changeMovementState();
    void move(GameEventReceiver &receiver);
    void moveUp(irr::core::vector3df &pos);
    void moveDown(irr::core::vector3df &pos);
    void moveLeft(irr::core::vector3df &pos);
    void moveRight(irr::core::vector3df &pos);

    bool dropBomb(GameEventReceiver &receiver);

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
    irr::f32 extraSpeedFactor; /* used for the SpeedUp_t powerUp */
    bool alive = true;
    bool fireUp = false;
    bool unlimitedBombs = false;

//    std::vector<Bomb> bombs; // @todo put this into the overall game class with all bombs on the field

    MyList<std::pair<Timer, PowerUpType>> powerUpTimers;
};

#endif //PLAYER_HPP_
