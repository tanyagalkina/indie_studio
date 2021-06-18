#ifndef VISUAL_MAP_HPP_
#define VISUAL_MAP_HPP_

#include "AppContext.hpp"
#include "Coordinate.hpp"
#include "IParticleAnimatedMeshSceneNodeEmitter.h"
#include "ISceneManager.h"
#include "IVideoDriver.h"
#include "my_list.hpp"
#include "Floor.hpp"
#include <iostream>
#include <vector>
#include "Cube.hpp"
#include "IXML.hpp"
using Map = MyList<std::pair<Floor::Type, Coordinate>>;

class VisualMap : IXML
{
public:
    VisualMap(SAppContext &ctx, Map &map);
    ~VisualMap();
    void display();
    void addCollision(irr::scene::IAnimatedMeshSceneNode *body);
    MyList<Cube *> getBlocks() const;
    void deserialize(std::string xmlCode) final;
    std::string serialize() final;
    Coordinate getMaxCoordinates();

private:
    void initializeMap(Map &map);
    irr::scene::IAnimatedMeshSceneNode *createCube(Floor::Type type, Coordinate coord);

private:
    /* general */
    SAppContext *context;
    irr::scene::ISceneManager *smgr;
    irr::video::IVideoDriver *driver;
    Coordinate maxCoordinates;

    /* list of wooden blocks (that can be destroyed) */
    // @todo replace this with a class that contains more information about the
    // block so we can load diff texture and check if you can move through this
    // at any time or is there a powerup underneath, this Class should have an
    // addCollision(just like the VisualMap class) method to make collision
    // between this box and the player possible.
    MyList<Cube *> blocks;

    /* collision */
    /* this one is just a collection of multiple selectors to act as one big
     * selector */
    irr::scene::IMetaTriangleSelector *metaSelector;
};

#endif //VISUAL_MAP_HPP_
