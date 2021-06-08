#ifndef VISUAL_MAP_HPP_
#define VISUAL_MAP_HPP_

#include "AppContext.hpp"
#include "IParticleAnimatedMeshSceneNodeEmitter.h"
#include "ISceneManager.h"
#include "IVideoDriver.h"
#include "my_list.hpp"
#include <iostream>
#include <vector>

class VisualMap
{
public:
    VisualMap(SAppContext &ctx, MyList<std::string> &map);
    void display();
    void addCollision(irr::scene::IAnimatedMeshSceneNode *body);

private:
    void initializeMap(MyList<std::string> &map);
    irr::scene::IAnimatedMeshSceneNode *createCube(int i, int j);

private:
    /* general */
    SAppContext *context;
    irr::scene::ISceneManager *smgr;
    irr::video::IVideoDriver *driver;

    /* list of wooden blocks (that can be destroyed) */
    // @todo replace this with a class that contains more information about the
    // block so we can load diff texture and check if you can move through this
    // at any time or is there a powerup underneath, this Class should have an
    // addCollision(just like the VisualMap class) method to make collision
    // between this box and the player possible.
    std::vector<irr::scene::IAnimatedMeshSceneNode *> blocks;

    /* collision */
    /* this one is just a collection of multiple selectors to act as one big
     * selector */
    irr::scene::IMetaTriangleSelector *metaSelector;
};

#endif //VISUAL_MAP_HPP_