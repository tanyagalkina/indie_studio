#include "VisualMap.hpp"
#include "Coordinate.hpp"
#include "IAnimatedMesh.h"
#include "Menu.hpp"
#include "Error.hpp"

void VisualMap::display()
{
    this->smgr->drawAll();
}

void VisualMap::initializeMap(Map &map)
{
    for (auto [type, coord] : map)
    {
        if (type == Floor::BOX)
            this->blocks.push_back(new Cube(*this->context, Floor::EMPTY, coord));
        this->blocks.push_back(new Cube(*this->context, type, coord));
    }
}

void VisualMap::addCollision(irr::scene::IAnimatedMeshSceneNode *body)
{
    auto *anim = smgr->createCollisionResponseAnimator(metaSelector, body,
            irr::core::vector3df(10, 10, 10),
            irr::core::vector3df(0.f, 0.f, 0.f));
    body->addAnimator(anim);
    anim->drop();

    for (auto &block : blocks)
        block->addCollision(body);
}

VisualMap::VisualMap(SAppContext &ctx, Map &map)
    : context(&ctx)
{
    this->smgr = context->device->getSceneManager();
    this->driver = context->device->getVideoDriver();

    //if (!this->smgr->loadScene("media/map.irr"))
        //AssetLoadErrorMac("Can't load 'media/map.irr'");
    if (!this->smgr->loadScene("media/skybox.irr"))
        AssetLoadErrorMac("Can't load 'media/skybox.irr'");

    this->smgr->addCameraSceneNode(NULL, irr::core::vector3df(0, 400, -200),
            irr::core::vector3df(0, 0, -50));

    maxCoordinates = map.back().second;
    initializeMap(map);

    irr::core::array<irr::scene::ISceneNode *>	walls;
    smgr->getSceneNodesFromType(irr::scene::ESNT_CUBE, walls);
    metaSelector = smgr->createMetaTriangleSelector();

    for (int i = 0; i < walls.size(); i++) {
        auto selector = smgr->createTriangleSelectorFromBoundingBox(walls[i]);
        metaSelector->addTriangleSelector(selector);
        selector->drop();
    }
}

VisualMap::~VisualMap()
{
    this->metaSelector->drop();

    for (auto &block : blocks)
        delete block;
}

MyList<Cube *> VisualMap::getBlocks() const
{
    return blocks;
}

Coordinate VisualMap::getMaxCoordinates()
{
    return maxCoordinates;
}

void VisualMap::deserialize(std::string xmlCode)
{
}

std::string VisualMap::serialize()
{
    SerializeHelper sh;
    sh.beginKey("VisualMap");
    for (auto block : blocks)
        sh.addXML(block->serialize());
    sh.endKey("VisualMap");
    return sh.getXML();
}

void VisualMap::eraseCubes(const MyList<MyList<Cube *>::iterator>& eares)
{
    for (auto &it : eares)
        blocks.erase(it);
}
